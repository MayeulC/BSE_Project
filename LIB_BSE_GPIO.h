/* This program is designed to be compiled with Keil ÂµVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This file contains the prototypes of the LIB_BSE_GPIO.C functions.

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

#ifndef LIB_BSE_GPIO_H
#define LIB_BSE_GPIO_H

#include "defines.h"
#include <intrins.h>

/*
 * void Config_GPIO(void)
 *
 * This function configures the GPIO, setting PORT pins in output/input
 * mode depending on the realized function
 */
void Config_GPIO(void);

/*
 * void Pulse_P20(void)
 *
 * This function generates a 500µs pulse on pin P2.0. It is blocking
 */
void Pulse_P20(void);

/*
 * void Pulse_P21(void)
 *
 * This function generates a 500µs pulse on pin P2.1. It is blocking
 */
void Pulse_P21(void);

/*
 * void Demo_GPIO(void)
 *
 * This function demonstrates the functionality of the various GPIO
 * elements
 */
void Demo_GPIO(void);

#endif //LIB_BSE_GPIO
