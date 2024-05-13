#include "unity.h"
#include "fff.h"
#include "display_button.h"
#include "tone.h"

DEFINE_FFF_GLOBALS;

// Declare fake functions
FAKE_VOID_FUNC(updateDisplay);
FAKE_VOID_FUNC(setScoreTo40);
FAKE_VOID_FUNC(tone_play_final_fantasy_victory);
FAKE_VOID_FUNC(controller_init);
// External declarations for game logic

void setUp(void) {
    RESET_FAKE(updateDisplay);
    RESET_FAKE(setScoreTo40);
    RESET_FAKE(tone_play_final_fantasy_victory);
    FFF_RESET_HISTORY();

    teamscore_a = 0;
    teamscore_b = 0;
}

void tearDown(void) {
    // Cleanup actions if necessary
}

void test_checkScoreAPlus_IncrementsCorrectly(void) {
    checkScoreAPlus();
    TEST_ASSERT_EQUAL(15, teamscore_a);
    checkScoreAPlus();
    TEST_ASSERT_EQUAL(30, teamscore_a);
    checkScoreAPlus();
    TEST_ASSERT_EQUAL(40, teamscore_a);
    checkScoreAPlus();
    TEST_ASSERT_EQUAL(41, teamscore_a);
    TEST_ASSERT_EQUAL(1, updateDisplay_fake.call_count);}

void test_checkScoreBPlus_FromZero(void) {
    checkScoreBPlus();
    TEST_ASSERT_EQUAL(15, teamscore_b);
    checkScoreBPlus();
    TEST_ASSERT_EQUAL(30, teamscore_b);
    checkScoreBPlus();
    TEST_ASSERT_EQUAL(41, teamscore_b);
    TEST_ASSERT_EQUAL(1, tone_play_final_fantasy_victory_fake.call_count);
    }


void test_checkScoreAMinus_From40to30(void) {
    teamscore_a = 40;
    checkScoreAMinus();
    TEST_ASSERT_EQUAL(30, teamscore_a);
    TEST_ASSERT_EQUAL(1, setScoreTo40_fake.call_count);}


void test_resetScores_TriggersCorrectFunctions(void) {
    resetScore();
    TEST_ASSERT_EQUAL(0, teamscore_a);
    TEST_ASSERT_EQUAL(0, teamscore_b);
}

void test_decrementScore_FromAdvantageToDeuce(void) {
    teamscore_a = 41;
    checkScoreAMinus();
    TEST_ASSERT_EQUAL(40, teamscore_a);
}

void test_incrementScore_DoesNotExceedVictory(void) {
    teamscore_a = 42;
    checkScoreAPlus();
    TEST_ASSERT_EQUAL(42, teamscore_a);
    TEST_ASSERT_EQUAL(1, tone_play_final_fantasy_victory_fake.call_count);
    }


void test_checkScoreBMinus_DeincrementsCorrectly(void) {
    teamscore_b = 30;
    checkScoreBMinus();
    TEST_ASSERT_EQUAL(15, teamscore_b);
    checkScoreBMinus();
    TEST_ASSERT_EQUAL(0, teamscore_b);
}

void test_resetScores(void) {
    setScoreTo40();
    resetScore();
    TEST_ASSERT_EQUAL(0, teamscore_a);
    TEST_ASSERT_EQUAL(0, teamscore_b);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_checkScoreAPlus_IncrementsCorrectly);
    RUN_TEST(test_checkScoreBPlus_FromZero);
    RUN_TEST(test_checkScoreAMinus_From40to30);
    RUN_TEST(test_resetScores_TriggersCorrectFunctions);
    RUN_TEST(test_decrementScore_FromAdvantageToDeuce);
    RUN_TEST(test_incrementScore_DoesNotExceedVictory);
    RUN_TEST(test_checkScoreBMinus_DeincrementsCorrectly);
    RUN_TEST(test_resetScores);
    return UNITY_END();
}
