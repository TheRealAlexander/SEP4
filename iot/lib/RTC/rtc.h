#ifndef RTC_H
#define RTC_H

#include <avr/io.h>
#include <stdint.h>

// Define I2C pins 
#define I2C_CLK 42 // PL7 
#define I2C_DAT 43 // PL6 

// DS1320 Registers
#define DS1320_ADDRESS 0x68

// Function prototypes
void i2c_init(void);
void DS1320_setDateTime(uint32_t unix_timestamp);
uint32_t DS1320_getDateTime(void);

#endif
