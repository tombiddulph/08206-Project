#ifndef COMMON_H
#define COMMON_H

#include <string.h>
#include <stdio.h>

struct DateTime
{
    unsigned char Year;
    unsigned char Month;
    unsigned char Day;
    unsigned char Hour;
    unsigned char Minute;
    unsigned char Second;
};


extern struct DateTime dateTime;

#endif

    