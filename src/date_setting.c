/*
 * File:   date_setting.c
 * Author: 462767
 *
 * Created on 12 December 2017, 17:22
 */

#include "Commonheader.h"
#include "date_setting.h"

/*
 Local constants
 */
#define DATE_OFFSET 0
#define TIME_OFFSET 2
#define LEFT_BUTTONS  PORTE
#define RIGHT_BUTTONS PORTB
#define DAY     0
#define MONTH   1
#define YEAR    2
#define HOUR    3
#define MINUTE  4
#define SECOND  5

/*
 local function prototypes
 */

void set_leap_year_status();
void Init();
void Update_values();

/*
 type definitions
 */
typedef enum {
    DATE, TIME, OVERVIEW
} DateTimeSettingState;
typedef void(*display_function)(DateTime *date, int lineNo);

/*
 local variables
 */
DateTimeSettingState currentDTstate;
display_function write_functions[2] = {Write_Date_Settings, Write_Time_Settings};

bool quit;
bool date_changed;
bool line_changed;
bool new_date_time_set;
bool leap_set;
bool month_changed;
char count;
char cursor_position;

int days_per_month [12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char title[15];
unsigned char command;
char date[6];
char year;

/*
 Initialize local variables
 */
void Init() {
    cursor_position = START_CURSOR_POSITION;
    count = 0;
    quit = false;
    date_changed = true;
    line_changed = true;
    new_date_time_set = false;
    leap_set = false;
    clear_lines();

    DateTime *dateTime = get_current_date_time();


    date[DAY] = dateTime->Day;
    date[MONTH] = dateTime->Month;
    date[YEAR] = dateTime->Year;
    date[HOUR] = dateTime->Hour;
    date[MINUTE] = dateTime->Minute;
    date[SECOND] = dateTime->Second;
}

void Date_time_setting_loop() {

    Init();

    currentDTstate = OVERVIEW;


    while (1) {
        if (currentDTstate == OVERVIEW) {
            Write_line("1: DATE", 0);
            Write_line("2: TIME", 1);
            Write_line("3: EXIT", 2);

            command = RIGHT_BUTTONS & BUTTON_MASK;
            Delay_loop(9999);
            command = RIGHT_BUTTONS & BUTTON_MASK;


            if (single_key_pressed(command)) {
                switch (command) {
                    case (1):
                        currentDTstate = DATE;
                        break;
                    case (2):
                        currentDTstate = TIME;
                        break;
                    case (4):
                        return;
                }
                count = currentDTstate == 1 ? 3 : 0;
                cmd(DISPLAY_CURSOR_BLINK_ON);
            }



        } else {
            switch (currentDTstate) {
                case (DATE):
                    str_cpy(title, "Date selection");
                    break;
                case (TIME):
                    str_cpy(title, "Time selection");
                    break;
            }

            if (line_changed) {
                line_changed = false;
                Write_line(title, 0);
                write_functions[currentDTstate](convertDateFromArray(date), 1);
            }

            if (date_changed) {
                write_functions[currentDTstate](convertDateFromArray(date), 1);
                date_changed = false;
            }

            cmd(cursor_position);


            if (new_date_time_set) {
                clear_lines();

                switch (currentDTstate) {
                    case (DATE):
                        Write_line("Date updated", 0);
                        Write_updated_date_rtc(convertDateFromArray(date));
                        break;
                    case (TIME):
                        Write_line("Time updated", 0);
                        Write_updated_time_rtc(convertDateFromArray(date));
                        break;
                }
                Write_line("Press any key", 1);
                Write_line("to continue", 2);
                currentDTstate = OVERVIEW;

                while (!(LEFT_BUTTONS & BUTTON_MASK) && !(RIGHT_BUTTONS & BUTTON_MASK)) {
                    /* do nothing */
                }
                new_date_time_set = false;
                line_changed = true;
                cmd(DISPLAY_ON);
            }




            Update_values();






        }
    }
}

void Update_values() {


    command = ((LEFT_BUTTONS & BUTTON_MASK) << 4) | (RIGHT_BUTTONS & BUTTON_MASK);
    Delay_loop(9999);
    command = ((LEFT_BUTTONS & BUTTON_MASK) << 4) | (RIGHT_BUTTONS & BUTTON_MASK);

    switch (command) {
        case (0):
            break;
        case (INCREMENT):
            switch (count) {
                case (DAY):

                    if (date[DAY] >= days_per_month[date[MONTH] - 1]) {
                        date[DAY] = 1;
                    } else {
                        date[DAY]++;
                    }

                    break;

                case (MONTH):
                    if (date[MONTH] == 12) {
                        date[MONTH] = 1;
                    } else {
                        date[MONTH]++;
                    }
                    month_changed = true;
                    set_leap_year_status();

                    if (date[DAY] > days_per_month[date[MONTH] - 1 ]) {
                        date[DAY] = days_per_month[date[MONTH] - 1];
                    }
                    break;
                case (YEAR):
                    date[YEAR]++;

                    set_leap_year_status();

                    break;
                case (HOUR):
                    if (date[HOUR] == 23) {
                        date[HOUR] = 0;
                    } else {
                        date[HOUR]++;
                    }
                    break;
                case (MINUTE):
                case (SECOND):
                    if (date[count] == 59) {
                        date[count] = 0;
                    } else {
                        date[count]++;
                    }
            }

            date_changed = true;
            break;
        case (DECREMENT):
            switch (count) {
                case (DAY):
                    if (date[DAY] == 1) {
                        date[DAY] = days_per_month[date[MONTH] - 1];
                    } else {
                        date[DAY]--;
                    }

                    break;
                case (MONTH):
                    if (date[MONTH] == 1) {
                        date[MONTH] = 12;
                    } else {
                        date[MONTH]--;
                    }

                    month_changed = true;


                    set_leap_year_status();
                    if (date[DAY] > (days_per_month[date[MONTH] - 1])) {
                        date[DAY] = days_per_month[date[MONTH] - 1];
                    }
                    break;
                case (YEAR):
                    date[YEAR]--;
                    set_leap_year_status();
                    break;
                case (HOUR):
                    if (date[HOUR] == 0) {
                        date[HOUR] = 23;
                    } else {
                        date[HOUR]--;
                    }


                    break;
                case (MINUTE):
                case (SECOND):

                    if (date[count] == 0) {
                        date[count] = 59;
                    } else {
                        date[count]--;
                    }
            }

            date_changed = true;
            break;
        case (MOVE_RIGHT):
            if (currentDTstate) {
                if (count == 5) {
                    count = 3;
                    cursor_position = START_CURSOR_POSITION;
                } else {
                    count++;
                    cursor_position += 2;
                }
            } else {
                if (count == 2) {
                    count = 0;
                    cursor_position = START_CURSOR_POSITION;
                } else {
                    count++;
                    cursor_position += 2;
                }
            }
            break;

        case (MOVE_LEFT):
            if (currentDTstate) {
                if (count == 3) {
                    count = 5;
                    cursor_position = START_CURSOR_POSITION + 4;
                } else {
                    count--;
                    cursor_position -= 2;
                }
            } else {
                if (count == 0) {
                    count = 2;
                    cursor_position = START_CURSOR_POSITION + 4;
                } else {
                    count--;
                    cursor_position -= 2;
                }
            }
            break;
        case (TOGGLE_LINE):
            currentDTstate = 1 - currentDTstate;
            count = currentDTstate == 1 ? 3 : 0;
            line_changed = true;
            break;
        case (SET):
            new_date_time_set = true;
            cmd(DISPLAY_ON);
            break;
    }

}

/*
 Adds an extra day to the month of february if the year is a leap year
 */

void set_leap_year_status() {
    year = 2000 + date[YEAR];

    if (((year & 3) == 0 && ((year % 25) != 0 || (year & 15) == 0)) && date[MONTH] == 2) {
        if (month_changed) {
            days_per_month[1]++;
            leap_set = true;
            month_changed = false;
        }
    } else if (leap_set) {
        days_per_month[1]--;
    }
}