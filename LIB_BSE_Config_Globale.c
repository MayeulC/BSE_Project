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


void Init_Device(void)
{
  
  Init_RST();
  Init_CLK();

}


void Init_RST(void)
{
  // Normally we don't need EA, but it doesn't hurt anyone to be safe
  EA    = 0;
  WDTCN = 0xDE;
  WDTCH = 0xAD;
  EA    = 1;
  
}

void Init_CLK(void)
{

  // We are supposed to have  OSCXCN = 0110 0111
  OSCXCN = 0x67; 

  int i;
  for(i=0; i<3000; i++);
  while( (OSCXCN & 0x80) == 0);
 
  OSCICN = 0x08;
}

void Init_IO(void)
{

}
