//experiment purpose: familiar how to use clock chip DS1302       
//first set time and date:second(08),minute(58),hour(05),day(13),month(01),year(55)   
//six LED display time and date,default display time,differentiate hour and min,min and second with decimal dot 
//when press RB1 not relax,display switch to date.     
//hardware request: SW S9,S5,S6 all ON,S1 the seventh bit ON,the other bits OFF,the other SWS OFF.


#include <xc.h>
#include "temp_sensor.h"
#include "lcd.h"
#include "clock.h"
#include "Commonheader.h"
#include "date_setting.h"
#include "zones.h"
#include "buzzer.h"
#define BUTTON_MASK 0x0F



#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
//#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
//#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
//#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#define SETTINGS_MASK 0x07
extern char temperature[8];
char previous_temp[8];
int oldMatch = 10;

//void (*settings_ptr[2]) = {Date_time_setting_loop, ZoneLoop };

typedef void (*settings_ptr)(void);
settings_ptr settings[2];

enum STATE {HOME, SETTINGS};

enum STATE currentState;
void mainInit()
{
    settings[0] = Date_time_setting_loop;
    settings[1] = ZoneLoop;
     //initTempSensor();                       //call system initialize function  
     initLCD();
     ButtonInit();   
     ZoneInit();
     buzzerInit();
     Port_init_rtc();                     //port initilize.
     ds1302_init();                   //DS1302 initilize.
}

void main()
  {
    currentState = HOME;
   
   
    mainInit();
        
   
    Delay_loop(5000);
    Set_time_rtc(); 
    //initTempSensor();                       //call system initialize function  
 
   
    Get_time_rtc();   
    //get_temp();  
    Get_time_rtc();
    Update_Global_DateTime();
     
    
   
   while(1)                                                                                                                                                                                        
     { 
       
   
       char choice;
       // get_temp();  
        Get_time_rtc();
        Update_Global_DateTime();
       
       switch(currentState)
       {
           case HOME:
           {
                //Write_line(temperature , 0);
               Write_line("test" , 0);
                Write_Date(1);
                Write_Time(2);
                
                  choice  = (PORTB & BUTTON_MASK);
                    
                   if(choice && !(choice & (choice - 1))) // check to see if 1 and only 1 bit is set
                   {
                       if(convert_from_bit_pos(choice) == 3)
                       {
                           currentState = SETTINGS;
                           break;
                       }
                   }
                
                break;
           }
           case SETTINGS:
           {
               Write_line("Date/Time", 0);
               Write_line("Zones", 1);
               Write_line("Temp", 2);
               
               
                choice  = (PORTB & SETTINGS_MASK);
               
                if(choice && !(choice & (choice - 1))) // check to see if 1 and only 1 bit is set
                {
                    
                    switch(convert_from_bit_pos(choice))
                    {
                        case (0):
                            Date_time_setting_loop();
                            break;
                        case (1):
                            ZoneLoop();
                            break;
                            
                    }
                    //(settings[])();         
                    currentState = HOME;
                }
               
               break;
           }
               
       }
       
   }
}  
