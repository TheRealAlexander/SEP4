#include "display_button.h"
#include <buttons.h>
#include <display.h>

int teamscore_a = 0;
int teamscore_b = 0;

void controller_init(void) {
    buttons_init();
    display_init();
}

void handle_button_A(void) {
    if (buttons_1_pressed()) {
        teamscore_a ++;
        display_setValues(17, 17, 1, 2);

    } else {
        display_setValues(17, 17, 17, 17);
    }
}
