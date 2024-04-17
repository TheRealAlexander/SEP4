////////////////////////////////////////////////////////////////
//- Fixed sized append-buffer

static void textbuf_init(textbuf *buf, char *base, size_t size) {
    buf->base = base;
    buf->size = size;
    buf->pos  = 0;
}

static void textbuf_reset(textbuf *buf) {
    buf->pos = 0;
    buf->oom = false;
}

static string textbuf_to_string(textbuf *buf) {
    string ret = { buf->base, buf->pos };
    return ret;
}

static char *textbuf_append(textbuf *buf, size_t size) {
    if (buf->oom) {
        return NULL;
    }

    if (buf->pos + size < buf->size) {
        char *ret = buf->base + buf->pos;
        buf->pos += size;
        return ret;
    } else {
        buf->oom = true;
        return NULL;
    }
}

static void textbuf_append_char(textbuf *buf, char c) {
    char *v = textbuf_append(buf, sizeof(char));
    if (v) {
        *v = c;
    }
}

static void textbuf_append_string(textbuf *buf, string s) {
    char *v = textbuf_append(buf, s.len);
    if (v) {
        memcpy(v, s.base, s.len);
    }
}

static void textbuf_append_int(textbuf *buf, int i) {
    char temp[16];
    string s = int_to_string(i, temp, sizeof(temp));
    textbuf_append_string(buf, s);
}
