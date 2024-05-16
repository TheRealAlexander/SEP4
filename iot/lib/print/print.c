////////////////////////////////////////////////////////////////
// Debug print

#if MOCK

void print_init(void) {}

void send_to_pc(char *s) {
    printf("%s", s);
}

void send_to_pc_fmt(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

#elif NO_DEBUG_PRINT

void print_init(void) {}
void send_to_pc(char *s) { UNUSED(s); }
void send_to_pc_fmt(char *fmt, ...) { UNUSED(fmt); }

#else

void print_init(void) {
    uart_init(USART_0, 9600, NULL);
}

void send_to_pc(char *s) {
    uart_send_string_blocking(USART_0, s); 
}

void send_to_pc_fmt(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char temp[1024];
    vsnprintf(temp, sizeof(temp), fmt, args);
    va_end(args);
    send_to_pc(temp);
}

#endif 
