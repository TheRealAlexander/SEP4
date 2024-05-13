#ifndef DISPLAY_BUTTON_H
#define DISPLAY_BUTTON_H

#include "includes/includes.h"

extern int teamscore_a;
extern int teamscore_b;

extern void controller_init(void);
extern void handle_buttons(void);
extern void resetScore(void);
extern void setScoreTo40(void);
extern void updateDisplay(void);
extern void checkScoreAPlus(void);
extern void checkScoreAMinus(void);
extern void checkScoreBPlus(void);
extern void checkScoreBMinus(void);

#endif // DISPLAY_BUTTON_H