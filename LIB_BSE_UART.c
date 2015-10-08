/* 
   This program is designed to be compiled with Keil µVision4's ANSI C
	 compiler, and ran on a 8051F020 microcontroller.
	 
        This file contains the files to configure the UART0, its clock and the functions used to read and write. 
	 
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


#include "LIB_BSE_UART.h"


void CFG_Clock_UART0(void)
{

  // The Baud source clock is Timer1
  TCLK =0;
  RCLK =0;

  //T1M = 0, Timer1 uses system clock

  CKCON |= (1<<4);

  // CFG of TH1

  TH1 = 256 - (1/16)*(SYSCLK/BAUDRATE); // Should be 244 = F4 

}
