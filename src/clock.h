#ifndef RTC_H
#define RTC_H

#define RTC_CLK RB0
#define RTC_IO  RB4
#define RTC_RST RB5

#define RTC_CMD_MASK 0x80

#define RTC_CONTROL_REGISTER 0x8F
#define RTC_TRICKLE_CHARGE_WRITE 0x90
#define RTC_TRICKLE_CHARGE_READ  0x91

void RTC_Init(void);
void RTC_Cmd(char cmd);

#endif