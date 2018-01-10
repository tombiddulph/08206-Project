#include "buzzer.h"
#include "Commonheader.h"
#include "clock.h"
#include "lcd.h"

int current_alarm_duration;

void buzzerInit()
{
	TRISC5 = 0;               /* Configure TRISB7 as o/p              */
	pin = 0;
}


void soundBuzzer(int duration, int zone)
{
    clear_lines();
    char buf[16];
    sprintf(buf, "Zone %d", zone);
    Write_line(buf, 0);
    Write_line("activated",1);
	unsigned char currentSecond = dateTime.Second;
    int timeLeft = current_alarm_duration;  
    while(timeLeft >= 0)
    {
        
        if(PORTB & 0x01 || timeLeft == 0)
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
          Get_time_rtc();
          Update_Global_DateTime();  
          
          char tmp = dateTime.Second;
          if(currentSecond != tmp)
          {
            currentSecond = tmp;
            --timeLeft;
            sprintf(buf, "Time left: %d s", timeLeft);
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