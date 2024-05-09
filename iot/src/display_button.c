#include "display_button.h"
#include <buttons.h>
#include <display.h>
#include <includes.h>
int teamscore_a = 0;
int teamscore_b = 0;

void controller_init(void) {
    buttons_init();
    display_init();
}

void handle_buttons(void) {
        int tensA = teamscore_a / 10;
        int onesA = teamscore_a % 10;
        int tensB = teamscore_b / 10;
        int onesB = teamscore_b % 10;
    if (buttons_1_pressed()) {
        teamscore_a ++;
        
        display_setValues(tensA, onesA, tensB, onesB);

    } else if (buttons_1_pressed && buttons_2_pressed){
        teamscore_a --;
        display_setValues(tensA, onesA, tensB, onesB);
    } else if (buttons_2_pressed){
         teamscore_a == 0;
         teamscore_b == 0;
         display_setValues(tensA, onesA, tensB, onesB);
    } else if( buttons_3_pressed){
        teamscore_b ++;
        display_setValues(tensA, onesA, tensB, onesB);
    } else if(buttons_2_pressed && buttons_3_pressed){
        teamscore_b --;
        display_setValues(tensA, onesA, tensB, onesB);
    }
}
bool checkScore(void){

}

