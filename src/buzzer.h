/* 
 * File:   buzzer.h
 * Author: 463929
 *
 * Created on 07 December 2017, 17:18
 */

#ifndef BUZZER_H
#define	BUZZER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define pin RC5
    
void soundBuzzer();
void buzzerInit();
#ifdef	__cplusplus
}
#endif

#endif	/* BUZZER_H */