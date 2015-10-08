/* 
   This program is designed to be compiled with Keil µVision4's ANSI C
	 compiler, and ran on a 8051F020 microcontroller.
	 
	 This file contains the config_Timer2(), ISR2_Timer2() and void Clear_RTC functions
	 and the global variables used.
	 
   Copyright (C) 2015  Aydin Alperen <alperen.aydin@cpe.fr>
   Copyright (C) 2015  Cantan Mayeul <mayeul.cantan@cpe.fr>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/
#ifndef LIB_BSE_TIMERS_H
#define LIB_BSE_TIMERS_H


#include <c8051f020.h>                    // SFR declarations

//Definitions

#define T2PERIOD 5 /*ms*/
#define T2RLDVAL /*65635*/ -(SYSCLK/12/1000)*T2PERIOD

unsigned char RTC_5ms;
unsigned char RTC_Secondes;
unsigned char RTC_Minutes;
unsigned char RTC_Heures; 


/*
 * void Config_Timer2(void)
 *
 * This function configures the TIMER2 interruption of 8051F020.
 * The period is 5ms => frequency of 200Hz
 * It is a 16 bit timer with Auto-recharge.
 * The overflow will call the function ISR2_Timer2
 * 
 */
void Config_Timer2(void);

/*
 * void ISR_Timer2(void)
 *
 * This is an interruptuion function. It is called when Timer2 overflows.
 * The 
 *
 * Note: This is a skeleton. For now, it only tuns on anf off a LED. More stuff will be eventually added.  
 */
void ISR_Timer2(void);

/*
 * void Clear_RTC(void)
 *
 * Resets the clock
 *
 */
void Clear_RTC(void);


#endif 
