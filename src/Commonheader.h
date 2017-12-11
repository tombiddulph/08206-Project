#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdbool.h>

typedef struct 
{
    unsigned char Year;
    unsigned char Month;
    unsigned char Day;
    unsigned char Hour;
    unsigned char Minute;
    unsigned char Second;
} DateTime;


extern DateTime dateTime;
extern bool DateChanged;


void Delay_loop(int j);

#endif

    