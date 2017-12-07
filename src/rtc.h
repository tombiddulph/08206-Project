/* 
 * File:   rtc.h
 * Author: tombi
 *
 * Created on 06 December 2017, 17:01
 */

#ifndef RTC_H
#define	RTC_H

#include <pic.h>

#define RTC_IO   RB4                      //1302I_O           
#define RTC_CLK  RB0                      //1302 clock        
#define RTC_RST  RB5                      //1302 enable bit   

unsigned char time_rx @ 0x30;        //define receive reg.
static volatile bit time_rx7   @ (unsigned)&time_rx*8+7;   //receive reg highest.//defined name time_rx7 for most significant bit (bit 7) for variable time_rx. After symbol @ there are calculation for the that bit address: &time_rx give us the address of variable time_rx, after multiplying with 8 we have the bit address of bit 0 of time_rx, and adding 7 give us the bit address of bit 7 of time_rx. Type casting (unsigned) used for avoiding signed result of multiplying operation.
//static volatile bit temp0     @ (unsigned)&temp*8+0;

extern const char rtc_table[]={0x00,0x58,0x12,0x8,0x3,0x06,0x06,0x00};
//define the read time and date save table.
char rtc_table1[7];
//define the display code for display 0-9
const char rtc_display_table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 

void port_init_rtc();                      //port initilize subroutine.
void ds1302_init();                    //DS1302 initilize subroutine.
void set_time_rtc();                       //set time subroutine.
void get_time_rtc();                       //get time subroutine.
void display_rtc();                        //display subroutine.
void time_write_rtc(unsigned char time_tx);    //write one byte subroutine.
unsigned char  time_read_rtc();          //read one byte subroutine.
void delay_rtc();                          //delay subroutine.






#endif	/* RTC_H */

