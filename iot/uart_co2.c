#include "uart.h"
#include <avr/io.h>

void uart_send_byte(uint8_t data){
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1<< UDRE0))); 
    UDR0 = data;
}

uint8_t uart_receive_byte(void){
    // Receive data
    while (!(UCSR0A & (1 << RXC0)));    
    return UDR0;
}