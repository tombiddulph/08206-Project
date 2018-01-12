
#define RS RA5
#define RW RA4
#define E  RA3
#define PSB RA2
#define CL_HOME 0b00000001
#define HOME 0b00000011
#define LEFT 0b00010111



#define SET_CGRAM_ADDR (addr) return (0x40 | addr);

#include <xc.h>
#include <string.h>
#include "lcd.h"


void Write_string(char a[]);

const int lines[] = {LINE_1, LINE_2, LINE_3, LINE_4};

enum CurrentPage
{
    Home
};

void LCD_delay(int j)
{
    for(unsigned i = 0; i < j; i++);
}

void cmd(char cmd)
{
    RS = 0;
    RW = 0;
    E = 0;
    LCD_delay(50);
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

    cmd(DISPLAY_CURSOR_BLINK_ON); // set cursor at start
    cmd(BASIC_FUNCTION_SET_8BIT);
    //cmd(0b00110000); // 2 lines

}

void data(char data)
{
    RS = 1;
    RW = 0;
    E = 0;
    LCD_delay(50);
    E = 1;
    PORTD = data; // set cursor at start
    LCD_delay(50);
    E = 0;
    LCD_delay(50);
}

void Write_string(char a[])
{

    int i = 0;
    while (a[i] != '\0')
    {
        data(a[i]);
        i++;
    }
    for(; i < 16; ++i)
    {
        data(' ');
    }
}

void Write_line(char param[], int lineNo)
{
    cmd(lines[lineNo]);
    Write_string(param);
}

void clear_lines()
{

    for(char i = 0; i < 4; i++)
    {
        cmd(lines[i]);
        Write_string(BLANK_LINE);
    }
}
char str[10];
void Write_Date(int lineNo)
{
    
    sprintf(str, "%02d/%02d/%02d", dateTime.Day, dateTime.Month, dateTime.Year);
    Write_line(str, lineNo);
}

void Write_Time(int lineNo)
{
    

    sprintf(str, "%02d:%02d:%02d", dateTime.Hour, dateTime.Minute, dateTime.Second);
    Write_line(str, lineNo);
}

void Write_Time_Settings(DateTime date, int lineNo)
{
    
    Write_line(" H   M  S", lineNo++);
    sprintf(str, "%02d  %02d  %02d", date.Hour, date.Minute, date.Second);
    Write_line(str, lineNo);
}

void Write_Date_Settings(DateTime date, int lineNo)
{
    Write_line(" D   M  Y", lineNo++);
    sprintf(str, "%02d  %02d  %02d", date.Day, date.Month, date.Year);
    Write_line(str, lineNo);
}