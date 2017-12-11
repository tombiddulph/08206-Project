
#define RS RA5
#define RW RA4
#define E  RA3
#define PSB RA2
#define CL_HOME 0b00000001
#define HOME 0b00000011
#define LEFT 0b00010111

#include <pic.h>

#include "lcd.h"






void LCD_delay (int j) {
for (unsigned i=0; i<j; i++);
}
int increase(int x)
{
    x++;
    return x;
}

void cmd(char cmd)
{
    RS = 0;
    RW = 0;
    E = 0;
    LCD_delay (50);
    E = 1;
    PORTD = cmd; 
    LCD_delay(50);
    E = 0;
    LCD_delay(50);
}

void initLCD()
{
    ADCON1 = 0x06; // digital output
    TRISA = 0x00;
    TRISD = 0x00;
    PORTA = 0;
    PORTD = 0;
    PSB = 1;    
    
    cmd(0x0f); // set cursor at start
    cmd(0x38);
    cmd(0b00111000); // 2 lines

}



void data(char data)
{
    RS = 1;
    RW = 0;
    E = 0;
    LCD_delay (50);
    E = 1;
    PORTD = data; // set cursor at start
    LCD_delay(50);
    E = 0;
    LCD_delay(50);
}
void Write_string(char a[])
{
 
    char *p = a;
    while (*p != '\0') 
    {
       data(*p++);
    } 
}

void Write_float(float fl)
{
 data(fl);
}

void Second_line(char param[])
{
    
    cmd(0b10010000); // set cursor to 16 second line
    Write_string(param);
}
void Write_line(char param[], int lineNo)
{
    switch (lineNo)
    {
        case 1:
            cmd(HOME);
            break;
        case 2:
            cmd(0b10010000); // set cursor to 16 second line
            break;
        case 3:
            cmd(0b10001000); // set cursor to 8 3rd line
            break;
        case 4:
            cmd(0b10011000); // set cursor to 24 4th line
            break;
    }
    Write_string(param);  
    
}

void clear_line(int lineNo)
{
    switch (lineNo)
    {
        case 1:
            cmd(HOME);
            Write_string("                ");
            break;
        case 2:
            cmd(0b10010000); // set cursor to 16 second line
            Write_string("                ");
            break;
        case 3:
            cmd(0b10001000); // set cursor to 8 3rd line
            Write_string("                ");
            break;
        case 4:
            cmd(0b10011000); // set cursor to 24 4th line
            Write_string("                ");
            break;
    }
}

void Write_Date(int lineNo)
{
    char str[7];
    sprintf(str, "%d/%d/%d", dateTime.Day, dateTime.Month, dateTime.Year);
    Write_line(str, lineNo);
}

void Write_Time(int lineNo)
{
    char str[7];
    sprintf(str, "%d:%d:%d", dateTime.Hour, dateTime.Minute, dateTime.Second);
    Write_line(str, lineNo);
}