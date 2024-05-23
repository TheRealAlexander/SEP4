#include "RTC.h"
#include <util/delay.h>

// DS1320 Registers
#define DS1320_SECONDS 0x00
#define DS1320_MINUTES 0x01
#define DS1320_HOURS 0x02
#define DS1320_DAY 0x03
#define DS1320_DATE 0x04
#define DS1320_MONTH 0x05
#define DS1320_YEAR 0x06
#define DS1320_CONTROL 0x07

// Macro to set a specific bit in a register
#define SET_BIT(reg, bit) (reg |= (1 << bit))

// Macro to clear a specific bit in a register
#define CLEAR_BIT(reg, bit) (reg &= ~(1 << bit))

// Function prototypes for internal use
void i2c_start(void);
void i2c_stop(void);
void i2c_write_byte(uint8_t data);
uint8_t i2c_read_byte(uint8_t ack);
uint8_t bcdToDec(uint8_t val);
uint8_t decToBcd(uint8_t val);
uint32_t unixToDateTime(uint32_t unix_timestamp, uint16_t *year, uint8_t *month, 
                       uint8_t *date, uint8_t *day, uint8_t *hours, 
                       uint8_t *minutes, uint8_t *seconds);
uint32_t dateTimeToUnix(uint16_t year, uint8_t month, uint8_t date, uint8_t hours,
                       uint8_t minutes, uint8_t seconds);

// I2C initialization
void i2c_init(void) {
  // Set I2C pins to output mode
  SET_BIT(DDRL, I2C_CLK);
  SET_BIT(DDRL, I2C_DAT);

  // Set I2C pins to HIGH (idle state)
  SET_BIT(PORTL, I2C_CLK);
  SET_BIT(PORTL, I2C_DAT);
}

// Start I2C communication
void i2c_start(void) {
  SET_BIT(PORTL, I2C_DAT); 
  _delay_us(1);
  SET_BIT(PORTL, I2C_CLK); 
  _delay_us(1);
  CLEAR_BIT(PORTL, I2C_DAT); 
  _delay_us(1);
  CLEAR_BIT(PORTL, I2C_CLK); 
  _delay_us(1);
}

// Stop I2C communication
void i2c_stop(void) {
  CLEAR_BIT(PORTL, I2C_DAT); 
  _delay_us(1);
  SET_BIT(PORTL, I2C_CLK);
  _delay_us(1);
  SET_BIT(PORTL, I2C_DAT); 
  _delay_us(1);
}

// Write a byte to I2C bus
void i2c_write_byte(uint8_t data) {
  for (uint8_t i = 0; i < 8; i++) {
    if (data & 0x80) {
      SET_BIT(PORTL, I2C_DAT); 
    } else {
      CLEAR_BIT(PORTL, I2C_DAT); 
    }
    _delay_us(1);
    SET_BIT(PORTL, I2C_CLK); 
    _delay_us(1);
    CLEAR_BIT(PORTL, I2C_CLK); 
    _delay_us(1);
    data <<= 1;
  }

  // Get acknowledge
  SET_BIT(PORTL, I2C_DAT); 
  _delay_us(1);
  SET_BIT(PORTL, I2C_CLK); 
  _delay_us(1);
  CLEAR_BIT(PORTL, I2C_CLK); 
  _delay_us(1);
}

// Read a byte from I2C bus
uint8_t i2c_read_byte(uint8_t ack) {
  uint8_t data = 0;
  SET_BIT(PORTL, I2C_DAT); 

  for (uint8_t i = 0; i < 8; i++) {
    _delay_us(1);
    SET_BIT(PORTL, I2C_CLK); 
    _delay_us(1);
    data <<= 1;
    if (PINL & (1 << I2C_DAT)) { 
      data |= 1;
    }
    CLEAR_BIT(PORTL, I2C_CLK);
    _delay_us(1);
  }

  // Send acknowledge
  if (ack) {
    CLEAR_BIT(PORTL, I2C_DAT);
  } else {
    SET_BIT(PORTL, I2C_DAT);
  }
  _delay_us(1);
  SET_BIT(PORTL, I2C_CLK);
  _delay_us(1);
  CLEAR_BIT(PORTL, I2C_CLK); 
  _delay_us(1);
  SET_BIT(PORTL, I2C_DAT); 
  return data;
}


