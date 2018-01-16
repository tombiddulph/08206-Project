#ifndef COMMON_H
#define COMMON_H

#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUTTON_MASK 0x0F



#define INCREMENT   0x01
#define DECREMENT   0x02
#define MOVE_RIGHT  0x04
#define MOVE_LEFT   0x08

typedef struct {
    unsigned char Year;
    unsigned char Month;
    unsigned char Day;
    unsigned char Hour;
    unsigned char Minute;
    unsigned char Second;
} DateTime;



typedef struct {
    short tens;
    short units;
} fake_float;

extern char alarmDurationMinutes;
extern char alarmDurationSeconds;
extern bool activeZones[4];

int ButtonCheck(void);
void ButtonInit(void);
void updateVariables(void);
void Delay_loop(unsigned long j);
unsigned char convert_from_bit_pos(unsigned char bitPos);
unsigned char convert_to_bit_pos(unsigned char pinNum);
bool single_key_pressed(char byteVal);
void ClearButtons(void);
unsigned char convert_bcd_to_dec(unsigned char val);
unsigned char convert_dec_to_bcd(unsigned char val);
void convert_to_datetime_from_array(const char input[], DateTime *dateTime);

#endif

