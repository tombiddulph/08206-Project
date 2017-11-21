#ifndef RTC_H
#define RTC_H




#define RTC_CLK RB0
#define RTC_IO  RB4
#define RTC_RST RB5

#define RTC_SERIAL_MASK 0x80


#define RTC_SEC_WRITE       0x80
#define RTC_SEC_READ        0x81
#define RTC_MIN_WRITE       0x82
#define RTC_MIN_READ        0x83
#define RTC_HOUR_WRITE      0x84
#define RTC_HOUR_READ       0x85
#define RTC_DATE_WRITE      0x86
#define RTC_DATE_READ       0x87
#define RTC_MONTH_WRITE     0x88
#define RTC_MONTH_READ      0x89
#define RTC_DAY_WRITE       0x8A
#define RTC_DAY_READ        0x8B
#define RTC_YEAR_WRITE      0x8C
#define RTC_YEAR_READ       0x8D
#define RTC_COTNROL_WRITE   0x8E
#define RTC_CONTROL_READ    0x8F
#define RTC_TRICKLE_WRITE   0x90
#define RTC_TRICKLE_READ    0x91

void RTC_Init(void);
void RTC_Cmd(unsigned cmd);
void RTC_Write(unsigned char address, unsigned char value);
unsigned char RTC_Read(unsigned char address);
void RTC_Serial_Write(unsigned char value);
unsigned char RTC_Serial_Read(void);


#endif