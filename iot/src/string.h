////////////////////////////////////////////////////////////////
//- Counted string

// NOTE(rune): When parsing http/json it is easier to work with counted strings
// than null terminated strings, since we don't need to insert null terminators
// everywhere or do any allcoations, when taking sub-strings.

typedef struct string string;
struct string {
    char *base;
    size_t len;
};

// NOTE(rune): Converts null terminated string literal to counted string literal,
// We need a seperate macro for compile time contants because designated initializers are annoying.
#define string(literal) (string) { .base = (literal), .len = sizeof(literal) - 1 }
#define STRING(literal)          { .base = (literal), .len = sizeof(literal) - 1 }

static bool     string_equal(string a, string b);
static bool     string_starts_with(string a, string b);
static string   string_chop_by_delim(string *s, string delim);
static int      string_to_int(string s);
static string   int_to_string(int i, char *buf, size_t buf_cap);

