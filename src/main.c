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
#include "alarm_duration.h"


#define BUTTON_MASK 0x0F
#define SETTINGS_MASK 0x0F

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)



extern char temperature[8];
char previous_temp[8];
int oldMatch = 10;

typedef void (*settings_ptr)(void);
typedef void (*page_ptr)(void);


void Home_page();
void Settings_page();
void Temp_sensor_page();
void Alarm_duration_page();

settings_ptr settings[4] = {Date_time_setting_loop, ZoneLoop, Temp_sensor_page, alarm_duration_settings_page};
page_ptr pages[2] = {Home_page, Settings_page};

enum STATE {HOME, SETTINGS};

enum STATE currentState;

int current_alarm_duration;

//eeprom_write(0x01, 0xF0); //write 0xF0 to memory location 0x01
    //char result = eeprom_read(0x01); //read from memory location 0x01
void mainInit()
{

    current_alarm_duration = 15;
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
        

    Set_time_rtc(); 
    //initTempSensor();                       //call system initialize function  
 
   
    Get_time_rtc();   
    //get_temp();  
    Get_time_rtc();
    Update_Global_DateTime();  
   
   while(1)                                                                                                                                                                                        
     { 
       
       // get_temp();  
       Get_time_rtc();
       Update_Global_DateTime();
       pages[currentState]();
       
       
        
       
    }
}  


void Home_page()
{
    while(1)
    {
      Write_line("test" , 0);
      Write_Date(1);
      Write_Time(2);
      Get_time_rtc();
      Update_Global_DateTime();
      char choice  = (PORTB & BUTTON_MASK);
                    
        if(single_key_pressed(choice)) // check to see if 1 and only 1 bit is set
        {
            if(convert_from_bit_pos(choice) == 0)
            {
                currentState = SETTINGS;
                break;
            }
        }
    }
}

void Settings_page()
{    
        
        while(1)
        {
           
            Write_line("Date/Time", 0);
            Write_line("Zones", 1);
            Write_line("Temp", 2);
            Write_line("Alarm duration", 3);

            char  choice  = (PORTB & SETTINGS_MASK);

            if(single_key_pressed(choice)) // check to see if 1 and only 1 bit is set
            {
             
                
                settings[convert_from_bit_pos(choice)]();
                clear_lines();
                currentState = HOME;  
                break;
               
            }    
            break;
        }
   
}

void Temp_sensor_page()
{
    clear_lines();
    Write_line("TEST", 0);
    Delay_loop(90000);
    
}


   
   

