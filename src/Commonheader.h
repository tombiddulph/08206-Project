#ifndef COMMON_H
#define COMMON_H

#include <string.h>
#include <stdio.h>

struct DateTime
{
    char Year[2];
    char Month[2];
    char Day[2];
    char Hour[2];
    char Minute[2];
    char Second[2];
};


extern struct DateTime dateTime;

#endif

    