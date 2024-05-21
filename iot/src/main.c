////////////////////////////////////////////////////////////////
// Macros

#define countof(a)          (sizeof(a) / sizeof(*(a)))

// TODO(rune): Define udfra build-script?

//#define SERVER_IP       "172.20.10.8"
//#define SERVER_PORT     8080

//#define SERVER_IP       "159.89.140.122"
//#define SERVER_IP       "216.58.211.14"
#define SERVER_IP       "172.20.10.6" // Alexander
//#define SERVER_IP       "172.20.10.3" // Rune 
#define SERVER_PORT     5200
//#define SERVER_PORT      5038

//#define WIFI_SSID       "Rune - iPhone"
//#define WIFI_PASSWORD   "123456789"
#define WIFI_SSID       "TheHotspot"
#define WIFI_PASSWORD   "pfea1111"

////////////////////////////////////////////////////////////////
// Debugging

void send_to_pc(char *str);
void send_to_pc_fmt(char *fmt, ...);

////////////////////////////////////////////////////////////////
// Depedencies

// NOTE(rune): Når vi compiler udenom Platform IO, compiler vi bare det hele
// i en translation unit, så vi kan have et meget simpelt build script.
// Platform IO gør nogle mærkelige ting med stier, f.eks. #include'er wifi.h
// uart.h uden at sige "../uart/uart.h", selvom wifi.h og uart.h ligger i
// forskellige mapper. Vi bruger #if NOT_PLATFORMIO til at arbejde rundt om 
// forskellene mellem Platform IO og ikke-Platform IO.

#if NOT_PLATFORMIO
#   include <stdio.h>
#   include <string.h>
#   include <util/delay.h>
#   include <avr/io.h>
#   include <avr/interrupt.h>
#   include "../lib/uart/uart.h"
#   include "../lib/uart/uart.c"
#   include "../lib/driverMHZ19B/driverMHZ19B.h"
#   include "../lib/driverMHZ19B/driverMHZ19B.c"
#   include "../lib/Periodic/periodic_task.h"
#   include "../lib/Periodic/periodic_task.c"
#   include "../lib/dht11/dht11.h"
#   include "../lib/dht11/dht11.c"
#   include "../lib/wifi/wifi2.h"
#   include "../lib/wifi/wifi2.c"
#   include "../lib/wifi/ntp.h"
#   include "../lib/wifi/ntp.c"
#   include "../lib/servo/servo.h"
#   include "../lib/servo/servo.c"
#else
#   include <stdio.h>
#   include <string.h>
#   include "uart.h"
#   include "driverMHZ19B.h"
#   include <periodic_task.h>
#   include "../wifi/ntp.h"
#endif

void callback(uint8_t byte) {
    usart3_co2_rx_handler(byte);
}

void send_to_pc_fmt(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char temp[1024];
    vsnprintf(temp, sizeof(temp), fmt, args);
    va_end(args);
    send_to_pc(temp);
}

////////////////////////////////////////////////////////////////
// ANSI console escape codes

#define ANSI_HOME                   "\x1b[H"
#define ANSI_ERASE_SCREEN           "\x1b[2J"

#define ANSI_RESET                  "\x1b[0m"
#define ANSI_BOLD                   "\x1b[1m"
#define ANSI_FAINT                  "\x1b[2m"
#define ANSI_ITALIC                 "\x1b[3m"
#define ANSI_UNDERLINE              "\x1b[4m"
#define ANSI_BLINKING               "\x1b[5m"
#define ANSI_STRIKETHROUGH          "\x1b[9m"

#define ANSI_FG_DEFAULT             "\x1b[39m"
#define ANSI_FG_BLACK               "\x1b[30m"
#define ANSI_FG_WHITE               "\x1b[97m"
#define ANSI_FG_RED                 "\x1b[31m"
#define ANSI_FG_GREEN               "\x1b[32m"
#define ANSI_FG_YELLOW              "\x1b[33m"
#define ANSI_FG_BLUE                "\x1b[34m"
#define ANSI_FG_MAGENTA             "\x1b[35m"
#define ANSI_FG_CYAN                "\x1b[36m"
#define ANSI_FG_GRAY                "\x1b[90m"
#define ANSI_FG_BRIGHT_GRAY         "\x1b[37m"
#define ANSI_FG_BRIGHT_RED          "\x1b[91m"
#define ANSI_FG_BRIGHT_GREEN        "\x1b[92m"
#define ANSI_FG_BRIGHT_YELLOW       "\x1b[93m"
#define ANSI_FG_BRIGHT_BLUE         "\x1b[94m"
#define ANSI_FG_BRIGHT_MAGENTA      "\x1b[95m"
#define ANSI_FG_BRIGHT_CYAN         "\x1b[96m"

