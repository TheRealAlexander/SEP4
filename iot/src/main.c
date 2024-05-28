////////////////////////////////////////////////////////////////
// Includ dependencies

#include "../lib/includes.h"

////////////////////////////////////////////////////////////////
// Timekeeper

static void timekeeper() {
    g_timestamp += 1;
}

////////////////////////////////////////////////////////////////
// Networking

void print_raw_bytes(void* ptr, size_t size) {
    char* byte_ptr = (char*)ptr;
    for(size_t i = 0; i < size; i++) {
        send_to_pc_fmt("%02X ", (unsigned char)byte_ptr[i]);
    }
    send_to_pc_fmt("\n");
}

void start_ntp_sync() {
    uint16_t delay = 3000;

    send_to_pc_fmt("📡 wifi begin NTP sync\n");

    wifi2_async_udp_open("216.239.35.0", 123);
    send_to_pc_fmt("📡 wifi udp open\n");

    _delay_ms(delay);

    ntp_request_packet ntp_request;
    construct_ntp_request(&ntp_request);
    send_to_pc_fmt(ANSI_FG_MAGENTA);
    print_raw_bytes(&ntp_request, sizeof(ntp_request));
    send_to_pc_fmt(ANSI_RESET);

    wifi2_async_udp_send((char*)&ntp_request, sizeof(ntp_request));
    send_to_pc_fmt("📡 wifi udp send\n");
    _delay_ms(delay);

    // Set ntp_response to the last 48 bytes of the wifi recv buffer
    ntp_response_packet ntp_response;
    uint8_t *start = wifi2_g_recv_buf + wifi2_g_recv_len - 48;
    memcpy(&ntp_response, start, 48);

    if (!is_ntp_response_packet((uint8_t*)&ntp_response, sizeof(ntp_response))) {
        send_to_pc_fmt("📡 wifi ntp response not valid\n");
        return;
    }
    send_to_pc_fmt("📡 wifi ntp response valid\n");
    print_raw_bytes(&ntp_response, sizeof(ntp_response));

    // Decode the NTP response
    decode_ntp_response((uint8_t*)&ntp_response, &ntp_response);

    // Calculate the correct UNIX time
    uint32_t unix_time = calculate_corrected_time(&ntp_response, delay); // Subtract artifically added delays
    // Cast unix_time to unit64_t to match g_timestamp
    g_timestamp = (timestamp)unix_time * 1000; // Convert seconds to milliseconds
    send_to_pc_fmt("📡 wifi ntp response UNIX time: %lu\n", unix_time);

    // Ensure UDP connection is closed
    wifi2_async_udp_close();
}

