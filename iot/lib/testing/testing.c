////////////////////////////////////////////////////////////////
// Test runner

static void test_begin(char *name, test_void_fn *before_each, test_void_fn *after_each) {
    g_test.name              = name;
    g_test.before_each       = before_each;
    g_test.after_each        = after_each;
    g_test.failed_tests      = 0;
    g_test.passed_tests      = 0;
}

static void test_run_(test_void_fn *test, char *test_name) {
    g_test.failed_assertions = 0;

    // Setup
    if (g_test.before_each != NULL) {
        g_test.before_each();
    }

    // Run the test
    test();

    // Teardown
    if (g_test.after_each != NULL) {
        g_test.after_each();
    }

    // Print result
    if (g_test.failed_assertions == 0) {
        send_to_pc_fmt("%s " ANSI_FG_GREEN "(OK)\n" ANSI_RESET, test_name);
        g_test.passed_tests += 1;
    } else {
        send_to_pc_fmt("%s " ANSI_FG_RED "(FAIL)\n" ANSI_RESET, test_name);
        g_test.failed_tests += 1;
        g_test.any_tests_failed_during_whole_runtime = true;
    }
}

static void test_end(void) {
    // Print summary
    send_to_pc_fmt("\n");
    send_to_pc_fmt("%s: %d/%d passed\n", g_test.name, g_test.passed_tests, g_test.passed_tests + g_test.failed_tests);
    send_to_pc_fmt("\n");
    send_to_pc_fmt(ANSI_FG_GRAY "================================\n" ANSI_RESET);
    send_to_pc_fmt("\n");
}

////////////////////////////////////////////////////////////////
// Assertions

#define ASSERT_T(cmp, fmt) {                                 \
    bool failed = cmp;                                       \
    if (failed) {                                            \
        g_test.failed_assertions += 1;                       \
        send_to_pc_fmt(ANSI_FG_BRIGHT_RED);                  \
        send_to_pc_fmt("\n");                                \
        send_to_pc_fmt("%s\n", loc);                         \
        send_to_pc_fmt("    Expected: " fmt "\n", expect);   \
        send_to_pc_fmt("    Actual:   " fmt "\n", actual);   \
        if (strlen(msg) > 0) {                               \
            send_to_pc_fmt("    Message:  %s\n", msg);       \
        }                                                    \
        send_to_pc_fmt(ANSI_RESET);                          \
    }                                                        \
}                                                            \

static void assert_string_msg_(char *loc, char *expect, char *actual, char *msg)        { ASSERT_T(strcmp(expect, actual), "%s");   }
static void assert_bool_msg_(char *loc, bool expect, bool actual, char *msg)            { ASSERT_T(expect != actual,       "%d");   }
static void assert_char_msg_(char *loc, char expect, char actual, char *msg)            { ASSERT_T(expect != actual,       "%c");   }
static void assert_int_msg_(char *loc, int expect, int actual, char *msg)               { ASSERT_T(expect != actual,       "%i");   }
static void assert_hex8_msg_(char *loc, uint8_t expect, uint8_t actual, char *msg)      { ASSERT_T(expect != actual,       "%02x"); }
static void assert_hex16_msg_(char *loc, uint16_t expect, uint16_t actual, char *msg)   { ASSERT_T(expect != actual,       "%04x"); }
static void assert_uint8_msg_(char *loc, uint8_t expect, uint8_t actual, char *msg)     { ASSERT_T(expect != actual,       "%u");   }
static void assert_uint16_msg_(char *loc, uint16_t expect, uint16_t actual, char *msg)  { ASSERT_T(expect != actual,       "%u");   }

#undef ASSERT_T