////////////////////////////////////////////////////////////////
// Measurements

typedef struct measurements {
    uint8_t humidity_integral;     // NOTE(rune): Før komma
    uint8_t humidity_decimal;      // NOTE(rune): Efter komma
    uint8_t temperature_integral;  // NOTE(rune): Før komma
    uint8_t temperature_decimal;   // NOTE(rune): Efter komma

    uint16_t co2;
    bool open_window;   
} measurements;

static measurements g_measurements;

////////////////////////////////////////////////////////////////
// Time keeping

typedef uint64_t timestamp;

static timestamp g_timestamp;

static void timekeeper() {
    g_timestamp += 1;
}

////////////////////////////////////////////////////////////////
// Networking

static int build_http_request(char *http_buf, int http_cap) {
    // NOTE(rune): Danner først json med separat snprintf, da vi skal bruge længden af json i Content-Length headeren.
    // TODO(rune): Burde kun tage de målinger med, som vi rent faktisk har resultater på. F.eks. skal co2 ikke skrives
    // i json, hvis checksum ikke passede, og temperatur skal ikke skrives på, hvis dht11_get() fejler.
    char json_buf[256];
    int json_len = snprintf(
        json_buf, sizeof(json_buf),
        "{"
        "\"temperature\": %d.%d, "
        "\"humidity\": %d.%d, "
        "\"co2\": %d"
        "}",
        g_measurements.temperature_integral, g_measurements.temperature_decimal,
        g_measurements.humidity_integral, g_measurements.humidity_decimal,
        g_measurements.co2
    );

    int http_len = snprintf(
        http_buf, http_cap,
        "POST /PostEnviromentData HTTP/1.0\r\n"
        "Host: indeklima\r\n"
        "Connection: Close\r\n"
        "Accept: application/json\r\n"
        "Accept-Encoding: identity\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n"
        "\r\n"
        "%s",
        json_len, json_buf
    );

    return http_len;
}

static void process_http_response(char *http_buf, int http_len) {

    send_to_pc(ANSI_FG_GREEN);
    uart_send_array_blocking(USART_0, http_buf, http_len);
    send_to_pc("\n");
    send_to_pc(ANSI_RESET);
    send_to_pc("========================\n");

    // NOTE(rune): Fjern whitespace så vi kan lave string comparison, 
    // uden at bekymre os om formatting fra serveren.
    char trim_buf[WIFI2_MAX_RECV];
    int read = 0;
    int write = 0;
    while (read < http_len) {
        if (http_buf[read] == ' ' ||
            http_buf[read] == '\n' ||
            http_buf[read] == '\r' ||
            http_buf[read] == '\t') {

            read++;
        } else {
            trim_buf[write] = http_buf[read];
            read++;
            write++;
        }
    }

    int trim_len = write;
    send_to_pc(ANSI_FG_GREEN);
    uart_send_array_blocking(USART_0, trim_buf, trim_len);
    send_to_pc("\n");
    send_to_pc(ANSI_RESET);

    trim_buf[trim_len] = '\0';
    if (strstr(trim_buf, "\"openWindow\":false")) { g_measurements.open_window = false; } 
    if (strstr(trim_buf, "\"openWindow\":true"))  { g_measurements.open_window = true; }

    send_to_pc(ANSI_FG_BRIGHT_MAGENTA);
    send_to_pc_fmt("window: %d\n", g_measurements.open_window);
    send_to_pc(ANSI_RESET);
}

void print_raw_bytes(void* ptr, size_t size) {
    char* byte_ptr = (char*)ptr;
    for(size_t i = 0; i < size; i++) {
        send_to_pc_fmt("%02X ", (unsigned char)byte_ptr[i]);
    }
    send_to_pc_fmt("\n");
}

