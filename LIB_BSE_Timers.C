/* 
   This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This file contains the config_Timer2(), ISR2_Timer2(), Clear_RTC()
   functions.

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

#include "LIB_BSE_Timers.h"


void Config_Timer2(void)
{
    T2CON = 0x00; // Resetting different parametres

    CKCON&= ~(1<<5); // CKCON.5 = T2M when set to one uses SYSCLK/12

    RCAP2 = T2RLDVAL;
    T2    = 0xffff;
    ET2   = 1; //Activation of Timer2
    PT2   = 0; // Priority of Timer2 (change this afterwards)

    T2CON |= 1<<2; // Activating Timer2

}

void ISR_Timer2(void) interrupt 5
{
    P3__5 =1; // Observable on the scope

    // RTC control
    // If it works correctly, Timer2 overflows every 5ms.
    RTC_5ms += 1;
    if (RTC_5ms == 200) // 200*5ms = 1s
    {
        RTC_Secondes += 1;
        RTC_5ms=0;
    }
    if (RTC_Secondes == 60) // 60s = 1m
    {
        RTC_Secondes=0;
        RTC_Minutes +=1;
    }
    if (RTC_Minutes == 60) // 60m = 1h
    {
        RTC_Minutes=0;
        RTC_Heures +=1;
    }

    timestamp++; // WARNING : loops every 65536*T2PERIOD, which is here 326s
    dispatch();

    if(timestamp%5) //frequently tidy the queue
        cleanEvents();

    // Clear the timer overflow flag
    TF2 = 0;

    P3__5 = 0;
}


void Clear_RTC(void)
{
    RTC_5ms      =0;
    RTC_Secondes =0;
    RTC_Minutes  =0;
    RTC_Heures   =0;
    // note that we don't clear the timestamp in order to be able to process
    // incoming events at the right time.
}
