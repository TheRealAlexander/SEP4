
static int  http_build_request(char *http_buf, int http_cap);

// NOTE(rune): Fjern whitespace så vi kan lave string comparison,
// uden at bekymre os om formatting fra serveren.
static int  http_trim_inplace(char *http_buf, int http_len);

// NOTE(rune): Assumes that response is trimmed of all whitspace and is null terminated.
// Returns false if the property is not found, and in that case does not touch *value.
static bool http_read_bool_from_response(char *response, char *property, bool *value);
static bool http_read_int_from_response(char *response, char *property, int *value);

// NOTE(rune): Set globals variable in g_measurement based on content of http_buf.
static void http_process_response(char *http_buf, int http_len);
