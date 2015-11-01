/*
   This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This files contains #defines and macros used by multiple files

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

#ifndef DEFINES_H
#define DEFINES_H

#include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"

/* system clock */
#define SYSCLK 22118400

/* UART0 */
#define BAUDRATE 115200

/* ADC0 */
#define ADC_TIMEOUT 8*16*3 // ADC clock is eight times slower than sysclk, it
                           //  needs 16 ticks. The timeout is three times this value.

/* Event dispatcher */
#define EVENT_QUEUE_LENGTH 32 //curently, max is 255 (unsigned char are used to browse the queue)
// Below, attempt to clean the queue if it reaches 85% capacity
#define EVENT_QUEUE_AUTO_CLEAN_THRESHOLD (EVENT_QUEUE_LENGTH*85)/100
// Below, attempt to remove elements from the queue if it reaches 110% capacity [disabled for now]
#define EVENT_QUEUE_AUTO_REMOVE_THRESHOLD (EVENT_QUEUE_LENGTH*85)/100

#endif //DEFINES_H
