////////////////////////////////////////////////////////////////
// Includ dependencies

#include "../lib/includes.h"

////////////////////////////////////////////////////////////////
// Macros

// TODO(rune): Define udfra build-script?

//#define SERVER_IP       "172.20.10.8"
//#define SERVER_PORT     8080

//#define SERVER_IP       "159.89.140.122"
//#define SERVER_IP       "216.58.211.14"
//#define SERVER_IP       "172.20.10.6" // Alexander
#define SERVER_IP       "172.20.10.3" // Rune
#define SERVER_PORT     5200
//#define SERVER_PORT      5038

#define WIFI_SSID       "Rune - iPhone"
#define WIFI_PASSWORD   "123456789"

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
    uart_send_array_blocking(USART_0, (uint8_t *)http_buf, http_len);
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
    trim_buf[trim_len] = '\0';

    send_to_pc(ANSI_FG_GREEN);
    send_to_pc(trim_buf);
    send_to_pc("\n");
    send_to_pc(ANSI_RESET);

    if (strstr(trim_buf, "\"openWindow\":false")) { g_measurements.open_window = false; }
    if (strstr(trim_buf, "\"openWindow\":true"))  { g_measurements.open_window = true; }

    send_to_pc(ANSI_FG_BRIGHT_MAGENTA);
    send_to_pc_fmt("window: %d\n", g_measurements.open_window);
    send_to_pc(ANSI_RESET);
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

    static timestamp packet_timestamp = 0;   // NOTE(rune): Timestamp for sidste gang vi begyndte en async tcp open+send+close omgang.
    static timestamp packet_interval = 5000; // NOTE(rune): Hvor ofte sendes ny packet?
    static timestamp packet_timeout = 1000;

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
            } break;

            case WIFI_STEP_AP_JOIN: {
                wifi2_async_ap_join(WIFI_SSID, WIFI_PASSWORD);
                next_wifi_step = WIFI_STEP_TCP_OPEN;

                send_to_pc_fmt("📡 wifi ap join\n");
            } break;

            case WIFI_STEP_TCP_OPEN: {
                if (packet_timestamp + packet_interval <= g_timestamp) { // Er der gået mere end packet_interval siden vi sendte sidste pakke?
                    packet_timestamp = g_timestamp;

                    wifi2_async_tcp_open(SERVER_IP, SERVER_PORT);
                    next_wifi_step = WIFI_STEP_TCP_SEND;

                    send_to_pc_fmt("📡 wifi tcp open\n");
                }
            } break;

            case WIFI_STEP_TCP_SEND: {
                char http_buf[512];
                int  http_len = build_http_request(http_buf, sizeof(http_buf));

                wifi2_async_tcp_send(http_buf, http_len);
                next_wifi_step = WIFI_STEP_TCP_CLOSE;

                send_to_pc_fmt("📡 wifi tcp send\n");
                send_to_pc(ANSI_FG_MAGENTA);
                uart_send_array_blocking(USART_0, (uint8_t *)http_buf, http_len);
                send_to_pc("\n");
                send_to_pc(ANSI_RESET);
            } break;

            case WIFI_STEP_TCP_CLOSE: {
                if (packet_timestamp + packet_timeout <= g_timestamp) {
                    process_http_response(wifi2_g_recv_buf, wifi2_g_recv_len);
                    wifi2_async_tcp_close();

                    next_wifi_step = WIFI_STEP_TCP_OPEN;
                    send_to_pc_fmt("📡 wifi tcp close\n");
                }
            } break;
        }
    }

    ////////////////////////////////////////////////////////////////
    // Tjek om nuværende command er færdig

    wifi2_cmd_result cmd_result = { 0 };
    if (wifi2_async_is_done(&cmd_result)) { // TODO(rune): Check også efter timeout her

        send_to_pc(ANSI_FG_YELLOW);
        uart_send_array_blocking(USART_0, (uint8_t *)wifi2_g_recv_buf, wifi2_g_recv_len);
        send_to_pc("\n");
        send_to_pc(ANSI_RESET);

        if (cmd_result.ok) {
            send_to_pc_fmt("🐊 CMD RESULT current_millis = %d counter = %d, ok = %d, data_len = %d\n", g_timestamp, 99, cmd_result.ok, cmd_result.data_len);
            send_to_pc(ANSI_FG_CYAN);
            uart_send_array_blocking(USART_0, cmd_result.data, cmd_result.data_len);
            send_to_pc("\n");
            send_to_pc(ANSI_RESET);
        } else if (curr_wifi_step == WIFI_STEP_TCP_CLOSE) {
            // NOTE(rune): WIFI_STEP_TCP_CLOSE giver ok == false hvis forbindelsen allerede er lukket,
            // hvilket den vil være er, hvis transaction blev færdig uden fejl, så vi ignorerer bare at ok == false.
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

static void co2_callback(uint8_t byte) {
    usart3_co2_rx_handler(byte);
}

static void do_co2(void) {
    static timestamp co2_timestamp = 0;
    static timestamp co2_interval = 5000; // TODO(rune): Test hvor langt vi kan sætte delay'et ned

    if (co2_timestamp + co2_interval <= g_timestamp) {
        co2_timestamp = g_timestamp;
        send_to_pc("⚡ Send CO2 command\n");
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
    uart_init(USART_0, 9600, 0);            // USB
    uart_init(USART_3, 9600, co2_callback); // CO2
    periodic_task_init_a(timekeeper, 1);

    while (1) {
        do_wifi();
        do_co2();
        do_dht11();
        do_servo();

        _delay_ms(100);
    }

    return 0;
}
