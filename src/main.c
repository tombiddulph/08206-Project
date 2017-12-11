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
#include "clock.h"

#define BUTTON_MASK 0x0F

//__PROG_CONFIG(0x1832);       
//__CONFIG( _DEBUG_OFF&_CP_ALL&_WRT_HALF&_CPD_ON&_LVP_OFF&_BODEN_OFF&_PWRTE_ON&_WDT_OFF&_HS_OSC);
__CONFIG( FOSC_HS & WDTE_OFF & PWRTE_ON & BOREN_OFF & LVP_OFF );

extern char temperature[8];
char previous_temp[8];
int oldMatch = 10;

void MainLoop();

unsigned lastPressed = 9;




void main()
  {
    
    
    Port_init_rtc();                     //port initilize.
    ds1302_init();                   //DS1302 initilize.
        
   
    Delay_loop(5000);
    Set_time_rtc(); 
    //initTempSensor();                       //call system initialize function  
    initLCD();
    cmd(CL_HOME);
    Get_time_rtc();   
    //cmd(CL_HOME);
    
   
   while(1)                                                                                                                                                                                        
     { 
   
        Get_time_rtc();
        Update_dateTime();
       // Write_line(temperature , 1);
        
        if(DateChanged)
        {
            Write_Date(1);
        }
        
        Write_Time(2);
       
        
        
        
        int result = (PORTB & BUTTON_MASK);
        
  
        if(result && !(result & (result - 1))) // check to see if 1 and only 1 bit is set
        {
            lastPressed = result;
            int portN = result == 8 ? 3 : result == 4 ? 2 : result == 2 ? 1 : 0; //convert hex value to port number
           
            char buf[12];
            sprintf(buf, "RB%d pressed", portN);
            Write_line(buf,0);
        }
        else
        {
             Write_line("nothing pressed",0);
        }
        
        Delay_loop(5000);
     } 
    
   
  
    
    
    
    
}  
