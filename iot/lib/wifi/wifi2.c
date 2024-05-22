#if NOT_PLATFORMIO
// Nothing
#else
// TODO(rune): Include headers som Platform IO skal bruge.
#endif

////////////////////////////////////////////////////////////////
// Globals

wifi2_state  wifi2_g_state;
char         wifi2_g_recv_buf[WIFI2_MAX_RECV];
int          wifi2_g_recv_len;

int          wifi2_g_ipd_len; // Tallet fra "+IPD,1234:" prefixet gemmes i wifi2_g_ipd_len, og fort�ller hvor langt response data er.
int          wifi2_g_ipd_idx; // Index i wifi2_g_recv_buf for data efter "+IPD,1234:" prefixet.

////////////////////////////////////////////////////////////////
// Functions

extern void wifi2_init() {
    uart_init(WIFI2_USART, WIFI2_BAUDRATE, wifi2_uart_callback);
}

extern bool wifi2_can_begin_async(void) {
    return wifi2_g_state == WIFI2_STATE_NONE;
}

extern bool wifi2_async_is_done(wifi2_cmd_result *result) {
    result->ok = false;
    result->data = "";
    result->data_len = 0;

    switch (wifi2_g_state) {
        case WIFI2_STATE_DONE_OK: {
            if (wifi2_g_ipd_idx > 0) {
                result->data     = wifi2_g_recv_buf + wifi2_g_ipd_idx;
                result->data_len = wifi2_g_ipd_len;
            } else {
                result->data = "";
                result->data_len = 0;
            }
            wifi2_g_state = WIFI2_STATE_NONE; // NOTE(rune): Marker at vi er klar til n�ste command
            result->ok = true;
            return true;
        }

        case WIFI2_STATE_DONE_FAIL: {
            wifi2_g_state = WIFI2_STATE_NONE; // NOTE(rune): Marker at vi er klar til n�ste command
            return true;
        }

        default: {
            return false;
        }
    }
}

static void wifi2_cancel_async(void) {
    wifi2_g_state = WIFI2_STATE_NONE;
}

extern void wifi2_async(char *cmd, bool ipd) {
    memset(wifi2_g_recv_buf, 0, sizeof(wifi2_g_recv_buf));
    wifi2_g_recv_len = 0;
    wifi2_g_ipd_idx = 0;
    wifi2_g_ipd_len = 0;

    if (ipd) {
        wifi2_g_state = WIFI2_STATE_WAIT_IPD;
    } else {
        wifi2_g_state = WIFI2_STATE_WAIT;
    }

    uart_send_string_blocking(WIFI2_USART, cmd);
}

extern void wifi2_uart_callback(uint8_t byte) {
    if (wifi2_g_recv_len < sizeof(wifi2_g_recv_buf)) {
        wifi2_g_recv_buf[wifi2_g_recv_len++] = byte;
    }

    switch (wifi2_g_state) {
        case WIFI2_STATE_WAIT:
        case WIFI2_STATE_WAIT_IPD: {
            static char *look_for[] = {
                "OK", "FAIL", "ERROR"
            };

            for (int i = 0; i < countof(look_for); i++) {
                int look_for_len = strlen(look_for[i]);
                if (memmem(wifi2_g_recv_buf, wifi2_g_recv_len, look_for[i], look_for_len)) {
                    if (i > 0) {
                        wifi2_g_state = WIFI2_STATE_DONE_FAIL;
                    } else if (wifi2_g_state == WIFI2_STATE_WAIT) {
                        wifi2_g_state = WIFI2_STATE_DONE_OK;
                    } else if (wifi2_g_state == WIFI2_STATE_WAIT_IPD) {
                        wifi2_g_state = WIFI2_STATE_WAIT_IPD_PREFIX;
                    } else {
                        wifi2_g_state = WIFI2_STATE_DONE_FAIL;
                    }

                    break;
                }
            }
        } break;

        case WIFI2_STATE_WAIT_IPD_PREFIX: {
            char *ipd_prefix = "+IPD,";
            if (memmem(wifi2_g_recv_buf, wifi2_g_recv_len, ipd_prefix, strlen(ipd_prefix))) {
                wifi2_g_state = WIFI2_STATE_WAIT_IPD_LENGTH;
            }
        } break;

        case WIFI2_STATE_WAIT_IPD_LENGTH: {
            if (byte >= '0' && byte <= '9') {
                wifi2_g_ipd_len *= 10;
                wifi2_g_ipd_len += byte - '0';
            } else if (byte == ':') {
                wifi2_g_state = WIFI2_STATE_WAIT_IPD_DATA;
                wifi2_g_ipd_idx = wifi2_g_recv_len;
            } else {
                wifi2_g_ipd_idx = 0;
                wifi2_g_ipd_len = 0;
            }
        } break;

        case WIFI2_STATE_WAIT_IPD_DATA: {
            if (wifi2_g_recv_len >= wifi2_g_ipd_idx + wifi2_g_ipd_len) {
                wifi2_g_state = WIFI2_STATE_DONE_OK;
            }
        } break;
    }
}

extern void wifi2_async_reset(void) {
    char *cmd = "AT+RST\r\n";
    wifi2_async(cmd, false);
}

extern void wifi2_async_ap_join(char *ssid, char *password) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
    wifi2_async(cmd, false);
}

extern void wifi2_async_tcp_open(char *ip, int port) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", ip, port);
    wifi2_async(cmd, false);
}

extern void wifi2_async_tcp_send(char *data, int data_len) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%d\r\n", data_len);
    wifi2_async(cmd, true);
    _delay_ms(20);
    uart_send_array_blocking(WIFI2_USART, data, data_len);
}

extern void wifi2_async_tcp_close(void) {
    char *cmd = "AT+CIPCLOSE\r\n";
    wifi2_async(cmd, false);
}

extern void wifi2_async_udp_open(char *ip, int port) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "AT+CIPSTART=\"UDP\",\"%s\",%d\r\n", ip, port);
    wifi2_async(cmd, false);
}

extern void wifi2_async_udp_send(char *data, int data_len) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%d\r\n", data_len);
    wifi2_async(cmd, false);
    _delay_ms(20);
    uart_send_array_blocking(WIFI2_USART, data, data_len);
}

extern void wifi2_async_udp_close(void) {
    // Same as tcp close
    wifi2_async_tcp_close();
}