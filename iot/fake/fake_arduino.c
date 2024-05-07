////////////////////////////////////////////////////////////////
//- Include standard library

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

////////////////////////////////////////////////////////////////
//- Include OS headers

#if _WIN32
#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2ipdef.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

////////////////////////////////////////////////////////////////
//- Include our own stuff

#include "../src/string.h"
#include "../src/string.c"
#include "../src/textbuf.h"
#include "../src/textbuf.c"
#include "../src/http.h"
#include "../src/http.c"

////////////////////////////////////////////////////////////////
//- File system

static string read_entire_file(char *file_name, bool *succeeded) {
    bool ok = false;

    FILE *f = fopen(file_name, "rb");
    if (!f) goto exit;

    if (fseek(f, 0, SEEK_END)) goto exit;
    size_t fsize = ftell(f);
    if (fseek(f, 0, SEEK_SET)) goto exit;

    char *buffer = malloc(fsize + 1);
    if (!buffer) goto exit;

    if (fread(buffer, fsize, 1, f) != 1) goto exit;

    buffer[fsize] = 0;

    ok = true;

exit:
    if (f) fclose(f);

    string ret = string("");
    if (ok) {
        ret = (string) { buffer, fsize };
    } else {
        perror(0);
        if (buffer) free(buffer);
    }

    if (succeeded) *succeeded = ok;

    return ret;
}

////////////////////////////////////////////////////////////////
//- Networking

typedef struct lookup_host_result  lookup_host_result;
struct lookup_host_result {
    char ipv4_address[64];
    char ipv6_address[64];
};

// NOTE(rune): lookup_host() is based on https://gist.github.com/jirihnidek/bf7a2363e480491da72301b228b35d5d
static int lookup_host(char *host, lookup_host_result  *out) {
    struct addrinfo hints, *res, *result;
    int errcode;
    void *ptr;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_CANONNAME;

    errcode = getaddrinfo(host, NULL, &hints, &result);
    if (errcode != 0) {
        perror("getaddrinfo");
        return -1;
    }

    res = result;

    while (res) {
        switch (res->ai_family) {
            case AF_INET: {
                ptr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
                inet_ntop(res->ai_family, ptr, out->ipv4_address, sizeof(out->ipv4_address));
            } break;

            case AF_INET6: {
                ptr = &((struct sockaddr_in6 *)res->ai_addr)->sin6_addr;
                inet_ntop(res->ai_family, ptr, out->ipv6_address, sizeof(out->ipv6_address));
            } break;
        }

        res = res->ai_next;
    }

    freeaddrinfo(result);

    return 0;
}

static void sleep_ms(int ms) {
#if _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

static string socket_send_and_recieve(char *addr, unsigned short port, string send_data, void *recv_buf, int recv_size) {
    int sd = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd == -1) {
        perror(0);
        fprintf(stderr, "Could not open socket TCP socket: %i\n", errno);
        exit(1);
    }

    struct sockaddr_in sa = { 0 };
    sa.sin_family      = AF_INET;
    sa.sin_addr.s_addr = inet_addr(addr);
    sa.sin_port        = htons(port);

    if (connect(sd, (struct sockaddr *)&sa, sizeof(sa))) {
        fprintf(stderr, "Could not connect address %s:%i: %i\n", addr, port, errno);
        exit(1);
    }

    send(sd, send_data.base, send_data.len, 0);

    int total_recv_len = 0;
    while (1) {
        int curr_recv_len = recv(sd, (char *)recv_buf + total_recv_len, recv_size - total_recv_len, 0);

        // NOTE(rune): Not enough space in the recieve buffer.
        if (total_recv_len + curr_recv_len > recv_size) {
            break;
        }

        // NOTE(rune): Connection has closed gracefully.
        // See: https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-recv
        if (curr_recv_len == 0) { 
            break;
        }

        total_recv_len += curr_recv_len;
    }

#if _WIN32
    closesocket(sd);
#else
    close(sd);
#endif

    string ret = { recv_buf, total_recv_len };
    return ret;
}

#define ANSI_FG_DEFAULT             "\033[39m"
#define ANSI_FG_GRAY                "\033[90m"

static void send_http_post_request(char *host, unsigned short port, string endpoint, string body) {

    // Find ip address from host name
    lookup_host_result lookup_result = { 0 };
    lookup_host(host, &lookup_result);

    // Request/response buffers
    char req_storage[4096];
    char res_storage[4096];

    // Build HTTP request string
    textbuf buf;
    textbuf_init(&buf, req_storage, sizeof(req_storage));
    http_append_head_begin(&buf, string("POST"), endpoint);
    http_append_head_string(&buf, string("Connection"), string("Close"));
    http_append_head_string(&buf, string("Accept"), string("application/json"));
    http_append_head_string(&buf, string("Content-Type"), string("application/json"));
    http_append_head_int(&buf, string("Content-Length"), (int)body.len);
    http_append_head_end(&buf);
    textbuf_append_string(&buf, body);

    // Send over TCP socket 
    string req = textbuf_to_string(&buf);
    string res = socket_send_and_recieve(lookup_result.ipv4_address, port, req, res_storage, sizeof(res_storage));

    // Print results
    printf(ANSI_FG_GRAY);
    printf("\n==============================================================================\n");
    printf("REQUEST\n");
    printf(ANSI_FG_DEFAULT);
    printf("%.*s\n", (int)req.len, req.base);

    printf(ANSI_FG_GRAY);
    printf("==============================================================================\n");
    printf("RESPONSE\n");
    printf(ANSI_FG_DEFAULT);
    printf("%.*s\n", (int)res.len, res.base);
}

