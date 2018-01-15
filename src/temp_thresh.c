#include "temp_thresh.h"
#include "lcd.h"

#define TEN_INCREMENT   0x01
#define TEN_DECREMENT   0x02
#define UNIT_INCREMENT  0x04
#define UNIT_DECREMENT 0x08
#define SAVE 0x10
#define MAX_TEMP 124
#define MIN_TEMP -54
#define MAX_TIME 60
#define MIN_TIME 0



short threshold_temp_LHS;
unsigned char threshold_temp_RHS;
unsigned char threshold_time = 1;
bool quit, displayedOnce, negativeFlag;

typedef enum {
    THRESH_TEMP, THRESH_TIME, OVERVIEW, EXIT
} ThermomiterSettingState;

ThermomiterSettingState currentThermState;

void update_threshold(char choice) {
    switch (choice) {
        case(TEN_INCREMENT):
            if (threshold_temp_LHS == 0 && negativeFlag) {
                negativeFlag = false;
            } else if (threshold_temp_LHS == -1) {
                negativeFlag = true;
                threshold_temp_LHS++;
            } else {

                if (threshold_temp_LHS == MAX_TEMP) {
                    threshold_temp_LHS = MIN_TEMP;

                } else {
                    threshold_temp_LHS++;
                }
            }
            break;
        case (TEN_DECREMENT):
            if (threshold_temp_LHS == 0) {
                if (!negativeFlag) {
                    negativeFlag = true;
                } else {
                    negativeFlag = false;
                    threshold_temp_LHS--;
                }
            } else {
                if (threshold_temp_LHS == MIN_TEMP) {

                    threshold_temp_LHS = MAX_TEMP;
                } else {
                    threshold_temp_LHS--;
                }
            }
            break;
        case (UNIT_INCREMENT):
            if (threshold_temp_RHS == 99) {
                threshold_temp_RHS = 0;
            } else {
                threshold_temp_RHS++;
            }
            break;
        case (UNIT_DECREMENT):
            if (threshold_temp_RHS == 0) {
                threshold_temp_RHS = 99;
            } else {
                threshold_temp_RHS--;
            }
            break;

        case (SAVE):
            quit = true;
            break;
    }

}

void setThresh() {


    char buf[7];
    if(negativeFlag){
        concat_strings(buf, "-");
    }
    char tempLhs[3];
    char tempRhs[3];
    int_to_string(tempLhs, threshold_temp_LHS);
    int_to_string(tempRhs, threshold_temp_RHS);
    concat_strings(buf, tempLhs);
    concat_strings(buf, ".");
    concat_strings(buf, tempRhs);
    //sprintf(buf, "%s%03d.%02d", negativeFlag ? "-" : " ",  threshold_temp_LHS, threshold_temp_RHS);
    Write_line(buf, 1);

    char escape = ((PORTE & BUTTON_MASK) << 4) | (PORTB & BUTTON_MASK);

    escape = ((PORTE & BUTTON_MASK) << 4) | (PORTB & BUTTON_MASK);
    if (single_key_pressed(escape)) {
        update_threshold(escape);


        if (quit) {
            clear_lines();

            char buf[16];
            //sprintf(buf ,"set to: %03d.%02d", threshold_temp_LHS, threshold_temp_RHS );

            Write_line("Thresh temp", 0);
            Write_line(buf, 1);
            Write_line("Press a button", 2);
            Write_line("to continue", 3);

            currentThermState = OVERVIEW;
            quit = displayedOnce = false;

            while ((!(PORTB & BUTTON_MASK)) && (!(PORTE & 0x07))) {
                /* do nothing */
            }

            clear_lines();
        }
    }
}

void updateTime() {
    char choice = ((PORTE & BUTTON_MASK) << 4) | (PORTB & BUTTON_MASK);

    switch (choice) {
        case(TEN_INCREMENT):
        {
            if (threshold_time == MAX_TIME) {
                threshold_time = MIN_TIME;
            } else {
                threshold_time++;
            }
            break;
        }
        case (TEN_DECREMENT):
        {
            if (threshold_time == MIN_TIME) {
                threshold_time = MAX_TIME;
            } else {
                threshold_time--;
            }
            break;
        }
        case (SAVE):
        {
            quit = true;
            break;
        }
    }


    if (quit) {
        clear_lines();

        char buf[16] = "";
        char time[2] = "";
        int_to_string(threshold_time, time);

        concat_strings(buf, "set to: ");
        concat_strings(buf, time);
        //sprintf(buf, "set to: %02d", threshold_time);

        Write_line("Thresh Time", 0);
        Write_line(buf, 1);
        Write_line("Press a button", 2);
        Write_line("to continue", 3);

        currentThermState = OVERVIEW;
        quit = displayedOnce = false;

        while ((!(PORTB & BUTTON_MASK)) && (!(PORTE & BUTTON_MASK))) {
            /* do nothing */
        }
        clear_lines();
    } else {
        char buf[2];
        //sprintf(buf, "%02d", threshold_time);
        Write_line(buf, 1);
    }

}

void overviewPage() {


    char choice = ((PORTE & BUTTON_MASK) << 4) | (PORTB & BUTTON_MASK);

    switch (choice) {
        case(TEN_INCREMENT):
        {
            currentThermState = THRESH_TEMP;
            break;
        }
        case (TEN_DECREMENT):
        {
            currentThermState = THRESH_TIME;
            break;
        }
        case(UNIT_INCREMENT):
        {
            currentThermState = EXIT;
            break;
        }
    }
}

void tempThreshLoop() {
    clear_lines();
    currentThermState = OVERVIEW;
    quit = displayedOnce = false;



    while (1) {
        updateVariables();
        switch (currentThermState) {
            case(OVERVIEW):
            {
                Write_line("1. Thresh Temp", 0);
                Write_line("2. Thresh Time", 1);
                Write_line("3. EXIT", 2);
                overviewPage();
                break;
            }
            case(THRESH_TEMP):
            {
                if (!displayedOnce) {
                    clear_lines();
                    Write_line("Thresh temp:", 0);
                    displayedOnce = true;
                }
                setThresh();
                break;
            }
            case(THRESH_TIME):
            {
                if (!displayedOnce) {
                    clear_lines();
                    Write_line("Trigger time(s):", 0);
                    char time[2]="";
                    int_to_string(time, threshold_time);
                    //sprintf(time, "%02d ", threshold_time);

                    displayedOnce = true;
                }

                updateTime();
                break;
            }
            case(EXIT):
            {
                return;
            }
        }
    }
}