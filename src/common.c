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

unsigned char bcd_to_decimal(unsigned char val)
{
  return ((val & 0x0F) + (((val & 0xF0) >> 4) * 10));
}
unsigned char decimal_to_bcd(unsigned char val)
{
    return (((val / 10) << 4) & 0xF0) | ((val % 10) & 0x0F);
}