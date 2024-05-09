#if NOT_PLATFORMIO
// Nothing
#else
#include "http.h"
#endif

////////////////////////////////////////////////////////////////
//- Write HTTP request

// Reference https://developer.mozilla.org/en-US/docs/Web/HTTP/Overview

static void http_append_head_begin(textbuf *buf, string method, string endpoint) {
    textbuf_append_string(buf, method);
    textbuf_append_string(buf, string(" "));
    textbuf_append_string(buf, endpoint);
    textbuf_append_string(buf, string(" "));
    textbuf_append_string(buf, string("HTTP/1.0")); // NOTE(rune): Use HTTP 1.0 so we don't have do deal with chunked responses.
    textbuf_append_string(buf, string("\r\n"));
}

static void http_append_head_string(textbuf *buf, string header_name, string header_value) {
    textbuf_append_string(buf, header_name);
    textbuf_append_string(buf, string(": "));
    textbuf_append_string(buf, header_value);
    textbuf_append_string(buf, string("\r\n"));
}

static void http_append_head_int(textbuf *buf, string header_name, int header_value) {
    textbuf_append_string(buf, header_name);
    textbuf_append_string(buf, string(": "));
    textbuf_append_int(buf, header_value);
    textbuf_append_string(buf, string("\r\n"));
}

static void http_append_head_end(textbuf *buf) {
    textbuf_append_string(buf, string("\r\n"));
}

////////////////////////////////////////////////////////////////
//- Read HTTP response

static void http_read_head_begin(string *s, int *status_code) {
    // NOTE(rune): First line of response if formatted like this:
    // "HTTP/1.1 200 OK"

    string line               = string_chop_by_delim(s, string("\r\n"));
    string version            = string_chop_by_delim(&line, string(" "));
    string status_code_string = string_chop_by_delim(&line, string(" "));
    string status_name        = line;

    *status_code = string_to_int(status_code_string);
}

static bool http_read_head_string(string *s, string *header_name, string *header_value) {
    string line   = string_chop_by_delim(s, string("\r\n"));
    *header_name  = string_chop_by_delim(&line, string(": "));
    *header_value = line;

    // NOTE(rune): Check for blank line between head and body.
    bool any_more_headers = !(s->len < 2 || string_starts_with(*s, string("\r\n")));
    return any_more_headers;
}

static void http_read_head_end(string *s) {
    string_chop_by_delim(s, string("\r\n"));
}
