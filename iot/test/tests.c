////////////////////////////////////////////////////////////////
// Include dependencies

#include "../lib/includes.h"

////////////////////////////////////////////////////////////////
// CO2 tests

static void test_checksum2_correct(void) {
    uint8_t test_packet[] = { 0xFF, 0x86, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };
    uint8_t expected_checksum = 0x79;

    uint8_t calculated_checksum = checksum2(test_packet);
    assert_hex8(expected_checksum, calculated_checksum);
}

static void test_checksum2_zeroes(void) {
    uint8_t test_packet[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    uint8_t expected_checksum = 0x00;
    uint8_t calculated_checksum = checksum2(test_packet);
    assert_hex8(expected_checksum, calculated_checksum);
}

static void test_checksum2_max(void) {
    uint8_t test_packet[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    uint8_t expected_checksum = 0x07;
    uint8_t calculated_checksum = checksum2(test_packet);
    assert_hex8(expected_checksum, calculated_checksum);
}

static void test_calculatePartsPerMil_normal(void) {
    uint8_t test_packet[] = { 0x00, 0x00, 0x04, 0xD2 };
    uint16_t expected = 1234;
    uint16_t result = calculatePartsPerMil(test_packet);
    assert_uint16(expected, result);
}

static void test_calculatePartsPerMil_null_pointer(void) {
    uint16_t result = calculatePartsPerMil(NULL);
    assert_uint16(0, result);
}

static void test_calculatePartsPerMil_max(void) {
    uint8_t test_packet[] = { 0x00, 0x00, 0xFF, 0xFF };
    uint16_t expected = 65535;
    uint16_t result = calculatePartsPerMil(test_packet);
    assert_uint16(expected, result);
}

static void test_calculatePartsPerMil_min(void) {
    uint8_t test_packet[] = { 0x00, 0x00, 0x00, 0x00 };
    uint16_t expected = 0;
    uint16_t result = calculatePartsPerMil(test_packet);
    assert_uint16(expected, result);
}

static void test_packet_incomplete(void) {
    uint8_t partial_packet[] = { 0xFF, 0x86 };
    for (int i = 0; i < isizeof(partial_packet); i++) {
        usart3_co2_rx_handler(partial_packet[i]);
    }
    assert_uint8_msg(0, new_co2_data_available, "Data should not be available with incomplete packet");
}

static void test_packet_error(void) {
    uint8_t error_packet[] = { 0xFF, 0x86, 0x01, 0x9A, 0x41, 0xFF, 0x00 }; // Incorrect checksum deliberately
    for (int i = 0; i < isizeof(error_packet); i++) {
        usart3_co2_rx_handler(error_packet[i]);
    }
    assert_uint8_msg(0, new_co2_data_available, "Data should not be available with erroneous content");
}

////////////////////////////////////////////////////////////////
// Display tests

// Fake function
int tone_play_final_fantasy_victory_fake_call_count;
void tone_play_final_fantasy_victory(void) { tone_play_final_fantasy_victory_fake_call_count += 1; }

void test_display_setup(void) {
    tone_play_final_fantasy_victory_fake_call_count = 0;
    teamscore_a = 0;
    teamscore_b = 0;
}

void test_display_teardown(void) {
}

void test_checkScoreAPlus_IncrementsCorrectly(void) {
    checkScoreAPlus();
    assert_int(15, teamscore_a);
    checkScoreAPlus();
    assert_int(30, teamscore_a);
    checkScoreAPlus();
    assert_int(40, teamscore_a);
    checkScoreAPlus();
    assert_int(41, teamscore_a);
    checkScoreAPlus();
    assert_int(42, teamscore_a);
    assert_int(1, tone_play_final_fantasy_victory_fake_call_count);
}

void test_checkScoreBPlus_FromZero(void) {
    checkScoreBPlus();
    assert_int(15, teamscore_b);
    checkScoreBPlus();
    assert_int(30, teamscore_b);
    checkScoreBPlus();
    assert_int(40, teamscore_b);
    checkScoreBPlus();
    assert_int(41, teamscore_b);
    checkScoreBPlus();
    assert_int(42, teamscore_b);
    assert_int(1, tone_play_final_fantasy_victory_fake_call_count);
}


void test_checkScoreAMinus_From40to30(void) {
    teamscore_a = 40;
    checkScoreAMinus();
    assert_int(30, teamscore_a);
    // assert_int(1, setScoreTo40_fake.call_count);
}


void test_resetScores_TriggersCorrectFunctions(void) {
    resetScore();
    assert_int(0, teamscore_a);
    assert_int(0, teamscore_b);
}

void test_decrementScore_FromAdvantageToDeuce(void) {
    teamscore_a = 41;
    checkScoreAMinus();
    assert_int(40, teamscore_a);
}

void test_incrementScore_DoesNotExceedVictory(void) {
    teamscore_a = 42;
    checkScoreAPlus();

    assert_int(42, teamscore_a);
    assert_int(0, tone_play_final_fantasy_victory_fake_call_count);
}


void test_checkScoreBMinus_DeincrementsCorrectly(void) {
    teamscore_b = 30;
    checkScoreBMinus();
    assert_int(15, teamscore_b);
    checkScoreBMinus();
    assert_int(0, teamscore_b);
}

void test_resetScores(void) {
    setScoreTo40();
    resetScore();
    assert_int(0, teamscore_a);
    assert_int(0, teamscore_b);
}
////////////////////////////////////////////////////////////////
// Test runner

int main(void) {
    print_init();

    ////////////////////////////////////////////////////////////////
    // Run CO2 tests

    test_begin("co2", NULL, NULL);
    test_run(test_checksum2_correct);
    test_run(test_checksum2_zeroes);
    test_run(test_checksum2_max);
    test_run(test_calculatePartsPerMil_normal);
    test_run(test_calculatePartsPerMil_null_pointer);
    test_run(test_calculatePartsPerMil_max);
    test_run(test_calculatePartsPerMil_min);
    test_run(test_packet_incomplete);
    test_run(test_packet_error);
    test_end();

    ////////////////////////////////////////////////////////////////
    // Run display tests

    test_begin("display", test_display_setup, test_display_teardown);
    test_run(test_checkScoreAPlus_IncrementsCorrectly);
    test_run(test_checkScoreBPlus_FromZero);
    test_run(test_checkScoreAMinus_From40to30);
    test_run(test_resetScores_TriggersCorrectFunctions);
    test_run(test_decrementScore_FromAdvantageToDeuce);
    test_run(test_incrementScore_DoesNotExceedVictory);
    test_run(test_checkScoreBMinus_DeincrementsCorrectly);
    test_run(test_resetScores);
    test_end();

    ////////////////////////////////////////////////////////////////
    // Print results

    if (g_test.any_tests_failed_during_whole_runtime) {
        send_to_pc(ANSI_FG_RED);
        send_to_pc("Not all tests succceded :(\n\n");
        send_to_pc(ANSI_RESET);
        return 1;
    } else {
        send_to_pc(ANSI_FG_BRIGHT_GREEN);
        send_to_pc("All tests succceded \\o/\n\n");
        send_to_pc(ANSI_RESET);
        return 0;
    }
}
