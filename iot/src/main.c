

#include "uart.h"


#include "driverMHZ19B.h"
#include <util/delay.h>
#include <stdio.h>
#include <string.h> 
#include <periodic_task.h>
#include <display_button.h>
#include <tone.h>
volatile uint16_t seconds_count = 0; // Counter for the seconds
volatile bool time_to_send_command = true;
volatile bool time_to_check_buttons = false;

void callback(uint8_t byte) {
    usart3_co2_rx_handler(byte);
}
void periodic_count_seconds() {
    seconds_count++; // Increment every time this function is called

    // Check if 20 seconds have passed
    if (seconds_count >= 10) {
        time_to_send_command = true; // Set the flag to send the command
    }
     if (seconds_count % 2 == 0) {  // Every 2 seconds
        time_to_check_buttons = true;
    }
}
static void send_co2_concentration_as_json(int co2_concentration) {
    char json[128] = {0};
    int len = sprintf(json, "{\"CO2 Concentration\": \"%d ppm\"}\r\n", co2_concentration);
    for (int i = 0; i < len; i++) {
        uart_send_blocking(USART_0, json[i]);
    }
}
int main() {
    uart_init(USART_0, 9600, 0);
    uart_init(USART_3, 9600, callback);
    tone_init();
    // Initialize your periodic task to call `periodic_count_seconds` every second
    periodic_task_init_a(periodic_count_seconds, 1000); // Assuming the driver uses milliseconds
    controller_init();
    while (1) {
        // Check if it's time to send the CO2 command
        if (time_to_send_command) {
            send_co2_command(Co2SensorRead);  // Trigger CO2 reading
            time_to_send_command = false; // Reset the flag
        }
          if (time_to_check_buttons) {
            handle_buttons();
            time_to_check_buttons = false;  
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

        _delay_ms(100);  // Small delay to prevent the loop from spinning too fast
    }
}