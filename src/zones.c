#include "Commonheader.h"
#include "zones.h"
#include "buzzer.h"
#include "lcd.h"
#include "clock.h"

#define ZONE0   0x01
#define ZONE1   0x02
#define ZONE2   0x04
#define ZONE3   0x08
#define EXIT_MASK   0x1

bool temperatureAlarm;
bool activeZones[4];
bool sounded = false;


void SetZone(int zone)
{
    activeZones[zone] = !activeZones[zone];
}

void ZoneInit()
{
    TRISC = 0x0F;
    PORTC = 0x00;
}

void ZoneCheck()
{
    Update_Global_DateTime();

    if((dateTime.Hour < 8 || dateTime.Hour > 20) || (dateTime.Hour == 19 && dateTime.Minute >= 30))
    {
        return;
    }

    int finalMask = 0;

    char mask = 0x01;

    for(int i = 0; i < 4; ++i)
    {
        if(activeZones[i])
        {
            finalMask |= mask;
        }
        mask = mask << 1;
    }


    if(((PORTC & ZONE_MASK) | temperatureAlarm) & finalMask)
    {

        char activatedZone;
        if(temperatureAlarm & finalMask)
        {
            activatedZone = 0;
        } else
        {
            activatedZone = convert_from_bit_pos(PORTC & ZONE_MASK);
        }

        if(!sounded)
        {
            soundBuzzer(activatedZone);
            sounded = true;
        }


    }
    if(PORTC & ZONE_MASK)
    {
        TRISC = 0x00;
        PORTC = 0x00;
        TRISC = 0x0F;
    }


}

void Display_Zones()
{
    char buf[10];

    for(char i = 0; i < 4; i++)
    {
        sprintf(buf, "Zone %d: %d", i, activeZones[i]);
        Write_line(buf, i);
    }
}

void ZoneLoop()
{
    Display_Zones();
    

    while (1)
    {
        int butt = -1;

        unsigned command = (PORTB & BUTTON_MASK);
        Delay_loop(10000);
        command = (PORTB & BUTTON_MASK);
        unsigned exit = (PORTE & EXIT_MASK);

        if(exit)
        {
            break;
        }

        if(sounded)
        {
            sounded = false;
            Display_Zones();
        }

        if(single_key_pressed(command))
        {
            butt = convert_from_bit_pos(command);
            SetZone(butt);
            Display_Zones();
        }


        updateVariables();
    }
}