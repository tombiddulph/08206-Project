/* 
 * File:   zones.h
 * Author: 463929
 *
 * Created on 12 December 2017, 14:42
 */

#ifndef ZONES_H
#define	ZONES_H

#include "Commonheader.h"



#define ZONE_MASK 0x0F
#define ZONE_0 0x00
#define ZONE_1 0x01
#define ZONE_2 0x04
#define ZONE_3 0x08    
    
    
bool activeZones[] = {false, false, false, false}; 
    
void SetZone(int zone);
void ZoneInit();
void ZoneCheck();
void ZoneLoop();

#endif	/* ZONES_H */