void start_ntp_sync() {
    send_to_pc_fmt("📡 wifi begin NTP sync\n");

    wifi2_async_udp_open("216.239.35.0", 123);
    send_to_pc_fmt("📡 wifi udp open\n");

    _delay_ms(3000);

    ntp_request_packet ntp_request;
    construct_ntp_request(&ntp_request);
    send_to_pc_fmt(ANSI_FG_MAGENTA);
    print_raw_bytes(&ntp_request, sizeof(ntp_request));
    send_to_pc_fmt(ANSI_RESET);

    // Record t1 just before sending the NTP request
    unsigned long long t1 = g_timestamp + NTP_TIMESTAMP_DELTA;

    wifi2_async_udp_send((char*)&ntp_request, sizeof(ntp_request));
    send_to_pc_fmt("📡 wifi udp send\n");
    _delay_ms(3000);

    // Record t4 immediately after receiving the NTP response
    unsigned long long t4 = g_timestamp + NTP_TIMESTAMP_DELTA;
    // Subtract the artificial delay to get the correct t4
    t4 -= 3000;

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
    uint32_t unix_time = calculate_corrected_time(&ntp_response, t1, t4);
    send_to_pc_fmt("📡 wifi ntp response UNIX time: %lu\n", unix_time);

    // Ensure UDP connection is closed after timeout
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

    static bool      packet_proccesed = true;
    static timestamp packet_timestamp = 0;   // NOTE(rune): Timestamp for sidste gang vi begyndte en async tcp open+send+close omgang.
    static timestamp packet_interval = 5000; // NOTE(rune): Hvor ofte sendes ny packet? 
    static timestamp packet_timeout = 1000;  

    ////////////////////////////////////////////////////////////////
    // Tjek om vi skal starte en ny command

    if (wifi2_can_begin_async()) {
        curr_wifi_step = next_wifi_step; // NOTE(rune): Husk på hvilken command vi sætter i gang, så vi ved hvad der skal gøres når kommandoen er færdig.

        switch (next_wifi_step) {
            case WIFI_STEP_RESET: {
                send_to_pc_fmt("📡 wifi reset\n"); // TODO(rune): Conditional debug print

                wifi2_init();
                wifi2_async_reset();
                next_wifi_step = WIFI_STEP_AP_JOIN;
            } break;

            case WIFI_STEP_AP_JOIN: {
                wifi2_async_ap_join(WIFI_SSID, WIFI_PASSWORD);
                next_wifi_step = WIFI_STEP_TCP_OPEN;

                send_to_pc_fmt("📡 wifi ap join\n"); // TODO(rune): Conditional debug print           

            } break;

            case WIFI_STEP_TCP_OPEN: {
                if (packet_timestamp + packet_interval <= g_timestamp) { // Er der gået mere end packet_interval siden vi sendte sidste pakke?
                    packet_timestamp = g_timestamp;
                    packet_proccesed = false;

                    wifi2_async_tcp_open(SERVER_IP, SERVER_PORT);
                    next_wifi_step = WIFI_STEP_TCP_SEND;

                    send_to_pc_fmt("📡 wifi tcp open\n"); // TODO(rune): Conditional debug print
                }
            } break;

            case WIFI_STEP_TCP_SEND: {
                char http_buf[512];
                int  http_len = build_http_request(http_buf, sizeof(http_buf));

                wifi2_async_tcp_send(http_buf, http_len);
                next_wifi_step = WIFI_STEP_TCP_CLOSE;

                send_to_pc_fmt("📡 wifi tcp send\n"); // TODO(rune): Conditional debug print
                send_to_pc(ANSI_FG_MAGENTA);
                uart_send_array_blocking(USART_0, http_buf, http_len);
                send_to_pc("\n");
                send_to_pc(ANSI_RESET);
            } break;

            case WIFI_STEP_TCP_CLOSE: {
                if (packet_timestamp + packet_timeout <= g_timestamp) {
                    process_http_response(wifi2_g_recv_buf, wifi2_g_recv_len);

                    next_wifi_step = WIFI_STEP_TCP_OPEN;
                    send_to_pc_fmt("📡 wifi tcp close\n"); // TODO(rune): Conditional debug print
                }
            } break;
        }
    }

    ////////////////////////////////////////////////////////////////
    // Tjek om nuværende command er færdig

    wifi2_cmd_result cmd_result = { 0 };
    if (wifi2_async_is_done(&cmd_result)) { // TODO(rune): Check også efter timeout her
        send_to_pc_fmt("Async command done: %d\n", curr_wifi_step);

        send_to_pc(ANSI_FG_YELLOW);
        uart_send_array_blocking(USART_0, wifi2_g_recv_buf, wifi2_g_recv_len);
        send_to_pc("\n");
        send_to_pc(ANSI_RESET);

        if (cmd_result.ok) {
            if (curr_wifi_step == WIFI_STEP_TCP_SEND) {
                //process_http_response(cmd_result.data, cmd_result.data_len);
            }
            if (curr_wifi_step == WIFI_STEP_AP_JOIN) {
                start_ntp_sync(); // Start NTP sync after joining AP
            }

            // TODO(rune): Conditional debug print
            send_to_pc_fmt("🐊 CMD RESULT current_millis = %d counter = %d, ok = %d, data_len = %d\n", g_timestamp, 99, cmd_result.ok, cmd_result.data_len);
            send_to_pc(ANSI_FG_CYAN);
            uart_send_array_blocking(USART_0, cmd_result.data, cmd_result.data_len);
            send_to_pc("\n");
            send_to_pc(ANSI_RESET);
        } else if (curr_wifi_step == WIFI_STEP_TCP_CLOSE) {
            // NOTE(rune): WIFI_STEP_TCP_CLOSE giver ok == false hvis forbindelsen allerede er lukket, så vi ignorerer bare fejlen.
        } else {
            // NOTE(rune): Bail hvis der sker en fejl -> forsøg at join AP igen og åbn TCP forbindelse igen
            next_wifi_step = WIFI_STEP_RESET;

            send_to_pc(ANSI_FG_RED);
            send_to_pc("cmd_result.ok == false\n");
            send_to_pc(ANSI_RESET);
        }
    }
}

