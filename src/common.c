#include "Commonheader.h"

void Delay_loop(int j )
{
    for (unsigned i=0; i<j; i++);
}
int convert_to_bit_pos(int pinNum)
{
   
    return (1 << pinNum);
}
int convert_from_bit_pos(int bitPos)
{
    int val = 0 ;
    while(bitPos >>= 1)
    {
        ++val;
    }
    return val;
}

char *formatString(char *inputstr, char *format)
{
    char buf[16];
    sprintf(buf, format, inputstr);
    return *buf;
}

bool single_key_pressed(char byteVal)
{
    return byteVal && !(byteVal & (byteVal - 1));
}


DateTime *convertDateFromArray(char input[])
{
     
 
    char *ptr = input;
     DateTime d;
     d.Day    = *ptr++;
     d.Month  = *ptr++;
     d.Year   = *ptr++;
     d.Hour   = *ptr++;
     d.Minute = *ptr++; 
     d.Second = *ptr; 
  
     

    

 
    
     return &d;
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
    
    TRISE0 = 1;
    TRISE1 = 1;
    TRISE2 = 1;
    RE0 = RE1 = RE2 = 0;
    
}

unsigned char bcd_to_decimal(unsigned char val)
{
  return ((val & 0x0F) + (((val & 0xF0) >> 4) * 10));
}
unsigned char decimal_to_bcd(unsigned char val)
{
    return (((val / 10) << 4) & 0xF0) | ((val % 10) & 0x0F);
}