

#include "buzzer.h"
#include <pic.h>


void buzzerInit()
{
    TRISD = 0;               /* Configure TRISD as o/p              */
}


void soundBuzzer()
{
    while(1)
 {
     if(pin == 0)
     {
         pin = 1;
         delay(1000);
     }
     else
     {
         pin = 0;
         delay(1000);
     } 
 }
    
}