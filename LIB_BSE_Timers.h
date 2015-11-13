/*
   This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This file contains the config_Timer2(), ISR2_Timer2(), Clear_RTC()
   functions prototypes and the global variables used.

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


#include "defines.h"

/* Defines */

#define T2RLDVAL /*65635*/ -(SYSCLK/12/1000)*T2PERIOD

// RTC = Real Time Clock
unsigned char RTC_5ms      =0;
unsigned char RTC_Secondes =0;
unsigned char RTC_Minutes  =0;
unsigned char RTC_Heures   =0;
unsigned int timestamp=0;

// Package detection

int Package_detected = 0;
//if 0, there is no package
//if not 0, the Package_detected*5ms*10m/s is the length of the package

/* EXTERNAL FUNCTIONS */
extern void dispatch(void);
extern void cleanEvents(void);
/* Functions */

/*
 * void Config_Timer2(void)
 *
 * This function configures the TIMER2 interruption of 8051F020.
 * The period is 5ms => frequency of 200Hz
 * It is a 16 bit timer with Auto-recharge.
 * The overflow will call the function ISR2_Timer2
 *
 * Modified registers: T2CON, CKCON, RCAP2L, RCAP2H, TL2, TH2
 * See datasheet p.237-239 for more details
 */
void Config_Timer2(void);

/*
 * void ISR_Timer2(void)
 *
 * This is an interruptuion function. It is called when Timer2 overflows.
 * It increments the RTC.
 * Launches some periodic actions like the event dispatcher
 * Writes to P3__5
 * Clears the TF2 flag
 *
 */
void ISR_Timer2(void);

/*
 * void Clear_RTC(void)
 *
 * Resets the RTC back to 0
 *
 */
void Clear_RTC(void);


#endif
