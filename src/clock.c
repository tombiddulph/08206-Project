/*
 * File:   clock.c
 * Author: 462767
 *
 * Created on 14 November 2017, 15:53
 */

#include "clock.h"
#include <xc.h>


void RTC_Init(void){
    TRISB = 0x00;
    PORTB = 0x00;
    
    RTC_RST = 0;
    RTC_CLK = 0;
    RTC_Cmd(RTC_COTNROL_WRITE, 0x00);
    RTC_Cmd(RTC_TRICKLE_WRITE, 0xA9);
    
    
    
    
}
void RTC_Cmd(unsigned cmd, unsigned char value) {
    RTC_RST = 1;
    RTC_Serial_Write(cmd);
    RTC_Serial_Write(value);
    RTC_RST = 0;
}



unsigned char RTC_Read(unsigned char address){
    unsigned char val = 0;
    RTC_RST = 1;
    RTC_Serial_Write(address);
    result = RTC_Serial_Read();
    RTC_RST = 0;
    return val;
}
void RTC_Serial_Write(unsigned char value) {
    
    unsigned char mask = 1;
    
    for(unsigned char i = 0; i < 8; i++){   
        RTC_IO = value & mask ? 1 : 0;
        RTC_CLK = 1;
        RTC_CLK = 0;
        mask <<= 1;  
    }  
}

unsigned char RTC_Serial_Read(void){
    unsigned i = 0;
    unsigned mask = 1;
    unsigned value = 0;
    
    for(i = 0; i < 8; i++){
        RTC_CLK = 1;
        RTC_CLK = 0;
        if(PORTB & mask){
            value |= mask
        }
        mask << 1;
    }
    
    return value;
}