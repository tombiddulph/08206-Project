/*
 * File:   date_setting.c
 * Author: 462767
 *
 * Created on 12 December 2017, 17:22
 */


#include "date_setting.h"

typedef enum  {DATE, TIME, OVERVIEW} DateTimeSettingState;

DateTimeSettingState currentDTstate;
void Left_buttons();
void Right_buttons();

//typedef void (*page_ptr)(void);
typedef void(*display_function)(DateTime date, int lineNo);
typedef void(*settings_function)(void);
display_function write_functions[2] = {Write_Date_Settings, Write_Time_Settings};
settings_function settings_functions[2] = { Left_buttons, Right_buttons };
bool quit;
bool date_changed;
bool line_changed;
bool set;
bool is_leap_year;

int count = 0;
int line = 0;
int startAddress = 0x48;
char command;
DateTime newDate;
char date[6];

#define DAY     0
#define MONTH   1
#define YEAR    2
#define HOUR    3
#define MINUTE  4
#define SECOND  5

const int days_per_month [12]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void Init()
{
    
    quit = false;
    date_changed = true;
    line_changed = true;
    set = false;
    is_leap_year = false;
    clear_lines();
   
    memcpy(&newDate, &dateTime, sizeof(dateTime));
    
    
    date[DAY] = newDate.Day;
    date[MONTH] = newDate.Month;
    date[YEAR] = newDate.Year;
    date[HOUR] = newDate.Hour;
    date[MINUTE] = newDate.Minute;
    date[SECOND] = newDate.Second;
}

void Date_time_setting_loop()
{
    
    Init();
    char title[15];
    currentDTstate = OVERVIEW;
    
    
    while(1)
    {
        if(currentDTstate == OVERVIEW)
        {
            Write_line("1: Date", 0);
            Write_line("2: Time", 1);
            
            command = PORTB & BUTTON_MASK;
            Delay_loop(9999);
            command = PORTB & BUTTON_MASK;
            
            
            if(single_key_pressed(command))
            {
                 switch(command)
                {
                    case(1):
                        currentDTstate = DATE;
                    break;
                     case(2):
                        currentDTstate = TIME;
                    break;
                }
            }
            
            
           
        }
        else
        {
            switch(currentDTstate)
            {
                case (DATE):
                    strcpy(title, "Date selection");
                    break;
                case (TIME):
                    strcpy(title, "Time selection");
                    break;
            }
            
            if(line_changed)
            {
                line_changed =  false;
                Write_line(title, 0);
                write_functions[currentDTstate](newDate, 1);
            }
           
            if(date_changed)
            {
               write_functions[line](newDate, 1);
               date_changed = false;
            }
            
             cmd(startAddress);
            
        
        
      
       
        Left_buttons();
      

      
        
        if(set)
        {
           
            
                 clear_lines();
            
         switch(currentDTstate)
        {
            case (DATE):
                Write_line("Date updated", 0);
                Write_updated_date_rtc(&newDate);
                break;
            case (TIME):
                Write_line("Time update", 0);
                Write_updated_time_rtc(&newDate);
                break;
        }
         Write_line("Press any key", 1);
            Write_line("to continue", 2);
            
            
            while(!(PORTE & BUTTON_MASK) && !(PORTB & BUTTON_MASK))
            {
                /* do nothing */
            }
            set = false;
            line_changed = true;
            cmd(DISPLAY_CURSOR_BLINK_ON);
        }
        
        if(quit)
        {

            break;
        }
      
      
        Right_buttons();
        
        

        newDate = *convertDateFromArray(date);

           
     }
    }   
}

void Left_buttons()
{
    command = PORTE & BUTTON_MASK;
    Delay_loop(9999);
    command = PORTE & BUTTON_MASK;
       
    switch(command)
    {
        case(0):
            break;
        case (TOGGLE_LINE):
            currentDTstate = 1 - currentDTstate;
            line = 1 - line;
            count = line ? 3 : 0;
            line_changed = true;
            break;
        case (BACK):
            quit = true;
            break;
        case (SET):
            set = true;
            cmd(DISPLAY_ON);
            break;
    }
}


void Right_buttons()
{
    command = PORTB & BUTTON_MASK;
    Delay_loop(9999);
    command = PORTB & BUTTON_MASK;
        
    switch(command)
    {
        case (0):
            break;
        case(INCREMENT):  
                switch(count)
                {
                    case (DAY):
                        
                        date[DAY] = date[DAY] > days_per_month[date[MONTH]] ? 0 : date[DAY]++;
                       
                    case (MONTH):
                        date[MONTH] = date[MONTH] > 12 ? 0 : date[MONTH]++;
                       
                        if(date[DAY] > days_per_month[date[MONTH]])
                        {
                            date[DAY] = days_per_month[date[MONTH]];
                        }
                        break;
                    case (YEAR):
                        date[YEAR]++;
                        //is_leap_year = (((date[YEAR] % 4) == 0) && (date[YEAR] % 100 != 0) || (date[YEAR] % 400 = 0);
                        break;
                    case (HOUR):
                        date[HOUR] = date[HOUR] > 23 ? 0 : date[HOUR]++;
                        
                    case(MINUTE):
                    case(SECOND):
                        
                        date[count] = date[count] > 59 ? 0 : date[count]++;
                       
                }
            date_changed = true;
            break;
        case (DECREMENT):
             switch(count)
                {
                    case (DAY):
                        date[DAY] = date[DAY] == 0 ?  days_per_month[date[MONTH]] : date[DAY]--;
                        
                    case (MONTH):
                         date[MONTH] = date[MONTH] == 0 ?  12 : date[MONTH]--;
                       
                        
                        if(date[DAY] > days_per_month[date[MONTH]])
                        {
                            date[DAY] = days_per_month[date[MONTH]];
                        }
                        break;
                    case (YEAR):
                        date[YEAR]--;
                        break;
                    case (HOUR):
                         date[HOUR] = date[HOUR] == 0 ?  23 : date[HOUR]--;
                       
                        break;
                    case(MINUTE):
                    case(SECOND):
                        date[count] = date[count] == 0 ? 59 : date[count]--;
                        
                }
           
            date_changed = true;
            break;
        case (MOVE_RIGHT):
            if(line)
            {
                if(count == 5)
                {
                    count = 3;
                    startAddress = START_CURSOR_POSITION;
                }
                else
                {
                    count++;
                    startAddress += 2;
                }
            }
            else
            {
                if(count == 2)
                {
                    count = 0;
                    startAddress = START_CURSOR_POSITION;
                }
                else
                {
                    count++;
                    startAddress += 2 ;
                }
            }
            break;

        case (MOVE_LEFT):
             if(line)
                {
                if(count == 3)
                {
                    count = 5;
                    startAddress = START_CURSOR_POSITION + 4;
                }
                else
                {
                    count--;
                    startAddress -= 2;
                }
            }
            else
            {
                if(count == 0)
                {
                    count = 2;
                    startAddress = START_CURSOR_POSITION + 4;
                }
                else
                {
                    count--;
                    startAddress -= 2 ;
                }
            }
            break;
        }

}