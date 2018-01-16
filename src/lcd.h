/* 
 * File:   LCD.h
 * Author: 463929
 *
 * Created on 21 November 2017, 12:17
 */

#ifndef LCD_H
#define	LCD_H

#include "Commonheader.h"

#define RS RA5
#define RW RA4
#define E  RA3
#define PSB RA2
#define CL_HOME 0b00000001
#define LINE_1 0x03
#define LINE_2 0x90
#define LINE_3 0x88
#define LINE_4 0x98
#define LEFT 0b00010111

#define DISPLAY_CURSOR_BLINK_ON 0x0F
#define DISPLAY_CURSOR_ON       0x0E
#define DISPLAY_ON              0x0C
#define BASIC_FUNCTION_SET_8BIT 0x30

#define BLANK_LINE "                "



void LCD_delay (int j);
void cmd(char cmd);
void initLCD();
void data(char data);
void Second_line(char param[]);
void Write_line(const char param[], int lineNo);
void clear_line(int lineNo);
void clear_lines();
void Write_Date(int lineNo);
void Write_Time(int lineNo);
void Write_Date_Time_Settings(DateTime *dat, int lineNo);
void Write_Time_Settings(DateTime *date, int lineNo);
void Write_Date_Settings(DateTime *date, int lineNo);



#endif	/* LCD_H */