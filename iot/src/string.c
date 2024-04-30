////////////////////////////////////////////////////////////////
//- Counted string

static bool string_equal(string a, string b) {
    if (a.len == b.len) {
        return memcmp(a.base, b.base, b.len) == 0;
    } else {
        return false;
    }
}

static bool string_starts_with(string a, string b) {
    if (a.len >= b.len) {
        return memcmp(a.base, b.base, b.len) == 0;
    } else {
        return false;
    }
}

static string string_chop_by_delim(string *s, string delim) {
    string after_delim  = string("");
    string before_delim = *s;

    if (s->len >= delim.len) {
        for (size_t i = 0; i < s->len - delim.len + 1; i++) {
            if (memcmp(s->base + i, delim.base, delim.len) == 0) {
                after_delim.base  = s->base + i + delim.len;
                after_delim.len   = s->len  - i - delim.len;
                before_delim.base = s->base;
                before_delim.len  = i;
                break;
            }
        }
    }

    *s = after_delim;
    return before_delim;
}

static int string_to_int(string s) {
    int i = 0;
    while (s.len > 0) {
        char c = *s.base;
        if (c >= '0' && c <= '9') {
            s.base++;
            s.len--;

            i *= 10;
            i += c - '0';
        }
    }
    return i;
}

static string int_to_string(int i, char *buf, size_t buf_cap) {
    int  len = 0;
    while (i > 0 && len < buf_cap) {
        int digit = i % 10;
        i /= 10;
        len++;
        buf[buf_cap - len] = (char)('0' + digit);
    }

    string s = { &buf[buf_cap - len], len };
    return s;
}
