////////////////////////////////////////////////////////////////
//- Write HTTP request

static void http_append_head_begin(textbuf *buf, string method, string endpoint);
static void http_append_head_string(textbuf *buf, string header_name, string header_value);
static void http_append_head_int(textbuf *buf, string header_name, int header_value);
static void http_append_head_end(textbuf *buf);

////////////////////////////////////////////////////////////////
//- Read HTTP response

static void http_read_head_begin(string *s, int *status_code);
static bool http_read_head_string(string *s, string *header_name, string *header_value);
static void http_read_head_end(string *s);
