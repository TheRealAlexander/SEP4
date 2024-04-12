#include "driverMHZ19B.h"
#include "uart.h"
#include <util/delay.h>
#include <avr/io.h>
#include "uart_co2.h"
#define BAUD_RATE 9600 // Set the baud rate for the specifications of the datasheet which is 9600
#define F_CPU 16000000UL 
#define BAUD_PRESCALE (((F_CPU / (BAUD_RATE * 16UL))) - 1)
#define ZERO_POINT_CALIBRATION 0x87
#define SPAN_POINT_CALIBRATION 0x88
// This function helps to calculate the amount of co2.
//It loops through the 8 bit length string and adds it together
// to find the final integer value. This is found through subtraction 
// The hex val with the final sum. 
uint8_t checksum(uint8_t* packet){
    uint8_t sum = 0;
    for(int i = 1; i < response_size - 1; i++){
        sum += packet[i];
    }
    return 0xFF - sum + 1;
}
// This function is constructing the command we are sending to the sensor. The first two bytes, are standard, while the third indicates which command is needed for
// the sensor. Byte 3 - 8 just need to have a default value of 0. This can be found in the datasheet. 
void command(uint8_t* command_one, uint8_t command_two){
    command_one[0] = 0xFF;
    command_one[1] = 0x01;
    command_one[2] = command_two;
    for (int i = 3; i < 8; i++){
        command_one[i] = 0x00;
    }
    command_one[8] = checksum(command_one);

}
int responseByte(uint8_t* response){
    if(response[1] != Co2SensorRead){
        return -1;  // The first byte sent back must match 0x86 otherwise it is not a proper response
    }
    if( checksum(response) != response[8]){
        return -2;   // There is a checksum error
    }
    return (response[2] << 8) + response[3]; // This essentially merges the two bytes to make a 16 bit number. Because Co2 has the unit of parts per million, 
    // We need to have a return value that can store the high number, it outputs. // The response[2] << 8 just shifts the bits so that we get 2⁸ 

} // This function just reads the co2sensor and sends the captured data back. 
int WHZ19B_readCO2(void){
    uint8_t com[9];
    uint8_t respond[response_size];

    command(com, Co2SensorRead);
    for (int i = 0; i < response_size; i++){
        uart_send_blocking(USART_0, com[i]); 
    }
    _delay_ms(10);

for (int i = 0; i < response_size; i++){
respond[i] = uart_receive_byte();
}
return responseByte(respond);
}
// This function just sends the command to do Zero Point Calibration
void sendZeroPointCalibration(void) {
    uint8_t zero_point_command[9];
    command(zero_point_command, ZERO_POINT_CALIBRATION);

    for (int i = 0; i < 9; i++) {
        uart_send_blocking(USART_0, zero_point_command[i]);
    }
    _delay_ms(100);
}
void sendSpanPointCalibration(uint8_t high_byte, uint8_t low_byte) {
    uint8_t span_point_command[9];
    command(span_point_command, SPAN_POINT_CALIBRATION);
    
    span_point_command[3] = high_byte;
    span_point_command[4] = low_byte;
    
    span_point_command[8] = checksum(span_point_command);
    
    for (int i = 0; i < 9; i++) {
        uart_send_blocking(USART_0, span_point_command[i]);
    }
    
    _delay_ms(100);
}

void uart_rx_callback(uint8_t data) {
    // Handle received data
    }



void WHZ19B_init(void){
    uart_init(USART_0, 9600, uart_rx_callback);
      UBRR0 = (uint8_t)(BAUD_PRESCALE >> 8);
      UBRR0L = (uint8_t)(BAUD_PRESCALE);
      // Enable receiver and transmitter
      UCSR0B = (1 << RXEN0) | (1 << TXEN0);
      // Set frame format: 8 data bits, no parity, 1 stop bit
      UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
