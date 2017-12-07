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
#define HOME 0b00000011
#define LEFT 0b00010111



void LCD_delay (int j);
void cmd(char cmd);
void initialise_LCD();
void data(char data);
void Write_string(char a[]);
void Second_line(char param[]);
void Write_line(char param[], int lineNo);
void Write_Date(int lineNo);

struct DateTime dateTime;

#endif	/* LCD_H */