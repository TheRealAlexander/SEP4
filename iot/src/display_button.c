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
int checkScoreA(){
   switch(teamscore_a) {
        case 0:
            return 15;
        case 15:
            return 30;
        case 30:
            return 40;
        case 40:
            if (teamscore_b < 41) {
                return 41; 
            } else {
               setScoreTo40();
            }
            break;
        case 41:
            if (teamscore_b < 41){
                return 42
            } else {
                setScoreTo40();
            }
            break;
        default:
            return teamscore_a; // Return the current score if none of the above conditions are met.
    }
    return teamscore_a;
int checkScoreB(void){

}
