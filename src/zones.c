
#include "zones.h"
#include <pic.h>
#include "buzzer.h"
#include "lcd.h"

  

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
    
//    int btn = (PORTC & ZONE_MASK);
//    char buf1[15];
//    sprintf(buf1, "button val %d ", btn);
//    Write_line(buf1, 1);
    
    if((PORTC & (ZONE_MASK & finalMask)) > 0)
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
        
        int butt = ButtonCheck();
        
        if(butt != -1)
        {
//            char buf[12];
//            sprintf(buf, "RB%d pressed", butt);
//            Write_line(buf,3);


            if(prevButt != butt)
            {
               SetZone(butt);
            }
             


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
        
        ZoneCheck();
        
        
        
        prevButt = butt;
    }
}
