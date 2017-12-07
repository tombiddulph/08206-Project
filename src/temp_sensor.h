/* 
 * File:   temp_sensor.h
 * Author: 463929
 *
 * Created on 21 November 2017, 11:48
 */



#ifndef TEMP_SENSOR_H
#define	TEMP_SENSOR_H

#include <stdlib.h>
#include <math.h>


#define  uch unsigned char                   //                                          
# define DQ RA0                              //define 18B20 data PORT                    
# define DQ_DIR TRISA0                       //define 18B20 D PORT direct register       
# define DQ_HIGH() DQ_DIR =1                 //set data PORT INPUT                       
# define DQ_LOW() DQ = 0; DQ_DIR = 0 




void delay(char x,char y);
void display();
void init();
reset(void);
void write_byte(uch val);
uch read_byte(void);
void get_temp();
void Write_float(float fl);
void tempConverter(uch ten, uch unit, uch a, uch b, uch c, uch d, char* temp);


#endif	/* TEMP_SENSOR_H */

