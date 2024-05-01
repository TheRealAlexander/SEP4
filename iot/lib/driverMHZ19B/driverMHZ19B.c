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

uint8_t rx_buffer[7];
uint8_t rx_count = 0;

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
void reset_rx_buffer(){
  memset(rx_buffer, 0, sizeof(rx_buffer)); // Clear the buffer contents
    rx_count = 0; // Reset the count of bytes in the buffer
    send_to_pc("\nBuffer reset.\n");
}void byte_process(uint8_t byte){
   // Check if a new packet is starting
    if (byte == 0xFF && rx_count == 0) {
        // Start of a new packet
        rx_buffer[rx_count++] = byte;
    } else if (rx_count > 0) {
        // Add the byte to the buffer if there's space
        if (rx_count < sizeof(rx_buffer)) {
            rx_buffer[rx_count++] = byte;

            // Check if we have received a full packet
            if (rx_count == sizeof(rx_buffer)) {
                // Calculate the checksum
                uint8_t calculated_checksum = checksum(rx_buffer);

                // Verify checksum
                if (calculated_checksum == rx_buffer[6]) {  // Assuming the checksum byte is at index 6
                    // If checksum is correct, process the data
                    process_co2_data();
                } else {
                    // If checksum fails, log the error and reset the buffer
                    send_to_pc("Checksum failed. Packet discarded.\n");
                }

                // Always reset the buffer after processing or discarding
                reset_rx_buffer();
            }
        } else {
            send_to_pc("Buffer overflow detected. Buffer reset.\n");
            reset_rx_buffer(); // Reset on overflow to avoid processing garbage data
        }
    }
}
void usart3_co2_rx_handler(uint8_t received_byte) {
   byte_process(received_byte);
}

void process_co2_data() {
   send_to_pc("\nProcessing CO2 data...\n");
    uint8_t saved_rx_buffer[sizeof(rx_buffer)];
    memcpy(saved_rx_buffer, rx_buffer, sizeof(rx_buffer));
    uint16_t co2_concentration = calculatePartsPerMil(rx_buffer);
    latest_co2_concentration = co2_concentration;  // Update global variable
    new_co2_data_available = true;

    // Format and send the CO2 concentration to the PC
    char debug_msg[128];
    snprintf(debug_msg, sizeof(debug_msg), "CO2 Concentration: %u ppm\n", co2_concentration);
    send_to_pc(debug_msg);
}

uint8_t checksum(uint8_t* packet) {
  char debug_msg[256] = "Bytes for checksum calculation: ";  // Initialize with initial message
    char byte_msg[10];

    // Adjusted to show all bytes except the start marker and the checksum itself
    for (int i = 0; i < 6; i++) {  
        snprintf(byte_msg, sizeof(byte_msg), "%02X ", packet[i]);
        strcat(debug_msg, byte_msg);
    }
    strcat(debug_msg, "\n");
    //send_to_pc(debug_msg);  // Send the compiled debug message

    //send_to_pc("Calculating checksum...\n");
    uint8_t sum = 0;
    // Calculate checksum from bytes between the initial and final markers
    for (int i = 1; i < 6; i++) {
        sum += packet[i];
    }
    uint8_t calculatedChecksum = 0xFF - sum + 1;

    snprintf(debug_msg, sizeof(debug_msg), "Expected checksum: %02X, Calculated checksum: %02X\n", packet[6], calculatedChecksum);
    send_to_pc(debug_msg);

    if (calculatedChecksum == packet[6]) {
        send_to_pc("Checksum correct. Processing packet...\n");
        return true;
    } else {
        send_to_pc("Checksum failed.\n");
        return false;
    }
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

    return co2_concentration;
}
uint8_t checksum2(uint8_t* packet) {
    uint8_t sum = 0;
    for (int i = 1; i < 8; i++) {
        sum += packet[i];
    }
    return 0xFF - sum + 1;
}
void send_co2_command(uint8_t command_type) {
    send_to_pc("Sending CO2 command...\n");
    uint8_t buf[9] = {0};
    
    // read co2 concentration
    buf[0] = 0xff; 
    buf[1] = 0x01;
    buf[2] = command_type;
    buf[3] = 0x00;
    buf[4] = 0x00;
    buf[5] = 0x00;
    buf[6] = 0x00;
    buf[7] = 0x00;
    buf[8] = checksum2(buf);
     // Calculate checksum, excluding the position of the checksum itself

    uart_send_array_blocking(USART_3, buf, sizeof(buf)); // Send the command via USART
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
            // Handle zero point calibration response
            send_to_pc("Zero point calibration process completed.\n");
            break;

        case SPAN_POINT_CALIBRATION:
            // Handle span point calibration response
            send_to_pc("Span point calibration process completed.\n");
            break;

        default:
            // Handle unknown packet types
            send_to_pc("Received packet with unknown command type.\n");
            break;
    }
    
}
