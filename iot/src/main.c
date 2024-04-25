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

extern volatile int latest_co2_concentration;
extern volatile bool new_co2_data_available;

static uint8_t rx_buffer[9];
static uint8_t rx_count = 0;

void WHZ19B_init(void);
void usart3_co2_rx_handler(uint8_t received_byte);
void send_to_pc(char *s);
void process_co2_data(void);
uint8_t checksum(uint8_t* packet);
void send_co2_command(uint8_t command_type);

int main() {
  
    send_to_pc("Initializing WHZ19B...\n");
    uart_init(USART_3, 9600, usart3_co2_rx_handler);
    uart_init(USART_0, 9600, NULL);
    // Initialize the CO2 sensor
    WHZ19B_init();

 while (1) {
        // Send a command to the sensor to read CO2 concentration
        send_co2_command(Co2SensorRead);
         send_to_pc("+++++++++++++++++++++++++++++\n");
        _delay_ms(200);  // Delay for sensor

        // Process received data if available
        if (new_co2_data_available) {
            process_packet(rx_buffer);
            new_co2_data_available = false;  // Reset the flag after processing
        } else {
            send_to_pc("Waiting for new CO2 data...\n");
        }
    }

    return 0; 
}