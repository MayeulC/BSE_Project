/* This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This file contains the prototypes of the LIB_BSE_INT_Ext.C functions.

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

#ifndef LIB_BSE_INT_Ext_H
#define LIB_BSE_INT_Ext_H
#include "defines.h"
#include "LIB_BSE_strings.h"

/* Externs */
extern void addEvent(struct event e);
extern unsigned char ACQ_ADC(void);
extern unsigned int timestamp;
extern struct event Eventuc(enum event_type type,
																 unsigned int deadline,
																 unsigned char uc);
extern struct event EventS(enum event_type type,
																 unsigned int deadline,
										char * string);

/* Functions */

/*
 * void Config_InT1(void)
 *
 * This function enables INT1, and sets its priority to low.
 * It configures INT1 as an edge-triggered interrupt.
 */
void Config_INT1(void);

/*
 * void ISR_INT1(void)
 *
 * This ISR is called when iNT1 is triggered.
 * For now, it is mostly a placeholder, emitting a signal on P3^4.
 */
void ISR_INT1(void);

#endif //LIB_BSE_INT_Ext_H
