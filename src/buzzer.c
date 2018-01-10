#include "buzzer.h"
#include "Commonheader.h"
#include "clock.h"
#include "lcd.h"

int current_alarm_duration;
DateTime alarmDuration;
bool quit;

void buzzerInit()
{
    TRISC5 = 0; /* Configure TRISB7 as o/p              */
    pin = 0;
}

void soundBuzzer(int duration, int zone)
{
    quit = false;
    clear_lines();
    char buf[16];
    sprintf(buf, "Zone %d", zone);
    Write_line(buf, 0);
    Write_line("activated", 1);
    unsigned char currentSecond = dateTime.Second;
    unsigned char currentMinute = dateTime.Minute;
    DateTime timeLeft;
    memcpy(&timeLeft, &alarmDuration, sizeof (dateTime));

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

        unsigned char sec = dateTime.Second;
        // unsigned char min = dateTime.Minute;
        if(currentSecond != sec)
        {

            currentSecond = sec;
            --timeLeft.Second;

            if(timeLeft.Minute == 0 && timeLeft.Second)
            {
                quit = true;
            }

            if(timeLeft.Second == 0)
            {
                --timeLeft.Minute;
                timeLeft.Second = 59;
            }
            sprintf(buf, "Time left: %02d:%02d", timeLeft.Minute, timeLeft.Second);

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