// NOTE(rune): Dette er ikke en del af CI/CD, men er bare til test af HTTP lokalt.
// Eksempel server:
//  var builder = WebApplication.CreateBuilder(args);
//  var app = builder.Build();
//  app.MapGet("/", () => "So what's it all about?");
//  app.Run();

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
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

////////////////////////////////////////////////////////////////
//- Include utility

#include "../src/string.h"
#include "../src/string.c"
#include "../src/textbuf.h"
#include "../src/textbuf.c"
#include "../src/http.h"
#include "../src/http.c"

////////////////////////////////////////////////////////////////
//- Socket test

static string socket_send_and_recieve(char *addr, unsigned short port, void *send_buf, int send_size, void *recv_buf, int recv_size) {
#if _WIN32
    WSADATA wsaData;
    int error = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (error != NO_ERROR) {
        printf("WSAStartup failed: %d\n", error);
        exit(1);
    }
#endif

    int sd = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd == -1) {
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

    send(sd, send_buf, send_size, 0);
    int recv_len = recv(sd, recv_buf, recv_size, 0);

#if _WIN32
    closesocket(sd);
#else
    close(sd);
#endif

    string ret = { recv_buf, recv_len };
    return ret;
}

int main(void) {
    char req_storage[4096];
    char res_storage[4096];

    textbuf buf;
    textbuf_init(&buf, req_storage, sizeof(req_storage));

    http_append_head_begin(&buf, string("GET"), string("/"));
    http_append_head_string(&buf, string("Host"), string("localhost"));
    http_append_head_string(&buf, string("Connection"), string("Close"));
    http_append_head_end(&buf);

    string req = textbuf_to_string(&buf);
    string res = socket_send_and_recieve("127.0.0.1", 5043, req.base, req.len, res_storage, sizeof(res_storage));

    printf("------------------\n");
    printf("REQUEST\n");
    printf("------------------\n");
    printf("%.*s\n", (int)req.len, req.base);
    printf("------------------\n");
    printf("RESPONSE\n");
    printf("------------------\n");
    printf("%.*s\n", (int)res.len, res.base);
    printf("------------------\n");

    return 0;
}
