/*
 * File:   clock.c
 * Author: 462767
 *
 * Created on 14 November 2017, 15:53
 */

#include "Commonheader.h"
#include "clock.h"
#include <xc.h>
#include <string.h>
#include <stdio.h>



//DS1302 initilize.
void ds1302_init()
  {
   RTC_CLK=0;                            //pull low clock
   RTC_RST =0;                            //reset DS1302
   RTC_RST=1;                             //enable DS1302
   write_time_rtc(RTC_CONTROL_WRITE);                //send control command
   write_time_rtc(0);                   //enable write DS1302
   RTC_RST=0;                             //reset
  }

//---------------------------------------------
//set time.
void Set_time_rtc()
  {
   int i;                             //define the loop counter.
   RTC_RST=1;                             //enable DS1302
   write_time_rtc(0xbe);                //
   for(i=0;i<8;i++)                   //continue to write 8 bytes.
     {
       write_time_rtc(rtc_table[i]);        //write one byte
     }
   RTC_RST=0;                             //reset
   }

//---------------------------------------------
//get time.
void Get_time_rtc()
 {
   int i;                             //set loop counter.
   RTC_RST=1;                             //enable DS1302
   write_time_rtc(0xbf);                //
   for(i=0;i<7;i++)                   //continue to read 7 bytes.
     {
        rtc_table1[i] = read_time_rtc();      //
     }
    RTC_RST=0;                            //reset DS1302
 }

//--------------------------------------------
//write one byte
void write_time_rtc(unsigned char time_tx)
 {
    int j;                            //set the loop counter.
    for(j=0;j<8;j++)                  //continue to write 8bit
      {
        RTC_IO=0;                        //
        RTC_CLK=0;                       //pull low clk
        if(time_tx&0x01)              //judge the send bit is 0 or 1.
          {
            RTC_IO=1;                    //is 1
          }
        time_tx=time_tx>>1;           //rotate right 1 bit.
        RTC_CLK=1;                       //pull high clk
       }
      RTC_CLK=0;                         //finished 1 byte,pull low clk
  }

//---------------------------------------------
//read one byte.
unsigned char read_time_rtc()
 {
   int j;                            //set the loop counter.  
   TRISB4=1;                         //continue to write 8bit 
   for(j=0;j<8;j++)                  
      {
        RTC_CLK=0;                       //pull low clk                   
        time_rx=time_rx>>1;           //judge the send bit is 0 or 1.  
        time_rx7=RTC_IO;                //put the received bit into the reg's highest.
       RTC_CLK=1;                       //pull high clk                 
      }                                                              
    TRISB4=0;                        //finished 1 byte,pull low clk  
    RTC_CLK=0;                          
    return(time_rx);                 
  }

//--------------------------------------------
//pin define func
void Port_init_rtc()
  {
    TRISA=0x00;                     //a port all output
    TRISD=0X00;                     //d port all output
    ADCON1=0X06;                    //a port all i/o
    TRISB=0X02;                     //rb1 input, others output
    PORTA=0XFF;               
    PORTD=0XFF;                     //clear all display
   }


//-------------------------------------------
//display
void Display_7_seg_rtc()
   {
    
     char *date = rtc_table1 + 3;
     char *time = rtc_table1;
     
     
     dateTime.Second = bcd_to_decimal(0x7F & *time++);
     dateTime.Minute = bcd_to_decimal(0x7F & *time++);
     dateTime.Hour   = bcd_to_decimal(0x3F & *time);
     dateTime.Day   = bcd_to_decimal(0x3F & *date++);
     dateTime.Month = bcd_to_decimal(0x1F & *date++);
     *date++; //increment again to skip over the week
     dateTime.Year  = bcd_to_decimal(0xFF & *date++);
   }

//------------------------------------------------------------------

unsigned char bcd_to_decimal(unsigned char val)
{
  return ((val & 0x0F) + (((val & 0xF0) >> 4) * 10));
}
unsigned char decimal_to_bcd(unsigned char val)
{
    return (((val / 10) << 4) & 0xF0) | ((val % 10) & 0x0F);
}