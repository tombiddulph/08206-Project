
#define RS RA5
#define RW RA4
#define E  RA3
#define PSB RA2
#define CL_HOME 0b00000001
#define HOME 0b00000011
#define LEFT 0b00010111
#include <pic.h>


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
    LCD_delay (1000);
    E = 1;
    PORTD = cmd; 
    LCD_delay(1000);
    E = 0;
    LCD_delay(1000);
}

void initialise_LCD()
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
    LCD_delay (1000);
    E = 1;
    PORTD = data; // set cursor at start
    LCD_delay(1000);
    E = 0;
    LCD_delay(1000);
}
void Write_string(char a[])
{
    int i = 0;
    while (a[i]!= '\0') 
    {
       data(a[i]);
       i++;
    } 
}

void Write_float(float fl)
{
 data(fl);
}

void Second_line(char param[])
{
    //cmd(0b10101000); // set cursor to 40
    //cmd(0b11010000); // set cursor to 80 second line
    cmd(0b10010000); // set cursor to 16 second line
    //cmd(0b10011000); // set cursor to 24 4th line
    //cmd(0b10001000); // set cursor to 8 3rd line
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

unsigned int number = 0;
