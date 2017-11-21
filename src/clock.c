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
    RTC_Cmd(RTC_CONTROL_REGISTER, 0x00);
    RTC_Cmd(RTC_TRICKLE_CHARGE_WRITE, 0xA9);
    
    
    
    
}
void RTC_Cmd(unsigned char address, unsigned char value){
    RTC_RST = 1;
    Serial_Write(address);
    Serial_Write(value);
    RTC_RST = 0;
}

void Serial_Write(unsigned char value){
    
    unsigned char mask = 1;
    
    for(unsigned char i = 0; i < 8; ++i){
        
        RTC_IO = value & mask ? 1 : 0;
        RTC_CLK = 1;
        RTC_CLK = 0;
        mask <<= 1;
       
    }
    
}