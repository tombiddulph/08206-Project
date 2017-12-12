
#include "zones.h"
#include <pic.h>
#include "buzzer.h"

  

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
    
    for(int i =0; i < 4; ++i)
    {
      int mask = 0x01;
      
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
