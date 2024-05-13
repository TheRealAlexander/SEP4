#ifndef DRIVERMHZ19B_H
#define DRIVERMHZ19B_H

#include <stdint.h>
#include <stdbool.h>

#define Co2SensorRead 0x86
#define ZERO_POINT_CALIBRATION 0x87
#define SPAN_POINT_CALIBRATION 0x88
#define BAUD_RATE 9600  

extern volatile int latest_co2_concentration;
extern volatile bool new_co2_data_available;
extern uint8_t rx_buffer[7];
extern uint8_t rx_count;

// Function declarations that are universal
uint8_t checksum(uint8_t* packet);
void send_to_pc(char *s);

#ifndef PLATFORMIO_UNIT_TEST
// Exclude these from native unit testing environment
void usart3_co2_rx_handler(uint8_t received_byte);  
void process_co2_data(void);
void WHZ19B_init(void);
void WHZ19B_readCO2(void);
void command(uint8_t* commandBuffer, uint8_t commandType);
void sendZeroPointCalibration(void);
void sendSpanPointCalibration(uint8_t high_byte, uint8_t low_byte);
void process_packet(uint8_t *packet);
void byte_process(uint8_t byte);
void reset_rx_buffer();
uint16_t calculatePartsPerMil(uint8_t *packet);
void send_co2_command(uint8_t command_type);
#endif // PLATFORMIO_UNIT_TEST

#endif // DRIVERMHZ19B_H