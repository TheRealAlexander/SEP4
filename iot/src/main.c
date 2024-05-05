#include "uart.h"
#include "wifi.h"
#include "servo.h"
#include "driverMHZ19B.h"
#include "periodic_task.h"

#include <util/delay.h>
#include <stdio.h>
#include <string.h>

volatile uint16_t seconds_count = 0; // Counter for the seconds
volatile bool time_to_send_command = true;
volatile bool new_co2_data_available = false;
int latest_co2_concentration = 0;
char wifi_recv_buffer[1024]

void usart3_co2_rx_handler(uint8_t byte) {
}

void callback(uint8_t byte) {
    usart3_co2_rx_handler(byte);
}

void periodic_count_seconds() {
    seconds_count++;
    // Check if 10 seconds have passed
    if (seconds_count >= 10) {
        time_to_send_command = true; // Set the flag to send the CO2 command
    }
}

// Sends CO2 concentration data as JSON over UART
static void send_co2_concentration_as_json(int co2_concentration) {
    char json[128] = {0};
    int len = sprintf(json, "{\"CO2 Concentration\": \"%d ppm\"}\r\n", co2_concentration);
    for (int i = 0; i < len; i++) {
        uart_send_blocking(USART_0, json[i]);
    }
}

// Send strings to PC over UART
void send_to_pc(char *s) {
    int len = strlen(s);
    uart_send_array_blocking(USART_0, s, len);
}

// Handle received WiFi data
void wifi_recv_callback(void) {
    send_to_pc("We received something:\r\n");
    send_to_pc(wifi_recv_buffer);
    send_to_pc("\r\n");

    if (strstr(wifi_recv_buffer, "\"openWindow\": true")) {
        servo_set_angle(0); // Trigger servo to open window
        send_to_pc("Command received: Open window.\r\n");
    } else if (strstr(wifi_recv_buffer, "\"openWindow\": false")) {
        servo_set_angle(180); // Trigger servo to close window
        send_to_pc("Command received: Close window.\r\n");
    }
}

int main() {
    uart_init(USART_0, 9600, 0);
    uart_init(USART_3, 9600, callback);

    send_to_pc("Hello, from Rune. Is there anybody out there?\r\n");

    servo_init();
    wifi_init();
    wifi_command_join_AP("Fatema - iPhone", "12345678");
    wifi_command_create_TCP_connection("3.221.38.252", 80, wifi_recv_callback, wifi_recv_buffer);

    periodic_task_init_a(periodic_count_seconds, 1000); // Initialize periodic task to count seconds

    char http_req[] = 
        "GET /get HTTP/1.0\r\n"
        "Host: httpbin.org\r\n"
        "Accept: */*\r\n"
        "Connection: Close\r\n"
        "\r\n";

    while (1) {
        // Check if it's time to send the CO2 command
        if (time_to_send_command) {
            send_co2_command(Co2SensorRead); // Trigger CO2 reading
            time_to_send_command = false; // Reset the flag
        }

        // Handle new CO2 data if available
        if (new_co2_data_available) {
            int current_co2_concentration = latest_co2_concentration;
            new_co2_data_available = false;  // Reset flag after reading
            send_co2_concentration_as_json(current_co2_concentration);

            seconds_count = 0; // Reset the counter
            char msg[50];
            snprintf(msg, sizeof(msg), "\nCurrent CO2 Concentration: %d ppm\n", current_co2_concentration);
            send_to_pc(msg);
        }

        wifi_command_TCP_transmit(http_req, strlen(http_req)); // Send HTTP request periodically
        _delay_ms(2000); // Delay to manage loop timing
    }
}
