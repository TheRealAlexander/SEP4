#include "unity.h"
#include "fff.h"
#include "driverMHZ19B.h"

// Declare the fake functions using fff.h
DEFINE_FFF_GLOBALS;
FAKE_VOID_FUNC(uart_send_array_blocking, uint8_t, const uint8_t*, size_t);

// This should match the actual function prototypes you have
void setUp(void) {
    RESET_FAKE(uart_send_array_blocking);
    FFF_RESET_HISTORY();
}

void tearDown(void) {
    // Cleanup function can be added here
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