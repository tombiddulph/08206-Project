#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdbool.h>
#include <xc.h>
#include <string.h>

#define BUTTON_MASK 0x0F

typedef struct 
{
    unsigned char Year;
    unsigned char Month;
    unsigned char Day;
    unsigned char Hour;
    unsigned char Minute;
    unsigned char Second;
} DateTime;

int prevButt = -1;
unsigned lastPressed = 9;
extern DateTime dateTime;
extern bool DateChanged;


void Delay_loop(int j);
int ButtonCheck();
void ButtonInit();

#endif

