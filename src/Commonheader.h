#ifndef COMMON_H
#define COMMON_H

#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define Pin(n) (1 << n) //convert from pin number to bit position
#define BUTTON_MASK 0x0F


#define INCREMENT   0x01
#define DECREMENT   0x02
#define MOVE_RIGHT  0x04
#define MOVE_LEFT   0x08

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
extern int current_alarm_duration;
extern bool activeZones[4];

int ButtonCheck();
void ButtonInit();
void updateVariables();
void Delay_loop(int j);
int convert_from_bit_pos(int bitPos);
int convert_to_bit_pos(int pinNum);
bool single_key_pressed(char byteVal);
unsigned char convert_bcd_to_dec(unsigned char val);
unsigned char convert_dec_to_bcd(unsigned char val);
DateTime *convertDateFromArray(char input[]);

#endif

    