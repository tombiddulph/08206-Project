#ifndef RTC_H
#define RTC_H

#include <xc.h>
#include "Commonheader.h"
#define RTC_IO   RB4                     //1302I_O           
#define RTC_CLK  RC4                      //1302 clock        
#define RTC_RST  RB5                      //1302 enable bit   

#define RTC_CONTROL_WRITE   0x8E
#define RTC_LOW_MASK        0x0F
#define RTC_HIGH_MASK       0xF0

//unsigned char time_rx @ 0x30;        //define receive reg.
//
//static volatile bit time_rx7   @ (unsigned)&time_rx*8+7;   //receive reg highest.//defined name time_rx7 for most significant bit (bit 7) for variable time_rx. After symbol @ there are calculation for the that bit address: &time_rx give us the address of variable time_rx, after multiplying with 8 we have the bit address of bit 0 of time_rx, and adding 7 give us the bit address of bit 7 of time_rx. Type casting (unsigned) used for avoiding signed result of multiplying operation.
unsigned char time_rx @ 0x30; 
bit time_rx7 @ (unsigned)&time_rx*8+7;

void Port_init_rtc();                      //port initilize subroutine.
void ds1302_init();                    //DS1302 initilize subroutine.
void Set_time_rtc();                       //set time subroutine.
void Get_time_rtc();                       //get time subroutine.
void Update_Global_DateTime();                        //display subroutine.
void Write_updated_date_time_rtc(DateTime *date);
void Write_updated_date_rtc(DateTime *date);
void Write_updated_time_rtc(DateTime *date);
void Write_dateTime_rtc(DateTime *date);
void write_time_rtc(unsigned char time_tx);    //write one byte subroutine.
unsigned char  read_time_rtc();          //read one byte subroutine.
void delay_rtc();                          //delay subroutine.



//define the time:       sec,  min,  hour,  day,  month,  week,  year, control word.
const char rtc_table[]={0x00,  0x58, 0x12,  0x12,  0x12,    0x06,   0x17,   0x00};//{0x00,  0x58, 0x12,  0x03,   0x04,   0x06, 0x05,0x00};
//define the read time and date save table.
char rtc_table1[7];

char rtc_lcd_display_date_table[9];
char rtc_lcd_display_time_table[9];
//define the display code for display 0-9
const char rtc_7_seg_display_table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 

DateTime dateTime;
bool DateChanged;

#endif