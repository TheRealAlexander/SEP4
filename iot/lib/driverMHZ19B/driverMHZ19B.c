#include "uart.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "includes.h"
#include "driverMHZ19B.h"
#define Co2SensorRead 0x86
#define ZERO_POINT_CALIBRATION 0x87
#define SPAN_POINT_CALIBRATION 0x88
#define BAUD_RATE 9600

volatile int latest_co2_concentration = 0;
volatile bool new_co2_data_available = false;

static uint8_t rx_buffer[9];
static uint8_t rx_count = 0;

void WHZ19B_init(void) {
    uart_init(USART_3, 9600, usart3_co2_rx_handler);
    uart_in(USART_0, 9600, NULL);

    uint16_t ubrr_value = (F_CPU / (16UL * 9600)) - 1;

    UBRR3H = (uint8_t)(ubrr_value >> 8);
    UBRR3L = (uint8_t)ubrr_value;

    UCSR3B = (1 << RXEN3) | (1 << TXEN3);

    UCSR3C = (1 << UCSZ31) | (1 << UCSZ30);
}
void usart3_co2_rx_handler(uint8_t received_byte) {
    if (rx_count < sizeof(rx_buffer)) {
        rx_buffer[rx_count] = received_byte;
        char temp[8];
        snprintf(temp, sizeof(temp), "%02x ", received_byte);
        send_to_pc(temp);
        rx_count++;
    } else {
        rx_count = 0;
    }

    if (rx_count >= sizeof(rx_buffer)) {
        rx_count = 0;
        process_co2_data();
    }
}
void send_to_pc(char *s) {
    uart_send_array_blocking(USART_0, s, strlen(s)); // Utilize USART_0 to send data to PC
}

void process_co2_data() {
    if (checksum(rx_buffer) == rx_buffer[8]) {
        latest_co2_concentration = (rx_buffer[2] << 8) + rx_buffer[3];
        new_co2_data_available = true;
    } else {
        latest_co2_concentration = -1;
    }
}

uint8_t checksum(uint8_t* packet) {
    uint8_t sum = 0;
    for (int i = 1; i < sizeof(rx_buffer) - 1; i++) {
        sum += packet[i];
    }
    return 0xFF - sum + 1;
}


void WHZ19B_readCO2(void) {
    uint8_t commandVariable[9];
    command(commandVariable, Co2SensorRead);
    uart_send_array_blocking(USART_3, command, sizeof(command)); // Send CO2 read command
    _delay_ms(10000);}


void command(uint8_t* commandBuffer, uint8_t commandType) {
    commandBuffer[0] = 0xFF;
    commandBuffer[1] = 0x01;
    commandBuffer[2] = commandType;
    for (int i = 3; i < 8; i++) {
        commandBuffer[i] = 0x00;
    }
    commandBuffer[8] = checksum(commandBuffer);
}

void sendZeroPointCalibration(void) {
    uint8_t commandVariable[9];
    command(commandVariable, ZERO_POINT_CALIBRATION);
    send_co2_command(commandVariable, sizeof(commandVariable));
}

void sendSpanPointCalibration(uint8_t high_byte, uint8_t low_byte) {
    uint8_t commandVariable[9];
    command(commandVariable, SPAN_POINT_CALIBRATION);
    commandVariable[3] = high_byte;
    commandVariable[4] = low_byte;
    commandVariable[8] = checksum(commandVariable);
    send_co2_command(commandVariable, sizeof(commandVariable));
}
