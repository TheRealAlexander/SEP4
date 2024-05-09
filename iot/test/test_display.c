#include "unity.h"
#include "fff.h"
#include "display_button.h"

DEFINE_FFF_GLOBALS;

// Declare fake functions
FAKE_VOID_FUNC(updateDisplay);
FAKE_VOID_FUNC(setScoreTo40);

void setUp(void) {
    RESET_FAKE(updateDisplay);
    RESET_FAKE(setScoreTo40);
    FFF_RESET_HISTORY();

    teamscore_a = 0;
    teamscore_b = 0;
}

void tearDown(void) {
    
}

// Test cases
void test_checkScoreAPlus_IncrementsCorrectly(void) {
    teamscore_a = 0;
    checkScoreAPlus();
    TEST_ASSERT_EQUAL(15, teamscore_a);

    checkScoreAPlus();
    TEST_ASSERT_EQUAL(30, teamscore_a);

    checkScoreAPlus();
    TEST_ASSERT_EQUAL(40, teamscore_a);

    teamscore_a = 40;
    teamscore_b = 42;  
    checkScoreAPlus();
    TEST_ASSERT_EQUAL(40, teamscore_a); 
    TEST_ASSERT(setScoreTo40_fake.call_count == 1);  
}

void test_checkScoreBPlus_FromZero(void) {
    teamscore_b = 0;
    checkScoreBPlus();
    TEST_ASSERT_EQUAL(15, teamscore_b);
    
    checkScoreBPlus();
    TEST_ASSERT_EQUAL(30, teamscore_b);
    
    checkScoreBPlus();
    TEST_ASSERT_EQUAL(40, teamscore_b);
    
    teamscore_b = 40;
    teamscore_a = 42;
    checkScoreBPlus();
    TEST_ASSERT_EQUAL(41, teamscore_b);  
}

// Main function to execute tests
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_checkScoreAPlus_IncrementsCorrectly);
    RUN_TEST(test_checkScoreBPlus_FromZero);
    return UNITY_END();
}
