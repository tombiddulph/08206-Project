/* 
 * File:   rtc.c
 * Author: tombi
 *
 * Created on 06 December 2017, 17:03
 */

#include "rtc.h"

//define the time: sec,min,hour,day,month,week,year,control word.


//---------------------------------------------
//DS1302 initilize.
void ds1302_init()
  {
   RTC_CLK=0;                            //pull low clock
   RTC_RST =0;                            //reset DS1302
   RTC_RST=1;                             //enable DS1302
   time_write_rtc(0x8e);                //send control command
   time_write_rtc(0);                   //enable write DS1302
   RTC_RST=0;                             //reset
  }

//---------------------------------------------
//set time.
void set_time_rtc()
  {
   int i;                             //define the loop counter.
   RTC_RST=1;                             //enable DS1302
   time_write_rtc(0xbe);                //
   for(i=0;i<8;i++)                   //continue to write 8 bytes.
     {
       time_write_rtc(rtc_table[i]);        //write one byte
     }
   RTC_RST=0;                             //reset
   }

//---------------------------------------------
//get time.
void get_time_rtc()
 {
   int i;                             //set loop counter.
   RTC_RST=1;                             //enable DS1302
   time_write_rtc(0xbf);                //
   for(i=0;i<7;i++)                   //continue to read 7 bytes.
     {
        rtc_table1[i]=time_read_rtc();      //
     }
    RTC_RST=0;                            //reset DS1302
 }

//--------------------------------------------
//write one byte
void time_write_rtc(unsigned char time_tx)
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
unsigned char time_read_rtc()
 {
   int j;                            //set the loop counter.  
   TRISB4=1;                         //continue to write 8bit 
   for(j=0;j<8;j++)                  
      {
        RTC_CLK=0;                       //pull low clk                   
        time_rx = time_rx>>1;           //judge the send bit is 0 or 1.  
        time_rx7 = RTC_IO;                //put the received bit into the reg's highest.
       RTC_CLK=1;                       //pull high clk                 
      }                                                              
    TRISB4=0;                        //finished 1 byte,pull low clk  
    RTC_CLK=0;                          
    return(time_rx);                 
  }

//--------------------------------------------
//pin define func
void port_init_rtc()
  {
    TRISA=0x00;                     //a port all output
    TRISD=0X00;                     //d port all output
    ADCON1=0X06;                    //a port all i/o
    TRISB=0X02;                     //rb1 input, others output
  //  OPTION=0X00;                    //open b port internal pull high.
    PORTA=0XFF;               
    PORTD=0XFF;                     //clear all display
   }

//-------------------------------------------
//display
void display_rtc()
   {
     int i;                         //define table variable.
     if(RB1==0)                     //judge rb1.
       {
          rtc_table1[0]=rtc_table1[3];     
          rtc_table1[1]=rtc_table1[4];
          rtc_table1[2]=rtc_table1[6];
       }
     i=rtc_table1[0]&0x0f;             //sec's low.
     PORTD=rtc_display_table[i];              //send to port d.
     PORTA=0x1f;                   //light on sec's low.
     delay_rtc();                      //delay some times.
     i=rtc_table1[0]&0xf0;             //sec's high
     i=i>>4;                       //rotate right for 4 bits.
     PORTD=rtc_display_table[i];              //send to port d.    
     PORTA=0x2f;                   //light on sec's high.
     delay_rtc();                      //delay some times.  
     
     i=rtc_table1[1]&0x0f;             //min's low.                 
     PORTD=rtc_display_table[i]&0x7f;         //send to port d.            
     PORTA=0x37;                   //light on min's low.        
     delay_rtc();                      //delay some times.          
     i=rtc_table1[1]&0xf0;             //min's high                 
     i=i>>4;                       //rotate right for 4 bits.   
     PORTD=rtc_display_table[i];              //send to port d.            
     PORTA=0x3b;                   //light on min's high.       
     delay_rtc();                      //delay some times.          

     i=rtc_table1[2]&0x0f;             //hour's low.                 
     PORTD=rtc_display_table[i]&0x7f;         //send to port d.            
     PORTA=0x3d;                   //light on hour's low.        
     delay_rtc();                      //delay some times.          
     i=rtc_table1[2]&0xf0;             //hour's high                 
     i=i>>4;                       //rotate right for 4 bits.   
     PORTD=rtc_display_table[i];              //send to port d.            
     PORTA=0x3e;                   //light on hour's high.       
     delay_rtc();                      //delay some times.          
   }

//------------------------------------------------------------------
//delay
void  delay_rtc()              //
    {
     int i;                 //define variable
     for(i=0x64;i--;);     //delay
    }