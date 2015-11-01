/*
   This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This file contains the function prototypes for the package management
   system.

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

#ifndef LIB_BSE_PACKAGES_H
#define LIB_BSE_PACKAGES_H
#include "defines.h"
#include "LIB_BSE_strings.h"

/* Externs */
extern void addEvent(struct event e);
extern void makeError(const char * message);

/* Globals */
struct packageCounter num_packages=0;

/*
 * packageDetection(void);
 *
 * This function analyses the signal generated by the detector to determine
 * each packet's length. It then adds a new event to process the packet if
 * necessary, at the right time.
 * In case on an oversized packet (>50cm), it generates an error.
 */
void packageDetection(void);

/*
 * void clearPackageCounter(void)
 *
 * This functions resets the package counter to 0
 *
 */
void clearPackageCounter(void);

/*
 * unsigned int getPackageCounter(void)
 *
 * Returns the current package count
 *
 */
struct packageCounter getPackageCounter(void);

#endif //LIB_BSE_PACKAGES_H
