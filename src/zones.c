
#include "zones.h"
#include <pic.h>
#include "buzzer.h"
#include "lcd.h"

#define ZONE0   0x01
#define ZONE1   0x02
#define ZONE2   0x04
#define ZONE3   0x08

bool temperatureAlarm;

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
    int finalMask = 0;
    
    char mask = 0x01;
    
    for(int i =0; i < 4; ++i)
    {
      if(activeZones[i])
      {
           finalMask |= mask;
      }
      mask = mask << 1;
    }
    

    //char tmp = ((PORTC & ZONE_MASK) & temperatureAlarm) & finalMask
    
    
    if(((PORTC & ZONE_MASK) | temperatureAlarm) & finalMask)
    {
        soundBuzzer(); //pass current time
    }
    if(PORTC & ZONE_MASK)
    {
        TRISC = 0x00;
        PORTC = 0x00;
        TRISC = 0x0F;
    }
  
  
}

void ZoneLoop()
{
    while(1)
    {  
        int butt = -1;
        
        char command = (PORTB & BUTTON_MASK);
        
        if (single_key_pressed(command))
        {
            butt = convert_from_bit_pos(command);
            SetZone(butt); 
           
            char duf[10];
            sprintf(duf, "Zone 0: %d", activeZones[0]);
            Write_line(duf,0);

            sprintf(duf, "Zone 1: %d", activeZones[1]);
            Write_line(duf,1);

            sprintf(duf, "Zone 2: %d", activeZones[2]);
            Write_line(duf,2);

            sprintf(duf, "Zone 3: %d", activeZones[3]);
            Write_line(duf,3);
            
        }
        
        if(butt != -1)
        {
            prevButt = butt;
        }
   
        updateVariables();
    }
}
