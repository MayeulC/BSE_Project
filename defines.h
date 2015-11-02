/*
   This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This files contains #defines and macros used by multiple files

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

#ifndef DEFINES_H
#define DEFINES_H

#include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"

/* MACROS */
#define min(x,y) ( (x) < (y) ? (x):(y))
#define max(x,y) ( (x) > (y) ? (x):(y))
#define abs(x) ( (x) < 0 ? (-(x)):(x))

/* DEFINES */
#define T2PERIOD 5 //ms // This was supposed to be defined elsewhere

/* Packages subsystem */
#define CONVASPEED 100 //cm/s
#define CONVBSPEED 100
#define CONVALENGTH 60 //cm
#define TRAVELTIME (CONVALENGTH*1000)/(CONVASPEED*T2PERIOD) //T2 tick
#define MAXPACKAGELENGTH 50 //cm
#define PACKAGE_GAUGE_TOLERANCE 10 //mm

/* system clock */
#define SYSCLK 22118400

/* UART0 */
#define BAUDRATE 115200

/* ADC0 */
#define ADC_TIMEOUT 8*16*3 // ADC clock is eight times slower than sysclk, it
                           //  needs 16 ticks. The timeout is three times this value.

/* Event dispatcher */
#define EVENT_QUEUE_LENGTH 32 //curently, max is 255 (unsigned char are used
                              // to browse the queue). This value is also used
                              // as an error code.
// Below, attempt to clean the queue if it reaches 85% capacity
#define EVENT_QUEUE_AUTO_CLEAN_THRESHOLD (EVENT_QUEUE_LENGTH*85)/100
// Below, attempt to remove elements from the queue if it reaches 110% capacity [disabled for now]
#define EVENT_QUEUE_AUTO_REMOVE_THRESHOLD (EVENT_QUEUE_LENGTH*110)/100


/* TYPES */
enum event_type{
    error,
    //reset, // This one is completly handled by the processInput function
    PPA_push,
    PPB_push,
    LED1_ON,
    LED2_ON,
    LED3_ON,
    LEDR_ON,
    LED1_OFF,
    LED2_OFF,
    LED3_OFF,
    LEDR_OFF,
    START_PES,
    STOP_PES,
    PRINT,
    NO_EVENT
    //QUERY_STATUS //the main() takes care of this one
};

enum package_types{
    TYPE1, //10cm
    TYPE2, //15cm
    TYPE3, //20cm
    OTHER, //25 to MAXPACKAGELENGTHcm
    ERROR,  // >MAXPACKAGELENGTHcm
    NO_PACKAGE
};

enum boolean{
    FALSE,
    TRUE
};

struct package{
    unsigned char weigth;
    enum package_types type;
};

struct packageCounter{ // Limited to 255 each, but we can print 99 at best, so...
    unsigned char num_packages;
    unsigned char num_packages1;
    unsigned char num_packages2;
    unsigned char num_packages3;

    unsigned char num_packages_processed1;
    unsigned char num_packages_processed2;
    unsigned char num_packages_processed3;
};

struct event{ // constructors available in LIB_BSE_Event_dispatcher.C
    enum event_type type;
    unsigned int deadline;
    enum package_types p;
    unsigned char uc;
    char * string;
    unsigned char discarded; // Boolean, marks the event as eraseable by
                             // the garbage collector
};

#endif //DEFINES_H
