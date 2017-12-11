
#define RS RA5
#define RW RA4
#define E  RA3
#define PSB RA2
#define CL_HOME 0b00000001
#define HOME 0b00000011
#define LEFT 0b00010111

#include <xc.h>
#include <string.h>
#include "lcd.h"

const int lines[] = { LINE_1, LINE_2, LINE_3, LINE_4 };


enum CurrentPage { Home };


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
 
   int i = 0;
	while (a[i] != '\0')
	{
		data(a[i]);
		i++;
	}
   for (; i < 15; ++i)
	{
		data(' ');
	}
}

void Write_float(float fl)
{
 data(fl);
}

void Second_line(char param[])
{
    
    cmd(LINE_2); // set cursor to 16 second line
    Write_string(param);
}
void Write_line(char param[], int lineNo)
{
    cmd(lines[lineNo]);
    Write_string(param);  
}

void clear_line(int lineNo)
{
    cmd(lines[lineNo]);
    Write_string(BLANK_LINE);
}

void Write_Date(int lineNo)
{
    char str[7];
    sprintf(str, "%02d/%02d/%02d", dateTime.Day, dateTime.Month, dateTime.Year);
    Write_line(str, lineNo);
}

void Write_Time(int lineNo)
{ 
    char str[10];
    sprintf(str, "%02d:%02d:%02d", dateTime.Hour, dateTime.Minute, dateTime.Second);
    Write_line(str, lineNo);
}