//experiment purpose: familiar how to use clock chip DS1302       
//first set time and date:second(08),minute(58),hour(05),day(13),month(01),year(55)   
//six LED display time and date,default display time,differentiate hour and min,min and second with decimal dot 
//when press RB1 not relax,display switch to date.     
//hardware request: SW S9,S5,S6 all ON,S1 the seventh bit ON,the other bits OFF,the other SWS OFF.


#include <xc.h>
#include <pic.h>
#include <string.h>
#include "temp_sensor.h"
#include "lcd.h"
//__PROG_CONFIG(0x1832);       
//__CONFIG( _DEBUG_OFF&_CP_ALL&_WRT_HALF&_CPD_ON&_LVP_OFF&_BODEN_OFF&_PWRTE_ON&_WDT_OFF&_HS_OSC);
__CONFIG( FOSC_HS & WDTE_OFF & PWRTE_ON & BOREN_OFF & LVP_OFF );

extern char temperature[8];
char previous_temp[8];
int oldMatch = 10;
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
    
    
    
    
}  
