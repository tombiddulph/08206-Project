//experiment purpose: familiar how to use clock chip DS1302       
//first set time and date:second(08),minute(58),hour(05),day(13),month(01),year(55)   
//six LED display time and date,default display time,differentiate hour and min,min and second with decimal dot 
//when press RB1 not relax,display switch to date.     
//hardware request: SW S9,S5,S6 all ON,S1 the seventh bit ON,the other bits OFF,the other SWS OFF.




#include <pic.h>                        //include MCU head file     
#include "Commonheader.h"
#include "clock.h"
#include "lcd.h"
//__PROG_CONFIG(0x1832);       
//__CONFIG( _DEBUG_OFF&_CP_ALL&_WRT_HALF&_CPD_ON&_LVP_OFF&_BODEN_OFF&_PWRTE_ON&_WDT_OFF&_HS_OSC);
__CONFIG( FOSC_HS & WDTE_OFF & PWRTE_ON & BOREN_OFF & LVP_OFF );


struct DateTime dateTime;
//----------------------------------------------
//main routine.
void main()
  {
    
   // time_rx7 @ (unsigned)&time_rx*8+7;
     Port_init_rtc();                     //port initilize.
     ds1302_init();                   //DS1302 initilize.
     Set_time_rtc();                      //set time
     
     LCD_delay(10000);
     initialise_LCD();
     cmd(CL_HOME);
     Get_time_rtc();    
     while(1)
        {
          
          
           Get_time_rtc();
           Display_7_seg_rtc();
          //Display_7_seg_rtc();      
           Write_Date(1);
//          Write_line(rtc_lcd_display_date_table , 1); 
//          Write_line(rtc_lcd_display_time_table,2);
          
          
        }
  }

//---------------------------------------------
