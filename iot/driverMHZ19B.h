// Driver for Co2 sensor

#ifndef DRIVERMHZ19B_H 
#define DRIVERMHZ19B_H

#include <stdint.h>
#define Co2SensorRead 0x86
#define response_size 9

void WHZ19B_init(void);
int WHZ19B_readCO2(void);
void command(uint8_t* command_one, uint8_t command_two);
uint8_t checksum(uint8_t* packetsize);
int responseByte(uint8_t* response);

#endif // DRIVERMHZ19B_H