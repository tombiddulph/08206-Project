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
__CONFIG( FOSC_HS & WDTE_OFF & PWRTE_ON & BOREN_OFF & LVP_OFF );

extern char temperature[8];
char previous_temp[8];
int oldMatch = 10;
void main()
{
    
    for(int j=0;j<10;j++)temperature[j] = 0;
    
    init();                       //call system initialize function  
    initialise_LCD();
    //cmd(CL_HOME);
    get_temp();
    Write_line(temperature , 1);
    Write_line("line 2" , 2);
    Write_line("line 3" , 3);
    Write_line("1111111111111112" , 4);
   while(1)                                                                                                                                                                                        
     { 
       get_temp();           //call temperature convert function 
       LCD_delay(1000);
       
       int match = memcmp(temperature, &previous_temp, 4);
       memcpy(&previous_temp, temperature, 4);
       
       
       if(match != oldMatch)
       {    
           clear_line(4);
            if(match == 0)
            {
                Write_line("ZERO" , 4);
            }
            else if(match > 0)
            {
                Write_line("GREATER" , 4);
            }
            else if( match < 0)
            {
                Write_line("LESS" , 4);
            }
            else
            {
                 Write_line("NOOO" , 4);
            }


            if (match != 0)
            {
                clear_line(1);
                clear_line(2);
                Write_line(temperature , 1);
                Write_line("Not match", 2);
            }
            else
            {
                clear_line(2);
                Write_line("match", 2);
            }
       }
       oldMatch = match;
       LCD_delay(1000);  
       
     }                                                                                                                                                                                             
}  
