
#define RS RA5
#define RW RA4
#define E  RA3
#define PSB RA2
#define CL_HOME 0b00000001
#define HOME 0b00000011
#define LEFT 0b00010111



#define SET_CGRAM_ADDR (addr) return (0x40 | addr);


#include "lcd.h"
#include "clock.h"

DateTime *dateTime;
void Write_string(char a[]);

const char lines[] = {LINE_1, LINE_2, LINE_3, LINE_4};

enum CurrentPage {
    Home
};

void cmd(char cmd) {
    RS = 0;
    RW = 0;
    E = 0;
    Delay_loop(50);
    E = 1;
    PORTD = cmd;
    Delay_loop(50);
    E = 0;
    Delay_loop(50);
}

void initLCD() {
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

void data(char data) {
    RS = 1;
    RW = 0;
    E = 0;
    Delay_loop(50);
    E = 1;
    PORTD = data; // set cursor at start
    Delay_loop(50);
    E = 0;
    Delay_loop(50);
}

void Write_string(char a[]) {

    char i = 0;
    while (a[i] != '\0') {
        data(a[i]);
        i++;
    }
    for (; i < 16; ++i) {
        data(' ');
    }
}

void Write_line(char param[], char lineNo) {
    cmd(lines[lineNo]);
    Write_string(param);
}

void clear_lines() {

    for (char i = 0; i < 4; i++) {
        cmd(lines[i]);
        Write_string(BLANK_LINE);
    }
}
char str[10];

void Write_Date(char lineNo) {
    
    char tmp[3];
    char temstr[16] = "";
    dateTime = get_current_date_time();
    int_to_string(tmp, dateTime->Day);
    concat_strings(tmp, "/");
    concat_strings(temstr, tmp);
    int_to_string(tmp, dateTime->Month);
    concat_strings(tmp, "/");
    concat_strings(temstr, tmp);
    int_to_string(tmp, dateTime->Year);
    concat_strings(temstr, tmp);

    Write_line(temstr, lineNo);
}

void Write_Time(char lineNo) {
    char tmp[3];
    char temstr[16] = "";

    int_to_string(tmp, dateTime->Hour);
    concat_strings(tmp, ":");
    concat_strings(temstr, tmp);
    int_to_string(tmp, dateTime->Minute);
    concat_strings(tmp, ":");
    concat_strings(temstr, tmp);
    int_to_string(tmp, dateTime->Second);
    concat_strings(temstr, tmp);

    Write_line(temstr, lineNo);
}

void Write_Time_Settings(DateTime *date, char lineNo) {

    char tmp[3];
    char temstr[16] = "";
    Write_line(" H   M  S", lineNo++);
    int_to_string(tmp, date->Hour);
    concat_strings(tmp, ":");
    concat_strings(temstr, tmp);
    int_to_string(tmp, date->Minute);
    concat_strings(tmp, ":");
    concat_strings(temstr, tmp);
    int_to_string(tmp, date->Second);
    concat_strings(temstr, tmp);
    Write_line(temstr, lineNo);
}

void Write_Date_Settings(DateTime *date, char lineNo) {

    char tmp[3];
    char temstr[16] = "";
    Write_line(" D   M  Y", lineNo++);
    int_to_string(tmp, date->Day);
    concat_strings(temstr, tmp);
    concat_strings(temstr, "  ");
    int_to_string(tmp, date->Month);
    concat_strings(temstr, tmp);
    concat_strings(temstr, "  ");
    int_to_string(tmp, date->Year);
    concat_strings(temstr, tmp);
    Write_line(temstr, lineNo);
}