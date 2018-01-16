#include "Commonheader.h"

void Delay_loop(unsigned long j)
{
    for(unsigned  long i = 0; i < j; i++);
}

unsigned char convert_from_bit_pos(unsigned char bitPos)
{
    int val = 0;
    while (bitPos >>= 1)
    {
        ++val;
    }
    return val;
}

void ClearButtons()
{
    TRISB0 = 0;
    TRISB1 = 0;
    TRISB2 = 0;
    TRISB3 = 0;
    TRISE0 = 0;
    TRISE1 = 0;
    TRISE2 = 0;
    PORTB = PORTB & 0xF0;
    PORTE = PORTE & 0xF8;
    TRISB0 = 1;
    TRISB1 = 1;
    TRISB2 = 1;
    TRISB3 = 1;
    TRISE0 = 1;
    TRISE1 = 1;
    TRISE2 = 1;
}

unsigned char convert_to_bit_pos(unsigned char pinNum)
{
    return (1 << pinNum);
}

bool single_key_pressed(char byteVal)
{
    return byteVal && !(byteVal & (byteVal - 1));
}



void convert_to_datetime_from_array(const char input[], DateTime *output)
{
    char *ptr = input;
    DateTime d;
    d.Day = *ptr++;
    d.Month = *ptr++;
    d.Year = *ptr++;
    d.Hour = *ptr++;
    d.Minute = *ptr++;
    d.Second = *ptr;
    
    *output = d;
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