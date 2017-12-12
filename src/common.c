#include "Commonheader.h"

void Delay_loop(int j )
{
    for (unsigned i=0; i<j; i++);
}
unsigned convert_to_bit_pos(unsigned pinNum)
{
    return (1 << pinNum);
}
unsigned convert_from_bit_post(unsigned bitPos)
{
    unsigned val;
    while(bitPos >>= 1)
    {
        ++val;
    }
    return val;
}