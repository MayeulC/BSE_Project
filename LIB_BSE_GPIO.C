/* This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.
	 
   This file contains the functions used to configure the GPIO. It does
	 NOT configure the crossbar.
	 
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

#include "LIB_BSE_GPIO.h"

void Config_GPIO(void)
{
	P2MDOUT = 0x7b; //P2.7 and P2.2 configured as open drain, the others as
							    // push-pull.
	P2=~0x7b;       //configure the open drains as input; output low on the 
									// others.
		
	P3MDOUT = 0x7c; //P3.0, P3.1 and P3.7 as open drain; push-pull for the others 
	
	P3=0x87;        //configure the open drains as input; output low on the 
									// others, excepted P3.2, which must be output high by default
	P1MDOUT |= 0x40;//Configures P1.6 (LED) as push-pull
}

void Pulse_P20(void)
{
	P2__0=1;
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	P2__0=0;
}

void Pulse_P21(void)
{
	P2__1=1;
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	_nop_ ();
	P2__1=0;
}

void Demo_GPIO(void)
{
	
}
