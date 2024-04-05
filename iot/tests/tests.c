////////////////////////////////////////////////////////////////
//- Include standard library

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

////////////////////////////////////////////////////////////////
//- Include utility

#include "../src/string.h"
#include "../src/string.c"
#include "../src/textbuf.h"
#include "../src/textbuf.c"
#include "../src/http.h"
#include "../src/http.c"

////////////////////////////////////////////////////////////////
//- Generate HTTP request tests

static void test_http_generate_get_request(void) {
    char storage[1024];

    textbuf buf = { 0 };
    textbuf_init(&buf, storage, sizeof(storage));

    http_append_head_begin(&buf, string("GET"), string("/all/the/things"));
    http_append_head_string(&buf, string("Host"), string("localhost"));
    http_append_head_string(&buf, string("Connection"), string("Close"));
    http_append_head_end(&buf);

    string actual = textbuf_to_string(&buf);
    string expect = string(
        "GET /all/the/things HTTP/1.0\r\n"
        "Host: localhost\r\n"
        "Connection: Close\r\n"
        "\r\n"
    );

    if (!string_equal(actual, expect)) {
        exit(1);
    }
}

static void test_http_generate_post_request(void) {
    char storage[1024];

    textbuf buf = { 0 };
    textbuf_init(&buf, storage, sizeof(storage));

    string body = string("{ \"a\": 123 }");

    http_append_head_begin(&buf, string("POST"), string("/all/the/things"));
    http_append_head_string(&buf, string("Host"), string("localhost"));
    http_append_head_string(&buf, string("Connection"), string("Close"));
    http_append_head_string(&buf, string("Accept"), string("application/json"));
    http_append_head_string(&buf, string("Content-Type"), string("application/json"));
    http_append_head_int(&buf, string("Content-Length"), (int)body.len);
    http_append_head_end(&buf);
    textbuf_append_string(&buf, body);

    string actual = textbuf_to_string(&buf);
    string expect = string(
        "POST /all/the/things HTTP/1.0\r\n"
        "Host: localhost\r\n"
        "Connection: Close\r\n"
        "Accept: application/json\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 12\r\n"
        "\r\n"
        "{ \"a\": 123 }"
    );

    if (!string_equal(actual, expect)) {
        exit(1);
    }
}

////////////////////////////////////////////////////////////////
//- Test runner

#define run_test(func) (func(), printf(#func " (OK)\n"))

int main() {
    run_test(test_http_generate_get_request);
    run_test(test_http_generate_post_request);
    printf("All tests suceeded\n");
    return 0;
}
