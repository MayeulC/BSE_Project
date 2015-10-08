/*
   This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This file contains the files to configure the UART0, its clock and
   the read/write functions.

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


#ifndef LIB_BSE_UART_H
#define LIB_BSE_UART_H

#include "LIB_BSE_Config_Globale.h"

#define BAUDRATE 115200
/*
 * void CFG_Clock_UART0(void)
 *
 * We will use Timer1 as our timer for UART0. (TCLK0 = RCLK = 0)
 * To have the correct Baudrate, we have to an appropiate TH1
 *
 * The equation is TH1 = 256 - (1/16)*(SYSCLK/BAUDRATE)
 * with SMOD0 =1, T1M = 1
 *
 */
void CFG_Clock_UART0(void);


/*
 * void CFG_UART0(void)
 *
 * We want UART0 to have 8 bits of data, 1 Stop bit; and no parity.
 * The baudrate is given by a Timer.
 * Its configuration is done in CFG_UART0
 */
#endif LIB_BSE_UART_H
