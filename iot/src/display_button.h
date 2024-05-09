#ifndef DISPLAY_BUTTON_H
#define DISPLAY_BUTTON_H
#include "includes/includes.h"

void controller_init(void);
void handle_buttons(void);
void resetScore(void);
void setScoreTo40(void);
void updateDisplay(void);
void checkScoreAPlus(void);
void checkScoreAMinus(void);
void checkScoreBPlus(void);
void checkScoreBMinus(void);
#endif