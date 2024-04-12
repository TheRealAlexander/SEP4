#ifndef UART_CO2_H
#define UART_CO2_H
#pragma once
#include <stdint.h>



void uart_send_byte(uint8_t data);
uint8_t uart_receive_byte(void);

#endif // UART_CO2_H