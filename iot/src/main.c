

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000
#include <util/delay.h>

#include "uart.h"
#include "uart.c"
#include "dht11.h"
#include "dht11.c"
#include "periodic_task.h"
#include "periodic_task.c"

#include <stdio.h>

static void print_int(char *name, int j) {
    char msg[128] = {0};
    int len = sprintf(msg, "%s %d\r\n", name, j);
    
    for (int i = 0; i < len; i++) {
        uart_send_blocking(USART_0, msg[i]);
    }
}

static void print_int2(char *name, int heltal, int decimal) {
    char msg[128] = {0};
    int len = sprintf(msg, "%s %d,%d\r\n", name, heltal, decimal);
    
    for (int i = 0; i < len; i++) {
        uart_send_blocking(USART_0, msg[i]);
    }
}

int counter_ms = 0;

static void call_me_every_ms(void) {
    counter_ms++;
}

int main()
{
  uart_init(USART_0, 9600, NULL);
    
  periodic_task_init_a(call_me_every_ms, 1);

  while(1)
  {
        print_int("millisekunder", counter_ms);
      
        uint8_t a = 0;
        uint8_t b = 0;
        uint8_t c = 0;
        uint8_t d = 0;
        
        int result = dht11_get(&a, &b, &c, &d);
        if (result == DHT11_OK) {
            print_int2("humid", a, b);
            print_int2("temp ", c, d);
        }
  }
  return 0;
}