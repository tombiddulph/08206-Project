#include "buzzer.h"
#include "Commonheader.h"
#include "clock.h"
#include "lcd.h"
#include <stdlib.h>

int current_alarm_duration;
bool quit;
char alarmDurationMinutes;
char alarmDurationSeconds;
void buzzerInit()
{
    TRISC5 = 0; /* Configure TRISB7 as o/p              */
    pin = 0;
}

void soundBuzzer( int zone)
{
    quit = false;
    clear_lines();
    char buf[16];
    sprintf(buf, "Zone %d", zone);
    Write_line(buf, 0);
    Write_line("activated", 1);
    DateTime dateTime;
    get_updated_date_time(&dateTime);
    
    int totalSecs = (alarmDurationMinutes * 60) + alarmDurationSeconds;
    char currentSec = dateTime.Second;
    
    

    //unsigned char countDownsec = (targetMin - dateTime.Minute)
    
    while (1)
    {

        if(PORTB & 0x01 || quit)
        {
            clear_lines();
            Write_line("Deactivated", 0);
            Write_line("Press any key", 1);
            Write_line("To continue", 2);

            while (!(PORTB & BUTTON_MASK))
            {
                /* do nothing */
            }
            clear_lines();
            return;
        }


        get_time_rtc();
        get_updated_date_time(&dateTime);

      

        if(totalSecs == 0)
        {
            quit = true;
        }
        else if(currentSec != dateTime.Second)
        {
            currentSec = dateTime.Second;
            --totalSecs;
            sprintf(buf, "Time left %02d:%02d", totalSecs /60, totalSecs % 60);
            Write_line(buf, 2);
        }
        
        RC5 = 1;
        Delay_loop(1000);
        RC5 = 0;
        Delay_loop(1000);
        RC5 = 1;
        Delay_loop(1000);
        RC5 = 0;
        Delay_loop(1000);
    }

}