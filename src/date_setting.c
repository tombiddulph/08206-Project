/*
 * File:   date_setting.c
 * Author: 462767
 *
 * Created on 12 December 2017, 17:22
 */


#include "date_setting.h"

void Date_time_setting_loop()
{
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
    bool date_changed = false;
    int count = 0;
    int line = 0;

    while(1)
    {

       Write_line(line ?"Time selection": "Date selection", 0);
       Write_Date_Time_Settings(d, 1);

       char command = PORTB & BUTTON_MASK;


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
                    count = count == 5 ? 3 : count++;
                }
                else
                {
                     count = count == 2  ? 0 : count++;
                }                       
                break;
            case (TOGGLE_LINE):
                line = 1 - line;
                count = line ? 3 : 0;
                break;
            case (BACK):
                quit = true;
                break;
        }

        d = *convertDateFromArray(date);

            if(quit)
            {
                 if(date_changed)
                 {
                    Write_dateTime(&d);
                 }
                break;
            }
        }
}