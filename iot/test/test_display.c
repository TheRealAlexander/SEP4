#include "unity.h"
#include "fff.h"
#include "display_button.h"
#include "tone.h"
#include "driverMHZ19B.h"
#include "uart.h"

DEFINE_FFF_GLOBALS;

// Declare fake functions
FAKE_VOID_FUNC(updateDisplay);
// FAKE_VOID_FUNC(setScoreTo40);
FAKE_VOID_FUNC(tone_play_final_fantasy_victory);
FAKE_VOID_FUNC(controller_init);
FAKE_VOID_FUNC(uart_send_array_blocking, USART_t, uint8_t *, uint16_t);
// External declarations for game logic

void setUp(void) {
    // Display setup
    RESET_FAKE(updateDisplay);
    // RESET_FAKE(setScoreTo40);
    RESET_FAKE(tone_play_final_fantasy_victory);

    teamscore_a = 0;
    teamscore_b = 0;

    // CO2 setup
    RESET_FAKE(uart_send_array_blocking);
    FFF_RESET_HISTORY();
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
    // TEST_ASSERT_EQUAL(1, setScoreTo40_fake.call_count);
    }


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

void test_checksum2_correct(void) {
    uint8_t test_packet[] = {0xFF, 0x86, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t expected_checksum = 0x79; 

    uint8_t calculated_checksum = checksum2(test_packet);
    TEST_ASSERT_EQUAL_HEX8(expected_checksum, calculated_checksum);
}
void test_checksum2_zeroes(void){
    uint8_t test_packet[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t expected_checksum = 0x00;  
    uint8_t calculated_checksum = checksum2(test_packet);
    TEST_ASSERT_EQUAL_HEX8(expected_checksum, calculated_checksum);
}
void test_checksum2_max(void){
    uint8_t test_packet[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    uint8_t expected_checksum = 0x07;  
    uint8_t calculated_checksum = checksum2(test_packet);
    TEST_ASSERT_EQUAL_HEX8(expected_checksum, calculated_checksum);
}

void test_calculatePartsPerMil_normal(void) {
    uint8_t test_packet[] = {0x00, 0x00, 0x04, 0xD2}; 
    uint16_t expected = 1234;
    uint16_t result = calculatePartsPerMil(test_packet);
    TEST_ASSERT_EQUAL_UINT16(expected, result);
}
void test_calculatePartsPerMil_null_pointer(void) {
    uint16_t result = calculatePartsPerMil(NULL);  
    TEST_ASSERT_EQUAL_UINT16(0, result);
}
void test_calculatePartsPerMil_max(void) {
    uint8_t test_packet[] = {0x00, 0x00, 0xFF, 0xFF}; 
    uint16_t expected = 65535;
    uint16_t result = calculatePartsPerMil(test_packet);
    TEST_ASSERT_EQUAL_UINT16(expected, result);
}
void test_calculatePartsPerMil_min(void) {
    uint8_t test_packet[] = {0x00, 0x00, 0x00, 0x00}; 
    uint16_t expected = 0;
    uint16_t result = calculatePartsPerMil(test_packet);
    TEST_ASSERT_EQUAL_UINT16(expected, result);
}
void test_packet_incomplete(void) {
    uint8_t partial_packet[] = {0xFF, 0x86}; 
    for (int i = 0; i < sizeof(partial_packet); i++) {
        usart3_co2_rx_handler(partial_packet[i]);
    }
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, new_co2_data_available, "Data should not be available with incomplete packet");
}
void test_packet_error(void) {
    uint8_t error_packet[] = {0xFF, 0x86, 0x01, 0x9A, 0x41, 0xFF, 0x00}; // Incorrect checksum deliberately
    for (int i = 0; i < sizeof(error_packet); i++) {
        usart3_co2_rx_handler(error_packet[i]);
    }
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, new_co2_data_available, "Data should not be available with erroneous content");
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

    RUN_TEST(test_checksum2_correct);
    RUN_TEST(test_checksum2_zeroes);
    RUN_TEST(test_checksum2_max);
    RUN_TEST(test_calculatePartsPerMil_normal);
    RUN_TEST(test_calculatePartsPerMil_null_pointer);
    RUN_TEST(test_calculatePartsPerMil_max);
    RUN_TEST(test_calculatePartsPerMil_min);
    RUN_TEST(test_packet_incomplete);
    RUN_TEST(test_packet_error);
    
    return UNITY_END();
}
