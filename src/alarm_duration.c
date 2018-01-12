#include "alarm_duration.h"
#include "Commonheader.h"
#include "lcd.h"

#define INCREMENT_MINUTES   0x01
#define DECREMENT_MINUTES   0x02
#define INCREMENT_SECONDS   0x04
#define DECREMENT_SECONDS   0x08
#define SAVE_DURATION       0x10

bool quit;

char alarmDurationMinutes;
char alarmDurationSeconds;

void alarm_duration_settings_page()
{
    quit = false;
    clear_lines();
    while (1)
    {
        Write_line("ALARM DURATION:", 0);
        char buf[16];
        sprintf(buf, "%02d:%02d", alarmDurationMinutes, alarmDurationSeconds);
        Write_line(buf, 1);


        char choice = ((PORTE & 0x07) << 4) | (PORTB & BUTTON_MASK);

        if(single_key_pressed(choice))
        {
            switch(choice)
            {
                case(INCREMENT_MINUTES):
                    if(alarmDurationMinutes == 30)
                    {
                        alarmDurationMinutes = 1;
                    }
                    else
                    {
                        alarmDurationMinutes++;
                        if(alarmDurationMinutes == 30)
                        {
                            alarmDurationSeconds = 0;
                        }
                    }
                    break;
                case (DECREMENT_MINUTES):
                    if(alarmDurationMinutes == 1)
                    {
                        alarmDurationMinutes = 30;
                        alarmDurationSeconds = 0;
                    }
                    else
                    {
                        alarmDurationMinutes--;
                    }
                    break;

                case (INCREMENT_SECONDS):
                {
                    if(alarmDurationSeconds == 60)
                    {
                        alarmDurationSeconds = 0;
                    }
                    else
                    {
                        if(alarmDurationMinutes != 30)
                        {
                            alarmDurationSeconds++;
                        }
                    }
                }
                    break;
                case (DECREMENT_SECONDS):
                {
                    if(alarmDurationSeconds == 0)
                    {
                        if(alarmDurationMinutes != 30)
                        {
                            alarmDurationSeconds = 60;
                        }
                    }
                    else
                    {
                        alarmDurationSeconds--;
                    }
                }
                    break;
                case (SAVE_DURATION):
                    quit = true;
                    break;
            }

            if(quit)
            {
                clear_lines();

            
                sprintf(buf, "set to: %02d:%02d", alarmDurationMinutes, alarmDurationSeconds);

                Write_line("Alarm duration", 0);
                Write_line(buf, 1);
                Write_line("press a button", 2);
                Write_line("to continue", 3);

                while (!(PORTB & BUTTON_MASK) && (!(PORTE & 0x7)))
                {
                    /* do nothing */
                }

                break;
            }
        }
    }

}