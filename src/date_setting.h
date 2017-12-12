/* 
 * File:   date_setting.h
 * Author: 462767
 *
 * Created on 12 December 2017, 17:22
 */

#ifndef DATE_SETTING_H
#define	DATE_SETTING_H


#include "clock.h"
#include "lcd.h"



#define BUTTON_MASK 0x0F
#define INCREMENT   0x01
#define DECREMENT   0x02
#define MOVE_RIGHT  0x04
#define MOVE_LEFT   0x08


#define TOGGLE_LINE 0x01
#define BACK        0x02
#define SET         0x04


#define START_CURSOR_POSITION 0x48

void Date_time_setting_loop();





#endif	/* DATE_SETTING_H */

