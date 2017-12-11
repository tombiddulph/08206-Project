

#include "buzzer.h"
#include <xc.h>
#include "Commonheader.h"


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
         Delay_loop(1000);
     }
     else
     {
         pin = 0;
         Delay_loop(1000);
     } 
 }
    
}