static void do_wifi(void) {
    ////////////////////////////////////////////////////////////////
    // Holder styr på hvilken async command vi er i gang med,
    // og hvilken command vi skal gå i gang med bagefter.

    typedef enum wifi_step {
        WIFI_STEP_RESET,
        WIFI_STEP_AP_JOIN,
        WIFI_STEP_TCP_OPEN,
        WIFI_STEP_TCP_SEND,
        WIFI_STEP_TCP_CLOSE,
    } wifi_step;

    static wifi_step curr_wifi_step = WIFI_STEP_RESET;
    static wifi_step next_wifi_step = WIFI_STEP_RESET;

    // TODO(rune): Burde dette command timeout være en del af driveren, eller er det mere fleksibelt at lade user-koden bestemme?
    // NOTE(rune): Timestamp for sidste gang vi begyndte en async wifi command på ESP32'en.
    static timestamp wifi_cmd_timestamp = 0;

    // NOTE(rune): Timestamp for hvor langt tid vi venter på svar fra ESP32'en.
    // Skal være større end packet_timeout. Er meget høj, da det kan tage langt tid at join et access point.
    static timestamp wifi_cmd_timeout = 20000;

    static timestamp packet_timestamp = 0;   // NOTE(rune): Timestamp for sidste gang vi begyndte en async tcp open+send+close omgang.
    static timestamp packet_timeout = 1000;
    timestamp packet_interval = g_measurements.want_next_measurement_delay;

    ////////////////////////////////////////////////////////////////
    // Tjek om vi skal starte en ny command

    if (wifi2_can_begin_async()) {
        curr_wifi_step = next_wifi_step; // NOTE(rune): Husk på hvilken command vi sætter i gang, så vi ved hvad der skal gøres når kommandoen er færdig.

        switch (next_wifi_step) {
            case WIFI_STEP_RESET: {
                send_to_pc_fmt("📡 wifi reset\n");

                wifi2_init();
                wifi2_async_reset();
                next_wifi_step = WIFI_STEP_AP_JOIN;
                wifi_cmd_timestamp = g_timestamp;
            } break;

            case WIFI_STEP_AP_JOIN: {
                wifi2_async_ap_join(WIFI_SSID, WIFI_PASSWORD);
                next_wifi_step = WIFI_STEP_TCP_OPEN;
                wifi_cmd_timestamp = g_timestamp;

                send_to_pc_fmt("📡 wifi ap join, ssid = '%s', password ='%s'\n", WIFI_SSID, WIFI_PASSWORD);

            } break;

            case WIFI_STEP_TCP_OPEN: {
                if (packet_timestamp + packet_interval <= g_timestamp) { // Er der gået mere end packet_interval siden vi sendte sidste pakke?
                    packet_timestamp = g_timestamp;

                    wifi2_async_tcp_open(SERVER_IP, SERVER_PORT);
                    next_wifi_step = WIFI_STEP_TCP_SEND;
                    wifi_cmd_timestamp = g_timestamp;

                    send_to_pc_fmt("📡 wifi tcp open, ip = %s, port = %d\n", SERVER_IP, SERVER_PORT);
                }
            } break;

            case WIFI_STEP_TCP_SEND: {
                char http_buf[512];
                int  http_len = http_build_request(http_buf, sizeof(http_buf));

                wifi2_async_tcp_send(http_buf, http_len);
                next_wifi_step = WIFI_STEP_TCP_CLOSE;
                wifi_cmd_timestamp = g_timestamp;

                send_to_pc_fmt("📡 wifi tcp send\n");
                send_to_pc(ANSI_FG_MAGENTA);
                uart_send_array_blocking(USART_0, (uint8_t *)http_buf, http_len);
                send_to_pc("\n");
                send_to_pc(ANSI_RESET);
            } break;

            case WIFI_STEP_TCP_CLOSE: {
                if (packet_timestamp + packet_timeout <= g_timestamp) {
                    http_process_response(wifi2_g_recv_buf, wifi2_g_recv_len);
                    wifi2_async_tcp_close();

                    next_wifi_step = WIFI_STEP_TCP_OPEN;
                    wifi_cmd_timestamp = g_timestamp;

                    send_to_pc_fmt("📡 wifi tcp close\n");
                }
            } break;
        }
    }

    ////////////////////////////////////////////////////////////////
    // Tjek om nuværende command er timeout eller færdig

    bool timeout_or_error = false;
    wifi2_cmd_result cmd_result = { 0 };
    if (wifi2_async_is_done(&cmd_result)) { // TODO(rune): Check også efter timeout her
        send_to_pc_fmt("Async command done: %d\n", curr_wifi_step);

        send_to_pc(ANSI_FG_YELLOW);
        uart_send_array_blocking(USART_0, (uint8_t *)wifi2_g_recv_buf, wifi2_g_recv_len);
        send_to_pc("\n");
        send_to_pc(ANSI_RESET);

        if (cmd_result.ok) {
            send_to_pc_fmt("next_wifi_step = %d\n", next_wifi_step);

            if (curr_wifi_step == WIFI_STEP_AP_JOIN) {
                start_ntp_sync(); // Start NTP sync after joining AP
                wifi2_cancel_async();
            }

            // TODO(rune): Conditional debug print
            send_to_pc_fmt("🐊 CMD RESULT current_millis = %d counter = %d, ok = %d, data_len = %d\n", g_timestamp, 99, cmd_result.ok, cmd_result.data_len);
            send_to_pc(ANSI_FG_CYAN);
            uart_send_array_blocking(USART_0, cmd_result.data, cmd_result.data_len);
            send_to_pc("\n");
            send_to_pc(ANSI_RESET);
        } else if (curr_wifi_step == WIFI_STEP_TCP_CLOSE) {
            // NOTE(rune): WIFI_STEP_TCP_CLOSE giver ok == false hvis forbindelsen allerede er lukket,
            // hvilket den vil være er, hvis transaction blev færdig uden fejl, så vi ignorerer bare at ok == false.
        } else {
            timeout_or_error = true;

            send_to_pc(ANSI_FG_RED);
            send_to_pc("cmd_result.ok == false\n");
            send_to_pc(ANSI_RESET);
        }
    } else if (wifi_cmd_timestamp + wifi_cmd_timeout <= g_timestamp) {
        timeout_or_error = true;

        send_to_pc(ANSI_FG_RED);
        send_to_pc("wifi cmd timeout\n");
        send_to_pc(ANSI_RESET);
    }

    if (timeout_or_error) {
        // NOTE(rune): Bail hvis der sker en fejl -> forsøg at join AP igen og åbn TCP forbindelse igen
        next_wifi_step = WIFI_STEP_RESET;
        wifi2_cancel_async();
    }
}

