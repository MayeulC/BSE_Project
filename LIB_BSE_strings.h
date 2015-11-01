/*
   This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This files contains strings that might be displayed to the user

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
#ifndef LIB_BSE_STRINGS_H
#define LIB_BSE_STRINGS_H

#ifdef LIB_BSE_UART_H
const char * string_e_package_too_big="Error, measured size exceeds "
                                             "max package size\r\n";

const char * string_e_defaultEvent = "Unknown event type\r\n";

const char * string_e_package_not_normed = "Error, measured size exceeds "
                                                  "max gauge tolerance\r\n";
																									
char string_status_request[73]="R \r\n"
                                          "RTC: xx/yy/zz \r\n" //last is 20th
                                          "T1 : xx/yy \r\n"
                                          "T2 : xx/yy \r\n"
                                          "T3 : xx/yy \r\n"
                                          "HG : xx/yy \r\n";


char string_label[35]="Tx -- Pds :yyy0g \r\n" //19 char
                                 "H : xx/yy/zz \r\n";
																 
#else
extern const char * string_e_package_too_big;
extern const char * string_e_defaultEvent;
extern const char * string_e_package_not_normed;			
extern char string_status_request[73];
extern char string_label[35];
#endif
#endif //LIB_BSE_STRINGS_H
