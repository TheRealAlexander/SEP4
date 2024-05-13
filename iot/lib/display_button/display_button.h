#ifndef DISPLAY_BUTTON_H
#define DISPLAY_BUTTON_H

#include "includes/includes.h"
#ifndef PLATFORMIO_UNIT_TEST
int teamscore_a;
int teamscore_b;

void controller_init(void);
void handle_buttons(void);
void resetScore(void);
void setScoreTo40(void);
void updateDisplay(void);
void checkScoreAPlus(void);
void checkScoreAMinus(void);
void checkScoreBPlus(void);
void checkScoreBMinus(void);
#endif // PLATFORMIO_UNIT_TEST
#endif // DISPLAY_BUTTON_H