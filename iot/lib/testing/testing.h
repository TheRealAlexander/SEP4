////////////////////////////////////////////////////////////////
// Global state

typedef void test_void_fn(void);

typedef struct test_state {
    // Is reset on every test_begin()
    char *name;
    test_void_fn *before_each;
    test_void_fn *after_each;
    int passed_tests;
    int failed_tests;

    // Is reset on every test_run()
    int failed_assertions;

    // Is never reset
    bool any_tests_failed_during_whole_runtime;
} test_state;

static test_state g_test;

////////////////////////////////////////////////////////////////
// Test runner

static void test_begin(char *name, test_void_fn *before_each, test_void_fn *after_each);
#define     test_run(test) test_run_(test, #test)
static void test_run_(test_void_fn *test, char *test_name);
static void test_end(void);

////////////////////////////////////////////////////////////////
// Source code location

#define test_loc__(a)    #a
#define test_loc_(a)     test_loc__(a)
#define test_loc()       (__FILE__ ":" test_loc_(__LINE__))

////////////////////////////////////////////////////////////////
// Assert without message

#define assert_string(expect, actual)   assert_string_msg_(test_loc(), expect, actual, "")
#define assert_bool(expect, actual)     assert_bool_msg_(test_loc(), expect, actual, "")
#define assert_char(expect, actual)     assert_char_msg_(test_loc(), expect, actual, "")
#define assert_int(expect, actual)      assert_int_msg_(test_loc(), expect, actual, "")
#define assert_hex8(expect, actual)     assert_hex8_msg_(test_loc(), expect, actual, "")
#define assert_hex16(expect, actual)    assert_hex16_msg_(test_loc(), expect, actual, "")
#define assert_uint8(expect, actual)    assert_uint8_msg_(test_loc(), expect, actual, "")
#define assert_uint16(expect, actual)   assert_uint16_msg_(test_loc(), expect, actual, "")

////////////////////////////////////////////////////////////////
// Assert without message

#define assert_string_msg(expect, actual, msg)  assert_string_msg_(test_loc(), expect, actual, msg)
#define assert_bool_msg(expect, actual, msg)    assert_bool_msg_(test_loc(), expect, actual, msg)
#define assert_char_msg(expect, actual, msg)    assert_char_msg_(test_loc(), expect, actual, msg)
#define assert_int_msg(expect, actual, msg)     assert_int_msg_(test_loc(), expect, actual, msg)
#define assert_hex8_msg(expect, actual, msg)    assert_hex8_msg_(test_loc(), expect, actual, msg)
#define assert_hex16_msg(expect, actual, msg)   assert_hex16_msg_(test_loc(), expect, actual, msg)
#define assert_uint8_msg(expect, actual, msg)   assert_uint8_msg_(test_loc(), expect, actual, msg)
#define assert_uint16_msg(expect, actual, msg)  assert_uint16_msg_(test_loc(), expect, actual, msg)

////////////////////////////////////////////////////////////////
// Non-macro asserts

static void assert_string_msg_(char *loc, char *expect, char *actual, char *msg);
static void assert_bool_msg_(char *loc, bool expect, bool actual, char *msg);
static void assert_char_msg_(char *loc, char expect, char actual, char *msg);
static void assert_int_msg_(char *loc, int expect, int actual, char *msg);
static void assert_hex8_msg_(char *loc, uint8_t expect, uint8_t actual, char *msg);
static void assert_hex16_msg_(char *loc, uint16_t expect, uint16_t actual, char *msg);
static void assert_uint8_msg_(char *loc, uint8_t expect, uint8_t actual, char *msg);
static void assert_uint16_msg_(char *loc, uint16_t expect, uint16_t actual, char *msg);

