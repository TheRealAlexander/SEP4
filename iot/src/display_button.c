#include "display_button.h"
#include <buttons.h>
#include <display.h>
#include <includes.h>
int teamscore_a = 0;
int teamscore_b = 0;

void controller_init(void)
{
    buttons_init();
    display_init();
}

void setScoreTo40(void)
{
    teamscore_a = 40;
    teamscore_b = 40;
    updateDisplay();
}

void resetScore(void)
{
    teamscore_a == 0;
    teamscore_b == 0;
    updateDisplay();
}

void updateDisplay(void)
{
    int tensA = teamscore_a / 10;
    int onesA = teamscore_a % 10;
    int tensB = teamscore_b / 10;
    int onesB = teamscore_b % 10;
    display_setValues(tensA, onesA, tensB, onesB);
}

void handle_buttons(void)
{
    if (buttons_1_pressed())
    {
        checkScoreAPlus();
    }
    else if (buttons_1_pressed() && buttons_2_pressed())
    {
        checkScoreAMinus();
    }
    else if (buttons_2_pressed())
    {
        resetScore();
    }
    else if (buttons_3_pressed())
    {
        checkScoreBPlus();
    }
    else if (buttons_2_pressed() && buttons_3_pressed())
    {
        checkScoreBMinus(); // Assuming there's a similar function for B
    }
    updateDisplay();
}

void checkScoreAPlus()
{
    switch (teamscore_a)
    {
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
        if (teamscore_b < 41)
        {
            teamscore_a = 41;
        }
        else
        {
            setScoreTo40();
        }
        break;
    case 41:
        if (teamscore_b < 41)
        {
            teamscore_a = 42
        }
        else
        {
            setScoreTo40();
        }
        break;
    default:
        break;
        ;
    }
}
void checkScoreAMinus(void)
{
    switch (teamscore_a)
    {
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
        break;
        ;
    }

    void checkScoreBPlus()
    {
        switch (teamscore_b)
        {
        case 0:
            teamscore_b = 15;
            break;
        case 15:
            teamscore_b = 30;
            break;
        case 30:
            teamscore_b = 40;
            break;
        case 40:
            if (teamscore_a < 41)
            {
                teamscore_b = 41;
            }
            else
            {
                setScoreTo40();
            }
            break;
        case 41:
            if (teamscore_a < 41)
            {
                teamscore_b = 42;
            }
            else
            {
                setScoreTo40();
            }
            break;
        default:
            break;
        }
    }

    void checkScoreBMinus(void)
    {
        switch (teamscore_b)
        {
        case 15:
            teamscore_b = 0; // If score is 15, decrement to 0
            break;
        case 30:
            teamscore_b = 15; // If score is 30, decrement to 15
            break;
        case 40:
            // If Team A is not in an advantage state and score is 40, decrement to 30
            // If Team A is in advantage, it means we are in a deuce situation
            if (teamscore_a == 41)
            {
                setScoreTo40(); // Set score back to 40-40 if it's a deuce
            }
            else
            {
                teamscore_b = 30;
            }
            break;
        case 41:
            // If Team B is in advantage, move back to 40
            teamscore_b = 40;
            break;
        case 42:
            // If Team B had won the game, move to advantage before losing the game
            teamscore_b = 41;
            break;
        }
        updateDisplay(); // Update the display after processing the decrement
    }
}
