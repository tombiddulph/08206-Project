/*
 * File:   main.c
 * Author: 462767
 *
 * Created on 14 November 2017, 11:58
 */

// ACW for 08026

#include <xc.h>
#include <pic.h>
#include "temp_sensor.h"
#include "lcd.h"
__CONFIG( FOSC_HS & WDTE_OFF & PWRTE_ON & BOREN_OFF & LVP_OFF );

extern char temperature[10];

void main()
{
    
    for(int j=0;j<10;j++)temperature[j] = 0;
    
   //init();                       //call system initialize function  
    //initialise_LCD();
    //cmd(CL_HOME);
    //Write_line("hello" , 1);
   while(1)                                                                                                                                                                                        
     { 
       init();
       get_temp();           //call temperature convert function   
       LCD_delay(10000);
       initialise_LCD();
       cmd(CL_HOME);
       Write_line(temperature , 1);
       LCD_delay(70000);  
       
     }                                                                                                                                                                                             
}  
