#include "wifi.h"
#include <util/delay.h>
#include <stdlib.h>
#include "wifi.c"

#include "uart.h"

void send_to_pc(char *s) {
    int len = strlen(s);
    uart_send_array_blocking(USART_0, s, len);
}


char *wifi_recv_buffer[1024];

void wifi_recv_callback(void) {
    send_to_pc("We recv something\r\n");

    send_to_pc(wifi_recv_buffer);
    send_to_pc("\r\n");
}

int main(){

    uart_init(USART_0, 9600, NULL);

    send_to_pc("Hello, from Rune. Is there anybody out there?");


    wifi_init();
    wifi_command_join_AP("Fatema - iPhone", "12345678"); //your hotspot
    // wifi_command_create_TCP_connection("172.20.10.5", 23, wifi_recv_callback, wifi_recv_buffer); //back form server to 
    //wifi_command_create_TCP_connection("142.250.74.14", 80, wifi_recv_callback, wifi_recv_buffer); //back form server to client 
    wifi_command_create_TCP_connection("3.221.38.252", 80, wifi_recv_callback, wifi_recv_buffer);

    

    char *http_req = 

"GET /get HTTP/1.0\r\n"
"Host: httpbin.org\r\n"
"Accept: */*\r\n"
"Connection: Close\r\n"
"\r\n";

    while (1)
    {
        wifi_command_TCP_transmit(http_req, strlen(http_req));//send data to se that alle thing works "Hello form arduino over LAN\N",28
        _delay_ms(2000);
    }
        // Opretter en instans af DHT strukturen
  
}
