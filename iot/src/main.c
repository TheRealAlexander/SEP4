#include "wifi.h"
#include "driverMHZ19B.h"
#include <util/delay.h>
#include <stdio.h>
#include <string.h> 
#include <Arduino.h>
int main() {
    WIFI_ERROR_MESSAGE_t wifi_status;
    int co2_concentration;

    
    WHZ19B_init();

    wifi_init();
    // Connect to the WiFi network
    wifi_status = wifi_command_join_AP("WiFimodem-CA34", "8ba9e66h42");
    if (wifi_status != WIFI_OK) {
        printf("Failed to connect to WiFi AP, error code: %d\n", wifi_status);
        return -1;
    }
    printf("Connected to WiFi AP successfully.\n");
    // TCP connection
    wifi_status = wifi_command_create_TCP_connection("192.168.1.19", 1234, NULL, NULL);
    if (wifi_status != WIFI_OK) {
        printf("Failed to establish TCP connection, error code: %d\n", wifi_status);
        return -1;
    }
    printf("TCP connection established successfully.\n");
   
    while (1) {
        WHZ19B_readCO2(); // read operation

        _delay_ms(2000); 

        
        if (new_co2_data_available) {
            co2_concentration = latest_co2_concentration; // Get the latest reading
            new_co2_data_available = false; 

            char message[128];
            sprintf(message, "CO2 Concentration: %d ppm", co2_concentration);
            wifi_command_TCP_transmit((uint8_t *)message, strlen(message));
        }
    }

    return 0;
}#include "wifi.h"
#include "driverMHZ19B.h"
#include <util/delay.h>
#include <stdio.h>
#include <string.h> 
#include <Arduino.h>
int main() {
    WIFI_ERROR_MESSAGE_t wifi_status;
    int co2_concentration;

    
    WHZ19B_init();

    wifi_init();
    // Connect to the WiFi network
    wifi_status = wifi_command_join_AP("WiFimodem-CA34", "8ba9e66h42");
    if (wifi_status != WIFI_OK) {
        printf("Failed to connect to WiFi AP, error code: %d\n", wifi_status);
        return -1;
    }
    printf("Connected to WiFi AP successfully.\n");
    // TCP connection
    wifi_status = wifi_command_create_TCP_connection("192.168.1.19", 1234, NULL, NULL);
    if (wifi_status != WIFI_OK) {
        printf("Failed to establish TCP connection, error code: %d\n", wifi_status);
        return -1;
    }
    printf("TCP connection established successfully.\n");
   
    while (1) {
        WHZ19B_readCO2(); // read operation

        _delay_ms(2000); 

        
        if (new_co2_data_available) {
            co2_concentration = latest_co2_concentration; // Get the latest reading
            new_co2_data_available = false; 

            char message[128];
            sprintf(message, "CO2 Concentration: %d ppm", co2_concentration);
            wifi_command_TCP_transmit((uint8_t *)message, strlen(message));
        }
    }

    return 0;
}
