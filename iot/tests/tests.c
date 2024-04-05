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
//- Assertions

// TODO(rune):
// This is a very primtive test setup, just so we can get started with CI/CD.
// Some things that could be better:
//  - Better error reporting: Which test failed? Which assertion failed? Which file and linenumber?
//  - Don't just exit(1) on a failed assertion, e.g. continue with other tests

static void assert_string(string actual, string expect) {
    bool failed = !string_equal(expect, actual);
    if (failed) {
        printf("------------------------------------------------\n");
        printf("Assertion failed :(\n");
        printf("Expected:\n");
        printf("%.*s\n", (int)expect.len, expect.base);
        printf("------------------------------------------------\n");
        printf("Actual:\n");
        printf("%.*s\n", (int)actual.len, actual.base);
        printf("------------------------------------------------\n");
        exit(1);
    }
}

static void assert_bool(bool actual, bool expect) {
    bool failed = expect != actual;
    if (failed) {
        printf("------------------------------------------------\n");
        printf("Assertion failed :(\n");
        printf("Expected:\n");
        printf("%s\n", expect ? "true" : "false");
        printf("------------------------------------------------\n");
        printf("Actual:\n");
        printf("%s\n", actual ? "true" : "false");
        printf("------------------------------------------------\n");
        exit(1);
    }
}

static void assert_char(char actual, char expect) {
    char failed = expect != actual;
    if (failed) {
        printf("------------------------------------------------\n");
        printf("Assertion failed :(\n");
        printf("Expected:\n");
        printf("'%c'\n", expect);
        printf("------------------------------------------------\n");
        printf("Actual:\n");
        printf("'%c'\n", actual);
        printf("------------------------------------------------\n");
        exit(1);
    }
}

static void assert_int(int actual, int expect) {
    int failed = expect != actual;
    if (failed) {
        printf("------------------------------------------------\n");
        printf("Assertion failed :(\n");
        printf("Expected:\n");
        printf("%i\n", expect);
        printf("------------------------------------------------\n");
        printf("Actual:\n");
        printf("%i\n", actual);
        printf("------------------------------------------------\n");
        exit(1);
    }
}

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

    assert_string(actual, expect);
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

    assert_string(actual, expect);
}

static void test_http_generate_request_no_overflow() {
    struct {
        char too_small[64];
        char dont_overflow_into_here[64];
    } buffers = { 0 };

    const char magic = 123;
    buffers.dont_overflow_into_here[0] = magic;

    textbuf buf = { 0 };
    textbuf_init(&buf, buffers.too_small, sizeof(buffers.too_small));

    http_append_head_begin(&buf, string("GET"), string("/all/the/things"));
    for (int i = 0; i < 100; i++) {
        http_append_head_string(&buf, string("A lot"), string("of headers"));
    }

    assert_bool(buf.oom, true);
    assert_char(buffers.dont_overflow_into_here[0], magic);
}

////////////////////////////////////////////////////////////////
//- Parse http response tests

static void test_http_parse_response() {
    // NOTE(rune): Example response from an ASP.NET web API
    string res = string(
        "HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-Type: text/plain; charset=utf-8\r\n"
        "Date: Thu, 04 Apr 2024 11:25:22 GMT\r\n"
        "Server: Kestrel\r\n"
        "\r\n"
        "So what's it all about?"
    );

    int status_code   = { 0 };
    string name       = { 0 };
    string value      = { 0 };
    bool more_headers = { 0 };

    http_read_head_begin(&res, &status_code);
    assert_int(status_code, 200);

    more_headers = http_read_head_string(&res, &name, &value);
    assert_string(name, string("Connection"));
    assert_string(value, string("close"));
    assert_bool(more_headers, true);

    more_headers = http_read_head_string(&res, &name, &value);
    assert_string(name, string("Content-Type"));
    assert_string(value, string("text/plain; charset=utf-8"));
    assert_bool(more_headers, true);

    more_headers = http_read_head_string(&res, &name, &value);
    assert_string(name, string("Date"));
    assert_string(value, string("Thu, 04 Apr 2024 11:25:22 GMT"));
    assert_bool(more_headers, true);

    more_headers = http_read_head_string(&res, &name, &value);
    assert_string(name, string("Server"));
    assert_string(value, string("Kestrel"));
    assert_bool(more_headers, false);

    http_read_head_end(&res);

    // NOTE(rune): Body should be the only thing remaining.
    assert_string(res, string("So what's it all about?"));
}

////////////////////////////////////////////////////////////////
//- Test runner

#define run_test(func) (func(), printf(#func " (OK)\n"))

int main() {
    run_test(test_http_generate_get_request);
    run_test(test_http_generate_post_request);
    run_test(test_http_generate_request_no_overflow);
    run_test(test_http_parse_response);
    printf("All tests suceeded\n");
    return 0;
}
