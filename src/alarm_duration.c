#include "alarm_duration.h"
#include "Commonheader.h"
#include "lcd.h"

#define SAVE_DURATION 0x04

bool quit;

void alarm_duration_settings_page()
{
    quit = false;
    clear_lines();
    while(1)
    {
        Write_line("DURATION:", 0);
        char buf[5];
        sprintf(buf, "%ds", current_alarm_duration);
        Write_line(buf, 1);
        
        
        char  choice  = (PORTB & BUTTON_MASK);
        
        if(single_key_pressed(choice))
        {
            switch(choice)
            {
                case(INCREMENT):
                    if(current_alarm_duration == 60)
                    {
                        current_alarm_duration = 0;
                    }
                    else
                    {
                        current_alarm_duration++;
                    }
                    break;
                case (DECREMENT):
                    if(current_alarm_duration == 0)
                    {
                        current_alarm_duration = 60;
                    }
                    else
                    {
                        current_alarm_duration--;
                    }
                    break;
                case (SAVE_DURATION):
                    quit = true;
                    break;
            }
            
            if(quit)
            {
                clear_lines();
                
                char buf[16];
                sprintf(buf ,"set to: %ds",current_alarm_duration );
                
                Write_line("Alarm duration", 0);
                Write_line(buf, 1);
                Write_line("Press a button", 2);
                Write_line("to continue", 3);
                        
                while (!(PORTB & BUTTON_MASK))
                {
                    /* do nothing */
                }
                
                break;
            }
        }
    }
    
}