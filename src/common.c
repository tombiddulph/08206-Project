#include "Commonheader.h"

void Delay_loop(int j )
{
    for (unsigned i=0; i<j; i++);
}

int ButtonCheck()
{
    int result = (PORTB & BUTTON_MASK);
        
  
        if(result && !(result & (result - 1))) // check to see if 1 and only 1 bit is set
        {
            lastPressed = result;
            int portN = result == 8 ? 0 : result == 4 ? 1 : result == 2 ? 2 : 3; //convert hex value to port number
            
            return portN;
        }
    return -1;
}

void ButtonInit()
{
    TRISB = 0x0F;
    PORTB = 0x00;
    
}