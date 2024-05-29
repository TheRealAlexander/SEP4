////////////////////////////////////////////////////////////////
// References

// https://github.com/LauritsIvar/sep4_drivers
// https://docs.espressif.com/projects/esp-at/en/latest/esp32/index.html

////////////////////////////////////////////////////////////////
// Macros

#define WIFI2_USART     USART_2
#define WIFI2_BAUDRATE  115200
#define WIFI2_MAX_RECV  2048

////////////////////////////////////////////////////////////////
// Types

typedef enum wifi2_state {
    WIFI2_STATE_NONE,            // Ingen igangværende command
    WIFI2_STATE_DONE_OK,         // Fandt "OK" i respose fra ESP32
    WIFI2_STATE_DONE_FAIL,       // Fandt "ERROR" eller "FAIL" i response fra ESP32
    WIFI2_STATE_WAIT,            // I gang med at læse AT+XXXXX response.
} wifi2_state;

typedef struct wifi2_cmd_result {
    bool ok;
} wifi2_cmd_result;

////////////////////////////////////////////////////////////////
// Globals

static wifi2_state  wifi2_g_state;
static char         wifi2_g_recv_buf[WIFI2_MAX_RECV];
static int          wifi2_g_recv_len;

////////////////////////////////////////////////////////////////
// Functions

static void wifi2_init();
static void wifi2_uart_callback(uint8_t byte);

static void wifi2_async(char *cmd);
static void wifi2_async_reset(void);
static void wifi2_async_ap_join(char *ssid, char *password);
static void wifi2_async_tcp_open(char *ip, int port);
static void wifi2_async_tcp_send(char *data, int data_len);
static void wifi2_async_tcp_close(void);
static void wifi2_async_udp_open(char *ip, int port);
static void wifi2_async_udp_send(char *data, int data_len);
static void wifi2_async_udp_close(void);

static bool wifi2_can_begin_async(void); // Klar til at starte ny async command?
static bool wifi2_async_is_done(wifi2_cmd_result *result); // Er seneste async command f�rdig eller har fejlet?
static void wifi2_cancel_async(void);
