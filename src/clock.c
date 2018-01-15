/*
 * File:   clock.c
 * Author: 462767
 *
 * Created on 14 November 2017, 15:53
 */

#include "Commonheader.h"
#include "clock.h"


 DateTime *dateTime;
//DS1302 initilize.

void ds1302_init()
{
    RTC_CLK = 0; //pull low clock
    //RTC_RST =0;                            //reset DS1302
    RTC_RST = 1; //enable DS1302
    write_time_rtc(RTC_CONTROL_WRITE); //send control command
    write_time_rtc(0);
    write_time_rtc(0x90);
    write_time_rtc(0xa9);
    //enable write DS1302
    RTC_RST = 0; //reset
}

//---------------------------------------------
//set time.
char i;
void set_time_rtc()
{
     //define the loop counter.
    RTC_RST = 1; //enable DS1302
    write_time_rtc(0xbe); //
    for(i = 0; i < 8; i++) //continue to write 8 bytes.
    {
        write_time_rtc(rtc_table[i]); //write one byte
    }
    RTC_RST = 0; //reset
}

//---------------------------------------------
//get time.

void get_time_rtc()
{
    
    RTC_RST = 1; //enable DS1302
    write_time_rtc(0xbf); //
    for(i = 0; i < 7; i++) //continue to read 7 bytes.
    {
        rtc_table1[i] = read_time_rtc(); //
    }
    RTC_RST = 0; //reset DS1302
}

//--------------------------------------------
//write one byte

void write_time_rtc(unsigned char time_tx)
{
   
    for(i = 0; i < 8; i++) //continue to write 8bit
    {
        RTC_IO = 0; //
        RTC_CLK = 0; //pull low clk
        if(time_tx & 0x01) //judge the send bit is 0 or 1.
        {
            RTC_IO = 1; //is 1
        }
        time_tx = time_tx >> 1; //rotate right 1 bit.
        RTC_CLK = 1; //pull high clk
    }
    RTC_CLK = 0; //finished 1 byte,pull low clk
}

//---------------------------------------------
//read one byte.

unsigned char read_time_rtc()
{
   //set the loop counter.  
    TRISB4 = 1; //continue to write 8bit 
    for(i = 0; i < 8; i++)
    {
        RTC_CLK = 0; //pull low clk                   
        time_rx = time_rx >> 1; //judge the send bit is 0 or 1.  
        time_rx7 = RTC_IO; //put the received bit into the reg's highest.
        RTC_CLK = 1; //pull high clk                 
    }
    TRISB4 = 0; //finished 1 byte,pull low clk  
    RTC_CLK = 0;
    return (time_rx);
}

//--------------------------------------------
//pin define func

void port_init_rtc()
{
    //d port all output
    //ADCON1=0X06;                    //a port all i/o


    RC4 = 0;
    RB4 = 0;
    RB5 = 0;
    TRISC4 = 0;
    TRISB4 = 0;
    TRISB4 = 0;


}

//-------------------------------------------
//display

void Write_updated_date_time_rtc(DateTime *date)
{
    RTC_RST = 1; //enable DS1302
    write_time_rtc(0xbe);
    write_time_rtc(decimal_to_bcd(date->Second));
    write_time_rtc(decimal_to_bcd(date->Minute));
    write_time_rtc(decimal_to_bcd(date->Hour));
    write_time_rtc(decimal_to_bcd(date->Day));
    write_time_rtc(decimal_to_bcd(date->Month));
    write_time_rtc(decimal_to_bcd(0x06));
    write_time_rtc(decimal_to_bcd(date->Year));
    write_time_rtc(00);
    RTC_RST = 0;
}

void Write_updated_date_rtc(DateTime *date)
{
    dateTime = get_current_date_time();
    RTC_RST = 1; //enable DS1302
    write_time_rtc(0xbe);
    write_time_rtc(decimal_to_bcd(dateTime->Second));
    write_time_rtc(decimal_to_bcd(dateTime->Minute));
    write_time_rtc(decimal_to_bcd(dateTime->Hour));
    write_time_rtc(decimal_to_bcd(date->Day));
    write_time_rtc(decimal_to_bcd(date->Month));
    write_time_rtc(decimal_to_bcd(0x06));
    write_time_rtc(decimal_to_bcd(date->Year));
    write_time_rtc(00);
    RTC_RST = 0;
}

void Write_updated_time_rtc(DateTime *date)
{
    dateTime = get_current_date_time();
    RTC_RST = 1; //enable DS1302
    write_time_rtc(0xbe);
    write_time_rtc(decimal_to_bcd(date->Second));
    write_time_rtc(decimal_to_bcd(date->Minute));
    write_time_rtc(decimal_to_bcd(date->Hour));
    write_time_rtc(decimal_to_bcd(dateTime->Day));
    write_time_rtc(decimal_to_bcd(dateTime->Month));
    write_time_rtc(decimal_to_bcd(0x06));
    write_time_rtc(decimal_to_bcd(dateTime->Year));
    write_time_rtc(00);
    RTC_RST = 0;
}

 DateTime *get_current_date_time()
{
     get_time_rtc();
    
    char *date = rtc_table1 + 3;
    char *time = rtc_table1;

    DateTime dateTime;

    dateTime.Second = bcd_to_decimal(0x7F & *time++);
    dateTime.Minute = bcd_to_decimal(0x7F & *time++);
    dateTime.Hour = bcd_to_decimal(0x3F & *time);
    dateTime.Day = bcd_to_decimal(0x3F & *date++);
    dateTime.Month = bcd_to_decimal(0x1F & *date++);
    *date++; //increment again to skip over the week
    dateTime.Year = bcd_to_decimal(0xFF & *date++);


    return &dateTime;

}

//------------------------------------------------------------------
