#ifndef COMMON_H
#define COMMON_H

#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define Pin(n) (1 << n) //convert from pin number to bit position
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

int ButtonCheck();
void ButtonInit();
void Delay_loop(int j);
int convert_from_bit_pos(int bitPos);
int convert_to_bit_pos(int pinNum);
unsigned char bcd_to_decimal(unsigned char val);
unsigned char decimal_to_bcd(unsigned char val);
DateTime *convertDateFromArray(char input[]);

#endif

    