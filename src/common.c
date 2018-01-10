#include "Commonheader.h"

void Delay_loop(int j )
{
    for (unsigned i=0; i<j; i++);
}

unsigned char convert_from_bit_pos(unsigned char  bitPos)
{
    int val = 0 ;
    while(bitPos >>= 1)
    {
        ++val;
    }
    return val;
}

unsigned char convert_to_bit_pos(unsigned char pinNum)
{
   return (1 << pinNum);
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


void ButtonInit()
{
    TRISB = 0x0F;
    PORTB = 0x00;
    
    TRISE0 = 1;
    TRISE1 = 1;
    TRISE2 = 1;
    RE0 = RE1 = RE2 = 0;
    
}

unsigned char convert_bcd_to_dec(unsigned char val)
{
  return ((val & 0x0F) + (((val & 0xF0) >> 4) * 10));
}
unsigned char convert_dec_to_bcd(unsigned char val)
{
    return (((val / 10) << 4) & 0xF0) | ((val % 10) & 0x0F);
}