////////////////////////////////////////////////////////////////
//- Fixed sized append-buffer

typedef struct textbuf {
    char  *base;
    size_t size;
    size_t pos;
    bool oom; // Out of memory
} textbuf;

static void     textbuf_init(textbuf *buf, char *base, size_t capacity);
static void     textbuf_reset(textbuf *buf);
static string   textbuf_to_string(textbuf *buf);

static char *   textbuf_append(textbuf *buf, size_t size);
static void     textbuf_append_char(textbuf *buf, char c);
static void     textbuf_append_string(textbuf *buf, string s);
static void     textbuf_append_int(textbuf *buf, int i);