////////////////////////////////////////////////////////////////
// CO2

static void co2_callback(uint8_t byte) {
    usart3_co2_rx_handler(byte);
}

static void do_co2(void) {
    static timestamp co2_timestamp = 0;
    static timestamp co2_interval = 5000; // Adjust the interval as needed

    if (co2_timestamp + co2_interval <= g_timestamp) {
        co2_timestamp = g_timestamp;
        send_to_pc("⚡ Send CO2 command\n");
        send_co2_command(Co2SensorRead);  // Trigger CO2 reading

        g_measurements.co2           = 0;
        g_measurements.co2_timestamp = 0;
    }

    // Check global variable, which may have been updated by the CO2 driver.
    if (new_co2_data_available) {
        new_co2_data_available = false;  // Reset flag after reading
        g_measurements.co2 = latest_co2_concentration;
        g_measurements.co2_timestamp = g_timestamp / 1000; // Save timestamp of CO2 measurement
        // Print timestamp
        send_to_pc_fmt("🕒 CO2 timestamp: %lu\n", g_measurements.co2_timestamp);
    }
}

////////////////////////////////////////////////////////////////
// Temperature and Humidity Reading

static void do_dht11() {
    static timestamp dht11_timestamp = 0;
    static timestamp dht11_interval = 1000; // Sample every second

    if (dht11_timestamp + dht11_interval <= g_timestamp) {
        dht11_timestamp = g_timestamp; // Update last measurement time

        uint8_t a, b, c, d;
        if (dht11_get(&a, &b, &c, &d) == DHT11_OK) {
            g_measurements.humidity_integral = a;
            g_measurements.humidity_decimal = b;
            g_measurements.temperature_integral = c;
            g_measurements.temperature_decimal = d;
            g_measurements.humidity_timestamp = g_timestamp / 1000; // Save timestamp of humidity measurement
            g_measurements.temperature_timestamp = g_timestamp / 1000; // Save timestamp of temperature measurement
            // Print timestamp
            send_to_pc_fmt("🕒 Humidity timestamp: %lu\n", g_measurements.humidity_timestamp);
            send_to_pc_fmt("🕒 Temperature timestamp: %lu\n", g_measurements.temperature_timestamp);
            send_to_pc("🌡️ DHT11 OK\n");
        } else {
            send_to_pc("🌡️ DHT11 not OK\n");

            g_measurements.humidity_integral     = 0;
            g_measurements.humidity_decimal      = 0;
            g_measurements.temperature_integral  = 0;
            g_measurements.temperature_decimal   = 0;
            g_measurements.humidity_timestamp    = 0;
            g_measurements.temperature_timestamp = 0;
        }
    }
}

////////////////////////////////////////////////////////////////
// Servo Control

static void do_servo() {
    if (g_measurements.open_window) {
        servo(0); // Assume 0 degrees is the position to open the window
    } else {
        servo(180); // Assume 180 degrees is the position to close the window
    }
}

////////////////////////////////////////////////////////////////
// Infrared sensor and lights

static void do_pir() {
    static timestamp motion_timestamp = 0;
    static timestamp motion_delay = 10*1000; // Bestemmer hvor langt tid skal der gå før lyset slukker igen.

    if (pir_motion()) {
        motion_timestamp = g_timestamp;
    }

    if (motion_timestamp + motion_delay >= g_timestamp && motion_timestamp != 0) {
        led_set(0x00);
    } else {
        led_set(0xff);
    }
}

////////////////////////////////////////////////////////////////
// Buttons and display

static void do_buttons_and_display() {
    static timestamp button_timestamp = 0;
    static timestamp button_interval = 2000; // Hver 2 sekunder

    if (button_timestamp + button_interval <= g_timestamp) {
        button_timestamp = g_timestamp;

        handle_buttons();
    }
}

////////////////////////////////////////////////////////////////
// Main loop

int main() {
    g_measurements.want_next_measurement_delay = 5000;

    uart_init(USART_0, 9600, 0);            // USB
    uart_init(USART_3, 9600, co2_callback); // CO2
    periodic_task_init_a(timekeeper, 1);
    tone_init();
    buttons_init();
    display_init();
    pir_init();
    dht11_init();
    led_init();

    while (1) {
        do_wifi();
        do_co2();
        do_dht11();
        do_servo();
        do_buttons_and_display();
        do_pir();

        _delay_ms(100);
    }

    return 0;
}
