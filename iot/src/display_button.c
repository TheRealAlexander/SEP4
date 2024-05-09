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
void setScoreTo40(void){
    teamscore_a == 40;
    teamscore_b == 40;
}
void resetScore(void){
    teamscore_a == 0;
    teamscore_b == 0;
}
void handle_buttons(void) {
        int tensA = teamscore_a / 10;
        int onesA = teamscore_a % 10;
        int tensB = teamscore_b / 10;
        int onesB = teamscore_b % 10;
    if (buttons_1_pressed()) {
        checkScoreAPlus();    
        display_setValues(tensA, onesA, tensB, onesB);

    } else if (buttons_1_pressed && buttons_2_pressed){
        checkScoreAMinus();
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
void checkScoreAPlus(){
   switch(teamscore_a) {
        case 0:
            teamscore_a = 15;
            break;
        case 15:
            teamscore_a = 30;
            break;
        case 30:
            teamscore_a = 40;
            break;
        case 40:
            if (teamscore_b < 41) {
                teamscore_a = 41; 
            } else {
               setScoreTo40();
            }
            break;
        case 41:
            if (teamscore_b < 41){
               teamscore_a = 42
            } else {
                setScoreTo40();
            }
            break;
        default:
            break;; 
    }
}
void checkScoreAMinus(void){
    switch(teamscore_a){
        case 0:
           break;
        case 15: 
           teamscore_a = 0;
           break;
        case 30:
           teamscore_a = 15;
           break;
        case 40:
           teamscore_a = 30;
           break;
        case 41:
           teamscore_a = 40;
           break;
        default:
        break;;

    }    
}
