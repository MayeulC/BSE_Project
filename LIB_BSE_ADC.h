/* 
   This program is designed to be compiled with Keil µVision4's ANSI C
	 compiler, and ran on a 8051F020 microcontroller.
	 
  This file contains the files to configure the ADC and other functions releated to ADC 
	 
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
#ifndef LIB_BSE_ADC_H
#define LIB_BSE_ADC_H

#include "defines.h"
#include <intrins.h>

/*
 * void CFG_VREF(void)
 *
 * Configuring the Reference voltage
 */
void CFG_VREF(void);

/*
 * void CFG_ADC0(void)
 *
 * Configuring ADC0 
 */
void CFG_ADC0(void);

#endif