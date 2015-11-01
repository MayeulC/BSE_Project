/* This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This file contains the event dispatcher function prototypes and
   declarations.
   The purpose of the event dispatcher is to maintain a list of tasks,
   and choose when to dedicate ressources to a task. It is responsible
   for the coordination between different tasks, and ensure that the
   "best effort" is always done in order to meet the task requirements,
   and to keep efficiency at its maximum.
   The event dispatcher can either be ran from a loop or from an ISR, ie
   a timer.
   Further improvements may include : dynamically adjust power states
   and system clock based on power demand. Unfortunately, the 8051
   doesn't have a lot of power options, which makes such a development
   rather useless.

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

#ifndef LIB_BSE_EVENT_DISPATCHER_H
#define LIB_BSE_EVENT_DISPATCHER_H
#include "LIB_BSE_Event_dispatcher.h"
#include "defines.h"
#include "LIB_BSE_strings.h"

/* EXTERNS */
extern void Pulse_P20(void);
extern void Pulse_P21(void);
extern void packageDetection(void);
extern void clearPackageCounter(void);
extern void Clear_RTC(void);
extern void Send_String(char * string);

/* GLOBALS */
extern struct package Waiting_PKG; // this one is in the main
extern unsigned int timestamp; //See timer2 files
/*
 * This is the event queue. It is the single most important variable in
 * this project. It is basically a todo list containing various elements
 * to process. If full, it emits the error state, and the whole must be
 * manually cleared, thus loosing any current operation. If this happens,
 * try reducing the load on the system (by reducing the conveyor speed,
 * for example), or increasing its size.
 * The associated variable is the event counter which tells the number of
 * events currently in memory.
 *
 */

static struct event event_queue[EVENT_QUEUE_LENGTH];
static unsigned char event_num=0;


/* FUNCTIONS */

/*
 * void dispatch(void)
 *
 * Once called, this evaluates if the next event can be processed, and
 * does so if it is the case. It also puts new event in the queue.
 *
 */
void dispatch(void);

/*
 * void addEvent(void)
 *
 * This function adds an event to the queue
 *
 */
void addEvent(struct event e);

/*
 *  struct event * nextEvent(void)
 *
 * This function finds and returns the index of the next event to be
 * processed, even if it has expired.
 *
 */
int nextEvent(void);

/*
 * void cleanEvents(void)
 *
 * This function cleans the event queue, removing discarded events, and
 * compacting the queue. It may be quite long to return, depending on the
 * queue length.
 *
 */
void cleanEvents(void);

/*
 * void processInput(void)
 *
 * This function goes trough every input, and adjusts the current state
 * accordingly. Note that it cannot be faster than the pooling frequency :
 * if it is called every 5ms, events shorter than that might not be caught.
 * This belongs to the event dispatcher as, well, input can be considered
 * as an event.
 *
 */
void processInput(void);

/*
 * void makeError(const char * message)
 *
 * This function inserts a new event in the events queue, with the
 * associated messages. These messages are then sent trough the UART, and
 * switch the program to an error state.
 *
 */
void makeError(const char * message);

/*
 * void removeUseless(void)
 *
 * This function tries to remove doubles from the event queue if there are
 * some, it also checks if an event is really useful, and deletes it if not.
 * Please note that calling this function is NOT really SAFE, and you only
 * want to do it if you are completely running out of memory. Moreover, it
 * might take a long time to perform.
 * Use this function at YOUR OWN RISKS
 *
 */
void removeUseless(void);

/*
 * event EventX(enum event_type, unsigned int, void*);
 *
 * These functions create a new event with the parameters they get, and return it.
 * Multiple constructors exists depending on the type of parameters to be set.
 * Note : Since this is a new event, discarded is automatically put at 0
 * 
 */

struct event Eventp(enum event_type type,
																 unsigned int deadline,
																 enum package_types p);
struct event Eventuc(enum event_type type,
																 unsigned int deadline,
																 unsigned char uc);
struct event Event(enum event_type type,
																 unsigned int deadline);
struct event EventS(enum event_type type,
																 unsigned int deadline,
										char * string);

#endif // LIB_BSE_EVENT_DISPATCHER_H
