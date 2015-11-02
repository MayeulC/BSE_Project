/* This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This file contains declarations and function prototypes used in the main

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

#ifndef BSE_MAIN_H
#define BSE_MAIN_H
#include "defines.h"
extern void Init_Device(void);
extern void Send_String(char *);
extern char Getchar(void);
extern void Putchar(char,int);
extern void demo1(void);
extern void demo2(void);
extern void Send_to_DAC0(unsigned char Output_DAC);
extern unsigned char ACQ_ADC(void);
extern int Package_flag;

void main(void);

void Package_detection(void);

#endif //BSE_MAIN_H
