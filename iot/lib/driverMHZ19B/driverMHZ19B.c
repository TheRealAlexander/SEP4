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

void send_to_pc(char *s) {
    int len = strlen(s);
    uart_send_array_blocking(USART_0, (uint8_t*)s, len); // Utilize USART_0 to send data to PC
}

void WHZ19B_init(void) {
    uint16_t ubrr_value = (F_CPU / (16UL * 9600)) - 1;
    UBRR3H = (uint8_t)(ubrr_value >> 8);
    UBRR3L = (uint8_t)ubrr_value;
    UCSR3B = (1 << RXEN3) | (1 << TXEN3);
    UCSR3C = (1 << UCSZ31) | (1 << UCSZ30);
}

void usart3_co2_rx_handler(uint8_t received_byte) {
    static bool expect_new_packet = true;

    if (received_byte == 0xFF && expect_new_packet) {
        rx_count = 0;
        rx_buffer[rx_count++] = received_byte;
        send_to_pc("New packet started.\n");
        expect_new_packet = false;
    } else if (rx_count < 9) {
        rx_buffer[rx_count++] = received_byte;
        char debug_msg[30];
        snprintf(debug_msg, 30, "Byte received: %02X\n", received_byte);
        send_to_pc(debug_msg);
    }

    if (rx_count >= 9) {
        process_co2_data(); // Assuming this processes and validates the packet, including checksum
        expect_new_packet = true;
    }
}

void process_co2_data() {
    send_to_pc("Processing CO2 data...\n");
    if (checksum(rx_buffer) == rx_buffer[8]) {
        latest_co2_concentration = (rx_buffer[2] << 8) + rx_buffer[3];
        new_co2_data_available = true;
        send_to_pc("CO2 data valid.\n");
    } else {
        latest_co2_concentration = -1;
        send_to_pc("Checksum failed.\n");
    }
}

uint8_t checksum(uint8_t* packet) {
    char debug_msg[128] = "Bytes for checksum calculation: ";  // Initialize with initial message
    char byte_msg[10];

    for (int i = 1; i < 8; i++) {  // Assume byte 0 is start, and byte 8 is the checksum itself
        snprintf(byte_msg, sizeof(byte_msg), "%02X ", packet[i]);  // Convert byte to hex string
        strcat(debug_msg, byte_msg);  // Append to the debug message
    }
    strcat(debug_msg, "\n");
    send_to_pc(debug_msg);  // Send the compiled debug message

    // Now calculate the checksum
    send_to_pc("Calculating checksum...\n");
    uint8_t sum = 0;
    for (int i = 1; i < 8; i++) {
        sum += packet[i];
    }
    uint8_t calculateChecksum = 0xFF - sum + 1;

    // Output the result and compare to expected
    snprintf(debug_msg, sizeof(debug_msg), "Expected checksum: %02X, Calculated checksum: %02X\n", packet[8], calculateChecksum);
    send_to_pc(debug_msg);

    if (calculateChecksum == packet[8]) {
        send_to_pc("Checksum correct. Processing packet...\n");
        process_packet(packet);  // Call process_packet directly if checksum is correct
    } else {
        send_to_pc("Checksum failed.\n");
    }

    return calculateChecksum;
}
uint16_t calculatePartsPerMil(uint8_t *packet) {
    if (!packet) {
        send_to_pc("Invalid Packet.\n");
        return 0;  // Error code or invalid concentration value
    }
    uint8_t highByte = packet[2]; 
    uint8_t lowByte = packet[3];

    uint16_t co2_concentration = highByte * 256 + lowByte;

    char debug_msg[50];
    snprintf(debug_msg, sizeof(debug_msg), "High byte: %02X, Low byte: %02X, CO2 Concentration: %u ppm\n",
             highByte, lowByte, co2_concentration);
    send_to_pc(debug_msg);

    return co2_concentration;
}

void send_co2_command(uint8_t command_type) {
    send_to_pc("Sending CO2 command...\n");
    uint8_t buf[9] = {0xff, 0x01, command_type, 0x00, 0x00, 0x00, 0x00, 0x00, checksum(buf)};
    buf[8] = checksum(buf);  

    char debug_msg[128];
    for (int i = 0; i < sizeof(buf); i++) {
        snprintf(debug_msg, sizeof(debug_msg), "%02x ", buf[i]);
        send_to_pc(debug_msg);
    }
    send_to_pc("\n");

    uart_send_array_blocking(USART_3, buf, sizeof(buf));
}

void sendZeroPointCalibration(void) {
   
    send_co2_command(ZERO_POINT_CALIBRATION);
}

void sendSpanPointCalibration(uint8_t high_byte, uint8_t low_byte) {
    send_co2_command(SPAN_POINT_CALIBRATION);
}

void process_packet(uint8_t *packet) {
    if (!packet) {
        send_to_pc("Invalid packet received.\n");
        return;
    }

    uint8_t command_type = packet[2];

    switch(command_type) {
        case Co2SensorRead:
            // Process CO2 concentration reading
            {
                uint16_t co2_concentration = calculatePartsPerMil(packet);
                char debug_msg[50];
                snprintf(debug_msg, sizeof(debug_msg), "CO2 Concentration: %u ppm\n", co2_concentration);
                send_to_pc(debug_msg);
            }
            break;

        case ZERO_POINT_CALIBRATION:
            // Handle zero point response
            send_to_pc("Zero point calibration process completed.\n");
            break;

        case SPAN_POINT_CALIBRATION:
            // Handle span point response
            send_to_pc("Span point calibration process completed.\n");
            break;

        default:
            // Handle unknown packet types
            send_to_pc("Received packet with unknown command type.\n");
            break;
    }
    
}
