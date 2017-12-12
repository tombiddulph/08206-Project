/*
 * File:   date_setting.c
 * Author: 462767
 *
 * Created on 12 December 2017, 17:22
 */


#include "date_setting.h"

//typedef void (*page_ptr)(void);
typedef void(*date_write)(DateTime date, int lineNo);
date_write write_functions[2] = {Write_Date_Settings, Write_Time_Settings};

void Date_time_setting_loop()
{
    clear_lines();
    DateTime d;
    memcpy(&d, &dateTime, sizeof(dateTime));

    char date[6];
    date[0] = d.Day;
    date[1] = d.Month;
    date[2] = d.Year;
    date[3] = d.Hour;
    date[4] = d.Minute;
    date[5] = d.Second;
    bool quit = false;
    bool date_changed = true;
    bool line_changed = true;
    bool set = false;
    int count = 0;
    int line = 0;
    int startAddress = 0x48;
    char command;
   
    while(1)
    {

        if(line_changed)
        {
            line_changed =  false;
            Write_line(line ? "Time selection": "Date selection", 0);
            write_functions[line](d, 1);
        }
       if(date_changed)
       {
          write_functions[line](d, 1);
          date_changed = false;
       }
        
       cmd(startAddress);

       command = PORTE & BUTTON_MASK;
       Delay_loop(9999);
       command = PORTE & BUTTON_MASK;
       
        switch(command)
        {
            case(0):
                break;
            case (TOGGLE_LINE):
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
        
        if(set)
        {
            
            Write_dateTime_rtc(&d);
            clear_lines();
            Write_line("Datetime updated", 0);
            Write_line("Press any key", 1);
            Write_line("to continue", 2);
            
            while(!(PORTE & BUTTON_MASK) && !(PORTB & BUTTON_MASK))
            {
            }
            set = false;
            line_changed = true;
            cmd(DISPLAY_CURSOR_BLINK_ON);
        }
        
        if(quit)
        {

            break;
        }
      
      
        command = PORTB & BUTTON_MASK;
        Delay_loop(9999);
        command = PORTB & BUTTON_MASK;
        
        switch(command)
        {
            case (0):
                break;
            case(INCREMENT):  
                date[count]++;
                date_changed = true;
                break;
            case (DECREMENT):
                date[count]--;
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
        
        

        d = *convertDateFromArray(date);

           
        }
    
    if(date_changed)
     {
       Write_dateTime_rtc(&d);
       clear_lines();
       Write_line("Datetime updated", 0);
       Delay_loop(999999);
     }
}