static void send_http_get_request(char *host, unsigned short port, string endpoint) {

    // Find ip address from host name
    lookup_host_result lookup_result = { 0 };
    lookup_host(host, &lookup_result);

    // Request/response buffers
    char req_storage[4096];
    char res_storage[4096];

    // Build HTTP request string
    textbuf buf;
    textbuf_init(&buf, req_storage, sizeof(req_storage));
    http_append_head_begin(&buf, string("GET"), endpoint);
    http_append_head_string(&buf, string("Host"), string("httpbin.org"));
    http_append_head_string(&buf, string("Accept"), string("*/*"));

    http_append_head_string(&buf, string("Connection"), string("Close"));
    //http_append_head_string(&buf, string("Accept"), string("application/json"));
    http_append_head_end(&buf);

    // Send over TCP socket 
    string req = textbuf_to_string(&buf);
    string res = socket_send_and_recieve(lookup_result.ipv4_address, port, req, res_storage, sizeof(res_storage));

    // Print results
    printf(ANSI_FG_GRAY);
    printf("\n==============================================================================\n");
    printf("REQUEST\n");
    printf(ANSI_FG_DEFAULT);
    printf("%.*s\n", (int)req.len, req.base);

    printf(ANSI_FG_GRAY);
    printf("==============================================================================\n");
    printf("RESPONSE\n");
    printf(ANSI_FG_DEFAULT);
    printf("%.*s\n", (int)res.len, res.base);
}

////////////////////////////////////////////////////////////////
//- Command line program

typedef struct args args;
struct args {
    int count;
    char **v;
};

static char *args_pop(args *args) {
    char *popped = 0;
    if (args->count > 0) {
        args->count--;
        popped = *args->v++;
    }
    return popped;
}

static string args_pop_string(args *args) {
    char *popped = args_pop(args);
    if (popped) {
        return (string) { popped, strlen(popped) };
    } else {
        return string("");
    }
}

static int args_pop_int(args *args) {
    string s = args_pop_string(args);
    if (s.len > 0) {
        return string_to_int(s);
    } else {
        return 0;
    }
}

int main(int argc, char **argv) {

    //- Windows specific initialization
#if _WIN32
    WSADATA wsaData;
    int error = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (error != NO_ERROR) {
        printf("WSAStartup failed: %d\n", error);
        exit(1);
    }
#endif

    //- Read commandline args
    args args = { argc, argv };
    char *exe_name = args_pop(&args);
    char *sub_cmd = args_pop(&args);
    if (sub_cmd == 0) {
        printf("No subcommand given\n");
        return 1;
    }

    //- Subcommand: Single request 
    if (strcmp(sub_cmd, "single-request") == 0) {
        if (args.count != 4) {
            printf("Usage: %s <host> <port> <endpoint> <body file name>\n", exe_name);
            return 1;
        }

        char * host           = args_pop(&args);
        int    port           = args_pop_int(&args);
        string endpoint       = args_pop_string(&args);
        char * body_file_name = args_pop(&args);

        string body = read_entire_file(body_file_name, 0);
        if (body.len == 0) {
            printf("Could not read body file: %s\n", body_file_name);
            return 1;
        }

        send_http_post_request(host, port, endpoint, body);
    }

    //- Subcommand: Simulate
    if (strcmp(sub_cmd, "simulate") == 0) {
        if (args.count != 2) {
            printf("Usage: %s <host> <port>\n", exe_name);
            return 1;
        }

        char * host = args_pop(&args);
        int    port = args_pop_int(&args);

        while (1) {
            float temperature = ((float)rand() / (float)RAND_MAX) * 5.0f + 18.0f; // TODO(rune): Read from mock sensor.
            float humidity    = ((float)rand() / (float)RAND_MAX) * 90.0f + 5.0f; // TODO(rune): Read from mock sensorr.

            char   body_buf[64];
            int    body_len = snprintf(body_buf, sizeof(body_buf), "{ \"temperature\": %f, \"humidity\": %f  }", temperature, humidity);
            string body = { body_buf, body_len };

            send_http_post_request(host, port, string("/report/the-temperature"), body);
            sleep_ms(15000);
        }
    }

    return 0;
}
