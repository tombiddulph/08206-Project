#include "buzzer.h"
#include "Commonheader.h"
#include "clock.h"
#include "lcd.h"

int current_alarm_duration;
DateTime alarmDuration;
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
    char buf[16] = "";
   // sprintf(buf, "Zone %d", zone);
    char tmp[1];
    int_to_string(tmp, zone);
    concat_strings(buf, "Zone ");
    concat_strings(buf, tmp);
    Write_line(buf, 0);
    Write_line("activated", 1);

    unsigned char targetHour =
            (dateTime.Minute + alarmDurationMinutes > 60) || (dateTime.Minute + alarmDurationMinutes > 60 && dateTime.Second + alarmDurationSeconds > 60) ?
            dateTime.Hour + 1 : dateTime.Hour;

    
    unsigned char targetMin = dateTime.Minute + alarmDurationMinutes > 60 ? dateTime.Minute - alarmDurationMinutes : dateTime.Minute + alarmDurationMinutes;
    unsigned char targetSec = dateTime.Second + alarmDurationSeconds > 60 ? dateTime.Second - alarmDurationSeconds : dateTime.Second + alarmDurationSeconds;

    
    if(targetMin < dateTime.Minute)
    {
        targetMin += 60;
    }
    unsigned char currentSec = dateTime.Second;
    unsigned char countDownSecs = (((targetMin - dateTime.Minute)*60)%60) + dateTime.Second;

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
        Update_Global_DateTime();

      

        if(dateTime.Hour == targetHour && dateTime.Minute == targetMin && dateTime.Second >= targetSec)
        {
            quit = true;
        }
        else if(currentSec != dateTime.Second)
        {
            currentSec = dateTime.Second;
            countDownSecs--;
            //sprintf(buf, "Time left %02d:%02d", targetMin - dateTime.Minute, countDownSecs % 60);
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