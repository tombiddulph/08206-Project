#include "buzzer.h"
#include "Commonheader.h"
#include "clock.h"


int current_alarm_duration;

void buzzerInit()
{
	TRISC5 = 0;               /* Configure TRISB7 as o/p              */
	pin = 0;
}


void soundBuzzer()
{
	pin = 1;
	Delay_loop(1000);
	pin = 0;

}