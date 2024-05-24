
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
}

void resetScore(void)
{
    teamscore_a = 0;
    teamscore_b = 0;
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

void handle_buttons(void) {


    #if 1
    if (buttons_1_pressed() && buttons_2_pressed()) {
        checkScoreAMinus();
    } else if (buttons_1_pressed()) {
        checkScoreAPlus();
    } else if (buttons_2_pressed() && buttons_3_pressed()) {
        checkScoreBMinus();
    } else if (buttons_2_pressed()) {
        resetScore();
    } else if (buttons_3_pressed()) {
        checkScoreBPlus();
    }
    updateDisplay();
    #endif
}


void checkScoreAPlus(void)
{
    if (teamscore_b == 42) {
        return;
    }
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
            teamscore_a = 42;
            tone_play_final_fantasy_victory();
            led_blink(20);
        } else
        {
            setScoreTo40();
        }
        break;
    default:
        break;
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
        
    }
}

void checkScoreBPlus(void)
    {
         if (teamscore_a == 42) {
        return;
    }

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
                tone_play_final_fantasy_victory();
                led_blink(20);
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
            teamscore_b = 0; 
            break;
        case 30:
            teamscore_b = 15; 
            break;
        case 40:
            if (teamscore_a == 41)
            {
                setScoreTo40(); 
            }
            else
            {
                teamscore_b = 30;
            }
            break;
        case 41:
            teamscore_b = 40;
            break;
        case 42:
            teamscore_b = 41;
            break;
        }
    }