// Set the date and time on the DS1320 using a Unix timestamp
void DS1320_setDateTime(uint32_t unix_timestamp) {
  uint16_t year;
  uint8_t month, date, day, hours, minutes, seconds;

  unixToDateTime(unix_timestamp, &year, &month, &date, &day, &hours, &minutes, &seconds);

  i2c_start();
  i2c_write_byte(DS1320_ADDRESS << 1);
  i2c_write_byte(DS1320_SECONDS);
  i2c_write_byte(decToBcd(seconds));
  i2c_write_byte(decToBcd(minutes));
  i2c_write_byte(decToBcd(hours));
  i2c_write_byte(decToBcd(day));
  i2c_write_byte(decToBcd(date));
  i2c_write_byte(decToBcd(month));
  i2c_write_byte(decToBcd(year - 2000));
  i2c_write_byte(0x00); 
  i2c_stop();
}

// Get the date and time from the DS1320 and return as a Unix timestamp
uint32_t DS1320_getDateTime(void) {
  uint16_t year;
  uint8_t month, date, day, hours, minutes, seconds;

  i2c_start();
  i2c_write_byte(DS1320_ADDRESS << 1); 
  i2c_write_byte(DS1320_SECONDS);
  i2c_start();
  i2c_write_byte((DS1320_ADDRESS << 1) | 1);
  seconds = bcdToDec(i2c_read_byte(1)); 
  minutes = bcdToDec(i2c_read_byte(1));
  hours = bcdToDec(i2c_read_byte(1));
  day = bcdToDec(i2c_read_byte(1));
  date = bcdToDec(i2c_read_byte(1));
  month = bcdToDec(i2c_read_byte(1));
  year = bcdToDec(i2c_read_byte(0)); 
  i2c_stop();

  year += 2000;

  return dateTimeToUnix(year, month, date, hours, minutes, seconds);
}

// Convert Binary Coded Decimal (BCD) to Decimal
uint8_t bcdToDec(uint8_t val) {
  return ((val / 16 * 10) + (val % 16));
}

// Convert Decimal to Binary Coded Decimal (BCD)
uint8_t decToBcd(uint8_t val) {
  return ((val / 10 * 16) + (val % 10));
}

// Convert Unix timestamp to individual time components
uint32_t unixToDateTime(uint32_t unix_timestamp, uint16_t *year, uint8_t *month, 
                       uint8_t *date, uint8_t *day, uint8_t *hours, 
                       uint8_t *minutes, uint8_t *seconds) {

  const uint32_t secondsPerDay = 86400;
  const uint32_t secondsPerHour = 3600;
  const uint32_t secondsPerMinute = 60;

  uint32_t daysSinceEpoch = unix_timestamp / secondsPerDay;
  uint8_t daysOfWeek = (daysSinceEpoch + 4) % 7;

  // Calculate year
  uint16_t currentYear = 1970;
  uint32_t daysInYear;
  while (daysSinceEpoch >= (daysInYear = (currentYear % 4 == 0 && (currentYear % 100 != 0 || currentYear % 400 == 0)) ? 366 : 365)) {
    daysSinceEpoch -= daysInYear;
    currentYear++;
  }
  *year = currentYear; 

  // Calculate month
  static const uint8_t daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  uint8_t currentMonth = 0;
  while (daysSinceEpoch >= daysInMonth[currentMonth]) {
    daysSinceEpoch -= daysInMonth[currentMonth];
    currentMonth++;
  }
  *month = currentMonth + 1; 

  // Calculate day
  *date = daysSinceEpoch + 1;

  // Calculate hours, minutes, seconds
  *hours = (unix_timestamp % secondsPerDay) / secondsPerHour;
  *minutes = (unix_timestamp % secondsPerHour) / secondsPerMinute;
  *seconds = unix_timestamp % secondsPerMinute;

  *day = daysOfWeek; 

  return 0; 
}

// Convert individual time components to Unix timestamp 
uint32_t dateTimeToUnix(uint16_t year, uint8_t month, uint8_t date, uint8_t hours,
                       uint8_t minutes, uint8_t seconds) {

  if (month < 1 || month > 12 || date < 1 || date > 31 || 
      hours > 23 || minutes > 59 || seconds > 59) {
    return 0;
  }

  uint32_t unixTimestamp = 0;

  // Years since 1970
  unixTimestamp = (year - 1970) * 31536000; 
  unixTimestamp += ((year - 1969) / 4) * 86400;
  if (year > 2000 && (year - 2000) % 100 == 0 && (year - 2000) % 400 != 0) {
    unixTimestamp -= 86400;
  }

  // Months 
  static const uint8_t daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  for (uint8_t currentMonth = 1; currentMonth < month; ++currentMonth) {
    unixTimestamp += daysInMonth[currentMonth - 1] * 86400;
  }
  // Adjust for leap year
  if (month > 2 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
    unixTimestamp += 86400; 
  }

  unixTimestamp += (date - 1) * 86400;

  unixTimestamp += hours * 3600;
  unixTimestamp += minutes * 60;
  unixTimestamp += seconds;

  return unixTimestamp;
}
