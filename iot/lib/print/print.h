////////////////////////////////////////////////////////////////
// Debug print

// NOTE(rune): Hvis MOCK=1, skrives til stdout via printf ellers sendes gennem uart.

void print_init(void);
void send_to_pc(char *s);
void send_to_pc_fmt(char *fmt, ...);

////////////////////////////////////////////////////////////////
// ANSI console escape codes

// NOTE(rune): List of ANSI escape sequences: 
// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

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
