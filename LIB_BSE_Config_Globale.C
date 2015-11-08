/* 
   This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.
	 
   This file contains the Init_Device() and other functions it calls,
   to initialise the device.
	 
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

#include "LIB_BSE_Config_Globale.h"

void Init_Device(void)
{
    EA = 0;
    Init_RST();
    Init_CLK();
    Init_XBAR();
    Config_GPIO();
    Config_INT1();
    CFG_UART0();
    CFG_ADC0();
    CFG_DAC0();
    Config_Timer2();
    EA = 1;
}


void Init_RST(void)
{
    // Normally we don't need EA, but it doesn't hurt anyone to be safe
    WDTCN = 0xDE;
    WDTCN = 0xAD;
}

void Init_CLK(void)
{
    int i;
    // We are supposed to have  OSCXCN = 0110 0111
    OSCXCN = 0x67;

    for(i=0; i<3000; i++);
    while( (OSCXCN & 0x80) == 0);

    OSCICN = 0x08;
}

void Init_XBAR(void)
{
    XBR0      = 0x04; // Enable UART0
    XBR1      = 0x10; // Enable INT1
    XBR2      = 0x40; // Enable crossbar
}
