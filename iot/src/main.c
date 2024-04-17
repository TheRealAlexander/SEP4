#include "uart.h"
#include "dht11.h"
#include "periodic_task.h"
#include <stdio.h>
#define F_CPU 16000000UL  // Adjust this according to your microcontroller's clock
#include <util/delay.h>

// Funktion til at sende data som JSON-format
static void print_json(int humid_int, int humid_dec, int temp_int, int temp_dec) {
    char json[128] = {0};
    int len = sprintf(json, "{\"humidity\": \"%d.%d%%\", \"temperature\": \"%d.%d°C\"}\r\n",
                      humid_int, humid_dec, temp_int, temp_dec);
    for (int i = 0; i < len; i++) {
        uart_send_blocking(USART_0, json[i]);
    }
}

static void call_me_every_ms(void) {
    static int counter_ms = 0;
    counter_ms++;
}

int main() {
    uart_init(USART_0, 9600, NULL);
    periodic_task_init_a(call_me_every_ms, 1);

    while(1) {
        uint8_t a = 0, b = 0, c = 0, d = 0;
        if (dht11_get(&a, &b, &c, &d) == DHT11_OK) {
            print_json(a, b, c, d);
        }
        _delay_ms(1000); // Just as an example delay
    }
    return 0;
}
