/*
 * File:   main.c
 * Author: 462767
 *
 * Created on 14 November 2017, 11:58
 */

// ACW for 08026

#include <xc.h>
#include <string.h>
#include "temp_sensor.h"
#include "lcd.h"
#include "buzzer.h"
#include "Commonheader.h"
#include "zones.h"





__CONFIG( FOSC_HS & WDTE_OFF & PWRTE_ON & BOREN_OFF & LVP_OFF );

extern char temperature[8];
char previous_temp[8];
int oldMatch = 10;


void mainInit()
{
     initTempSensor();                       //call system initialize function  
     initLCD();
     ButtonInit();   
     ZoneInit();
     buzzerInit();
}

void ZoneLoop()
{
    while(1)
    {
        
        int butt = ButtonCheck();
        
        if(butt != -1)
        {
//            char buf[12];
//            sprintf(buf, "RB%d pressed", butt);
//            Write_line(buf,3);


            if(prevButt != butt)
            {
               SetZone(butt);
            }
             


            char duf[10];
            sprintf(duf, "Zone 0: %d", activeZones[0]);
            Write_line(duf,0);
            
            sprintf(duf, "Zone 1: %d", activeZones[1]);
            Write_line(duf,1);
            
            sprintf(duf, "Zone 2: %d", activeZones[2]);
            Write_line(duf,2);
            
            sprintf(duf, "Zone 3: %d", activeZones[3]);
            Write_line(duf,3);
            
        }
        
        ZoneCheck();
        
        
        
        prevButt = butt;
    }
}

void Temploop()
{
  while(1)                                                                                                                                                                                        
  { 
    get_temp();           //call temperature convert function 
    LCD_delay(1000);

    int match = memcmp(temperature, &previous_temp, 4);
    memcpy(&previous_temp, temperature, 4);


    if(match != oldMatch)
    {    
         if(match == 0)
         {
             Write_line("ZERO" , 3);
         }
         else if(match > 0)
         {
             Write_line("GREATER" , 3);
         }
         else if( match < 0)
         {
             Write_line("LESS" , 3);
         }
         else
         {
              Write_line("NOOO" , 3);
         }


         if (match != 0)
         {
             Write_line(temperature , 0);
             Write_line("Not match", 1);
         }
         else
         {
             Write_line("match", 1);
         }
    }
    oldMatch = match;
    LCD_delay(1000);  
    
     int butt = ButtonCheck();
     
     if(butt == 1)
     {
         ZoneLoop();
     }
  }
}


void main()
{   
    mainInit();
    //ZoneLoop();
    Temploop();
}  
