/*
 * File:   main.c
 * Author: 462767
 *
 * Created on 14 November 2017, 11:58
 */

// ACW for 08026

#include <xc.h>
#include <pic.h>
#include <string.h>
#include "temp_sensor.h"
#include "lcd.h"
#include "buzzer.h"
#include "Commonheader.h"

#define BUTTON_MASK 0x0F
#define ZONE_MASK 0x0F
#define ZONE_0 0x00
#define ZONE_1 0x01
#define ZONE_2 0x04
#define ZONE_3 0x08


__CONFIG( FOSC_HS & WDTE_OFF & PWRTE_ON & BOREN_OFF & LVP_OFF );

extern char temperature[8];
char previous_temp[8];
int oldMatch = 10;
int prevButt = -1;

bool activeZones[] = {false, false, false, false};

unsigned lastPressed = 9;

void SetZone(int zone)
{
    activeZones[zone] = !activeZones[zone];  
}

void ZoneInit()
{
    TRISC = 0x0F;
    PORTC = 0x00;
}

void ZoneCheck()
{
    int finalMask = 0;
    
    for(int i =0; i < 4; ++i)
    {
      int mask = 0x01;
      
      if(activeZones[i])
      {
           finalMask |= mask;
      }
      mask = mask << 1;
    }
    
//    int btn = (PORTC & ZONE_MASK);
//    char buf1[15];
//    sprintf(buf1, "button val %d ", btn);
//    Write_line(buf1, 1);
    
    if((PORTC & (ZONE_MASK & finalMask)) > 0)
    {
        soundBuzzer(); //pass current time
    }
    if(PORTC & ZONE_MASK)
    {
        TRISC = 0x00;
        PORTC = 0x00;
        TRISC = 0x0F;
    }
  
  
}

int ButtonCheck()
{
    int result = (PORTB & BUTTON_MASK);
        
  
        if(result && !(result & (result - 1))) // check to see if 1 and only 1 bit is set
        {
            lastPressed = result;
            int portN = result == 8 ? 3 : result == 4 ? 2 : result == 2 ? 1 : 0; //convert hex value to port number
            
            return portN;
        }
    return -1;
}

void ButtonInit()
{
    TRISB = 0x0F;
    PORTB = 0x00;
    
}





void main()
{
    
//    for(int j=0;j<10;j++)temperature[j] = 0;
//    
//    initTempSensor();                       //call system initialize function  
//    initLCD();
//    //cmd(CL_HOME);
//    get_temp();
//    Write_line(temperature , 1);
//    Write_line("line 2" , 2);
//    Write_line("line 3" , 3);
//    Write_line("1111111111111112" , 4);
//   while(1)                                                                                                                                                                                        
//     { 
//       get_temp();           //call temperature convert function 
//       LCD_delay(1000);
//       
//       int match = memcmp(temperature, &previous_temp, 4);
//       memcpy(&previous_temp, temperature, 4);
//       
//       
//       if(match != oldMatch)
//       {    
//           clear_line(4);
//            if(match == 0)
//            {
//                Write_line("ZERO" , 4);
//            }
//            else if(match > 0)
//            {
//                Write_line("GREATER" , 4);
//            }
//            else if( match < 0)
//            {
//                Write_line("LESS" , 4);
//            }
//            else
//            {
//                 Write_line("NOOO" , 4);
//            }
//
//
//            if (match != 0)
//            {
//                clear_line(1);
//                clear_line(2);
//                Write_line(temperature , 1);
//                Write_line("Not match", 2);
//            }
//            else
//            {
//                clear_line(2);
//                Write_line("match", 2);
//            }
//       }
//       oldMatch = match;
//       LCD_delay(1000);  
//       
//     } 
    
     initTempSensor();                       //call system initialize function  
     initLCD();
     ButtonInit();
     buzzerInit();
     ZoneInit();
    
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
