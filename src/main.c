


#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include "temp_sensor.h"
#include "lcd.h"
#include "clock.h"
#include "Commonheader.h"
#include "date_setting.h"
#include "zones.h"
#include "buzzer.h"
#include "alarm_duration.h"
#include "temp_thresh.h"


#define BUTTON_MASK         0x0F
#define SETTINGS_MASK       0x0F
#define DATA_START_ADDRESS  0x01
#define DATE_DAY            0x00
#define DATE_MONTH          0x01
#define DATE_YEAR           0x02
#define DATE_HOURS          0x03
#define DATE_MINUTES        0x04
#define DATE_SECONDS        0x05
#define ZONES               0x06
#define ALARM_DURATION      0x07
#define THRESHOLD_TENS      0x08
#define THRESHOLD_UNITS     0x09

#define SAVE_SETTINGS       0x01
#define LOAD_SETTINGS       0x02



__EEPROM_DATA(0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88);

extern char temperature[8];
char previous_temp[8];
int oldMatch = 10;
char threshold[7];
int threshold_temp_LHS;
int threshold_temp_RHS;
int temp_LHS;
int temp_RHS;
bool temperatureAlarm;
bool activeZones[4];

typedef void (*settings_ptr)(void);
typedef void (*page_ptr)(void);


void Home_page();
void Settings_page();
void Temp_sensor_page();
void Alarm_duration_page();
void tempCheck();
void wait_for_button_press(char *message);

settings_ptr settings[4] = {Date_time_setting_loop, ZoneLoop, tempThreshLoop, alarm_duration_settings_page};
page_ptr pages[2] = {Home_page, Settings_page};

typedef enum
{
    HOME, SETTINGS
} STATE;
STATE currentState;
int current_alarm_duration;

const char *saved = "Settings saved";
const char *loaded = "Settings loaded";
const char *buttonPress = "press a button";
const char *toContinue = "to continue";

void mainInit()
{
    currentState = HOME;
    for(char i = 0; i < 4; i++)
    {
        activeZones[i] = false;
    }

    current_alarm_duration = 2;
    initTempSensor(); //call system initialize function  
    initLCD();
    ButtonInit();
    ZoneInit();
    buzzerInit();
    Port_init_rtc(); //port initilize.
    ds1302_init(); //DS1302 initilize.
    Set_time_rtc();
    threshold_temp_LHS = 0;
    threshold_temp_RHS = 0;
}

void SaveZones()
{

    char i;
    unsigned volatile char zones = 0;
    for(i = 0; i < 4; i++)
    {
        if(activeZones[i] == 1)
        {
            zones |= 1 << i;
        }
    }



    volatile unsigned char save_Data[10];
    save_Data[DATE_DAY] = (dateTime.Day);
    save_Data[DATE_MONTH] = (dateTime.Month);
    save_Data[DATE_YEAR] = (dateTime.Year);
    save_Data[DATE_HOURS] = (dateTime.Hour);
    save_Data[DATE_MINUTES] = (dateTime.Minute);
    save_Data[DATE_SECONDS] = (dateTime.Second);
    save_Data[ZONES] = zones;
    save_Data[ALARM_DURATION] = (unsigned char) current_alarm_duration;
    save_Data[THRESHOLD_TENS] = threshold_temp_LHS + 0x36; //+ the offset to make sure it the value isn't negative
    save_Data[THRESHOLD_UNITS] = threshold_temp_RHS;


    volatile unsigned char *ptr = save_Data;
    for(i = 0; i < 10; i++)
    {
        eeprom_write(DATA_START_ADDRESS + i, *ptr++);
        Delay_loop(1000);
    }

    wait_for_button_press(saved);

}

void LoadZones()
{
    int i;
    volatile unsigned int value = 0;

    volatile unsigned char load_data[10];



    for(i = 0; i < 10; i++)
    {
        load_data[i] = eeprom_read(DATA_START_ADDRESS + i);
        Delay_loop(1000);
    }
    current_alarm_duration = load_data[ALARM_DURATION];
    DateTime date = *convertDateFromArray(load_data);
    Write_updated_date_time_rtc(&date);
    threshold_temp_LHS = load_data[THRESHOLD_TENS] - 0x36; //remove the offset
    threshold_temp_RHS = load_data[THRESHOLD_UNITS];
    for(i = 3; i >= 0; i--)
    {
        if((load_data[ZONES]) & (1 << i))
        {
            activeZones[i] = 1;
        }
    }

    wait_for_button_press(loaded);
}

void updateVariables()
{
    get_temp();
    Get_time_rtc();
    Update_Global_DateTime();
    tempCheck();
    ZoneCheck();

}

void tempCheck()
{
    temperatureAlarm = ((temp_LHS > threshold_temp_LHS) || (temp_LHS == threshold_temp_LHS && (temp_RHS > threshold_temp_RHS)));
}

void main()
{
    mainInit();
    clear_lines();


    //call system initialize function  
    while (1)
    {
        pages[currentState]();
    }
}

void Home_page()
{
    clear_lines();
    while (1)
    {
        updateVariables();
        get_temp();
        char buf[16];
        sprintf(buf, "temp:%03d.%02d", temp_LHS, temp_RHS);
        Write_line(buf, 0);
        Write_Date(1);
        Write_Time(2);


        if(PORTE & 0x01)
        {
            SaveZones();
        }

        if(PORTE & 0x02)
        {
            LoadZones();
        }

        char choice = (PORTB & BUTTON_MASK);

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

    while (1)
    {
        updateVariables();
        Write_line("Date/Time", 0);
        Write_line("Zones", 1);
        Write_line("Temp", 2);
        Write_line("Alarm duration", 3);

        unsigned char choice = (PORTB & SETTINGS_MASK);
        choice = (PORTB & SETTINGS_MASK);
        if(single_key_pressed(choice)) // check to see if 1 and only 1 bit is set
        {
            Delay_loop(1000);
            ClearButtons();
            Delay_loop(1000);
            settings[convert_from_bit_pos(choice)]();
            clear_lines();
            currentState = HOME;
            return;

        }
        if((PORTE & 0x07))
        {
            currentState = HOME;
            return;
        }


        break;
    }

}

void wait_for_button_press(char *message)
{
    clear_lines();
    Write_line(message, 0);
    Write_line("press a button", 1);
    Write_line("to continue", 2);
    while (!(PORTB & BUTTON_MASK) && (!(PORTE & BUTTON_MASK)))
    {
        /* do nothing */
    }
    Delay_loop(10001);
    ClearButtons();
    Delay_loop(10001);
}





