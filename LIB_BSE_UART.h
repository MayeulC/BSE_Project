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

#include "defines.h"
#include "LIB_BSE_strings.h"
#include <intrins.h>

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
 * Its configuration is done in CFG_Clock_UART0
 */
void CFG_UART0(void);


/*
 * char Putchar(char c, int csg_tempo)
 *
 * The write function. Writes thj character c in SBUF0
 *
 * The Algorithm:
 * If csg_tempo = 0, return 0
 *
 * Check if the flag TI0 is 1 so we can transmit
 * if true,
 *        Put the c in SBUF0
 *        Set TI0 = 0
 *        return c
 * If not, wait 100 us then call Putchar(c, csg_tempo-1) 
 *
 * 
 */
char Putchar(char c, int csg_tempo);

/*
 * int Send_String(char *char_ptr)
 * 
 * Sends a string using Putchar several times.
 * If a single Putchar fails, it return 0.
 * Othewise, it returns the number of strings sent.
 */
int Send_String(char *char_ptr);

/*
 * char Getchar(void)
 * 
 * The read function. Reads the the character in SBUF0
 *
 * The Algorithm:
 * Checks if RI0 is 1
 * if true, 
 *    c = SBUF0
 *    RI0 = 0
 *    return c
 * if not,
 *    return 0
 *
 */
char Getchar(void);

/*
 * void demo1(void)
 * 
 * A small echo function. 
 * Waits for a character.
 * When it gets it, it sends it back 2 times. 
 */ 
 void demo1(void);

/*
 * void demo2(void)
 * 
 * Another small echo function. 
 * As long as new character isn't received, it sends the same char.
 */ 
 void demo2(void);

/*
 * void CONV_Pes_Val(unsigned char value, char * string)
 *
 * This function converts a number into a 3 char string.
 *
 */
void CONV_Pes_Val(unsigned char value, char * string);

/*
 * void sendStatus(void)
 *
 * Ths functions replies to a status request, sending statistics about
 * operations.
 *
 */
void sendStatus(void);

/*
 * void print(enum package_types type)
 *
 * Prints the label on the package
 *
 */
enum package_types type(enum package_types type);

#endif //LIB_BSE_UART_H