////////////////////////////////////////////////////////////////
// CO2

static void do_co2(void) {
    static timestamp co2_timestamp = 0;
    static timestamp co2_interval = 5000; // TODO(rune): Test hvor langt vi kan sætte delay'et ned

    if (co2_timestamp + co2_interval <= g_timestamp) {
        co2_timestamp = g_timestamp;
        send_to_pc("⚡ Send CO2 command\n"); // TODO(rune): Conditional debug print
        send_co2_command(Co2SensorRead);  // Trigger CO2 reading
    }

    // Check global variable, which may have been updated by the CO2 driver.
    if (new_co2_data_available) {
        new_co2_data_available = false;  // Reset flag after reading
        g_measurements.co2 = latest_co2_concentration;
    }
}

////////////////////////////////////////////////////////////////
// Temperature and humidity

static void do_dht11() {
    static timestamp dht11_timestamp = 0;
    static timestamp dht11_interval = 1000;

    if (dht11_timestamp + dht11_interval <= g_timestamp) {
        dht11_timestamp = g_timestamp;

        uint8_t a, b, c, d;
        if (dht11_get(&a, &b, &c, &d) == DHT11_OK) {
            g_measurements.humidity_integral    = a;
            g_measurements.humidity_decimal     = b;
            g_measurements.temperature_integral = c;
            g_measurements.temperature_decimal  = d;

            send_to_pc("🌡️ DHT11 OK\n");
        } else {
            send_to_pc("🌡️ DHT11 not OK\n");
        }
    }
}

////////////////////////////////////////////////////////////////
// Servo

static void do_servo() {

    if (g_measurements.open_window) {
        servo(0);
    } else {
        servo(180);
    }
}

////////////////////////////////////////////////////////////////
// Main loop

int main() {
    uart_init(USART_0, 9600, 0);        // USB
    uart_init(USART_3, 9600, callback); // CO2
    periodic_task_init_a(timekeeper, 1);

    while (1) {
        do_wifi();
        do_co2();
        do_dht11();
        //do_servo();

        _delay_ms(100);
    }

    return 0;
}
