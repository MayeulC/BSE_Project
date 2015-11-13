/* This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This file contains event dispatcher functions

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

#include "LIB_BSE_Event_dispatcher.h"

void dispatch(void)
{
    enum package_types current_weighed=NO_PACKAGE;
    static enum boolean scale_free=TRUE; //Yes, this is an assumption
    unsigned char remaining_loops=5; // To avoid staying too long
    unsigned char next;

    processInput();

    if(event_num == 0)
        return; // nothing to do

    while( remaining_loops)
    {
        next = nextEvent();
        if(next==EVENT_QUEUE_LENGTH) // no suitable event
            break;
        remaining_loops--;
        switch(event_queue[next].type) {
            case PPA_push:
                //TODO : check that it hasn't expired
                if(!scale_free)
                    break; //just discard it, there is nothing we can do
                Pulse_P20(); //push PPA
                scale_free=FALSE;
                current_weighed=event_queue[next].p;
                addEvent(Event(START_PES,timestamp));
                addEvent(Event(STOP_PES,timestamp+1));
                break;
            case PPB_push:
                Pulse_P21(); //push PPB
                scale_free=TRUE;
                current_weighed=NO_PACKAGE;
                break;
            case LED1_ON:
                CT1_DCT=0;
                break;
            case LED2_ON:
                CT2_DCT=0;
                break;
            case LED3_ON:
                CT3_DCT=0;
                break;
            case LEDR_ON:
                CHG_DCT=0;
                break;
            case LED1_OFF:
                CT1_DCT=1;
                break;
            case LED2_OFF:
                CT2_DCT=1;
                break;
            case LED3_OFF:
                CT3_DCT=1;
                break;
            case LEDR_OFF:
                CHG_DCT=1;
                break;
            case START_PES:
                Decl_PES=1;
                break;
            case STOP_PES:
                Decl_PES=0;
                break;
            case PRINT:
                Waiting_PKG.type=current_weighed;
                Waiting_PKG.weigth=event_queue[next].uc;
                // The main will call the print function  (with "M ..... m")
                // note : 5ms ~= 500char@115200 bauds
                break;
            case error:
                event_num=0;
                SIG_Erreur=0;
                // Scale must be freed whenever there's an error.
                // This could be smarter.
                scale_free=TRUE;
                Waiting_PKG.type=ERROR;
                Waiting_PKG.meta=event_queue[next].string;
                break;
            default:
                makeError(string_e_defaultEvent);
        }
        // Since we proceeded it, it is no longer useful. We however
        // add a "backdoor" for packages that might get pushed later
        event_queue[next].discarded=!event_queue[next].discarded;
    }
    if(event_num > EVENT_QUEUE_AUTO_REMOVE_THRESHOLD)
        removeUseless();
    else if(event_num > EVENT_QUEUE_AUTO_CLEAN_THRESHOLD)
        cleanEvents();
}

void addEvent(struct event e)
{	
    char temp_IE = IE; // interrupt-safe

    if(SIG_Erreur ==0)
        return; // if we are in error mode, don't do anything

    EA = 0;

    event_num++;
    if(event_num >= EVENT_QUEUE_LENGTH)
    {
        event_queue[0].type=error;
        event_queue[0].string=string_e_queue_full;
        event_num=1;
    }
    else
    {
        event_queue[event_num-1]=e;
    }
    IE = temp_IE;

}

int nextEvent(void) // TODO : make this less dumb
{
    unsigned char i=0;
    unsigned char candidate=EVENT_QUEUE_LENGTH;
    enum event_type returningtype=NO_EVENT;
    unsigned char encounteredPPB_Push=EVENT_QUEUE_LENGTH; //not yet
    if(event_num == 0)
        return candidate; // Skip a few corner cases

    while(i<event_num) // All the events are candidate
    {
        if(!event_queue[i].discarded) // If still valid, we continue
        {
            if(event_queue[i].type == error ) // This one is of the utmost importance
                return i;                     // must be processed as soon as possible
            if(event_queue[i].deadline == timestamp ||
               event_queue[i].deadline == timestamp -1)
            {
                candidate=i; //we could have broken the loop, if not for the line below
            }
            if(event_queue[i].type == PPB_push) // Those too are here to be processed ASAP
                encounteredPPB_Push=i;
        }
        i++;
    }
    if(candidate!=EVENT_QUEUE_LENGTH &&
            event_queue[candidate].type==PPA_push &&
            encounteredPPB_Push!= EVENT_QUEUE_LENGTH)
        return encounteredPPB_Push; // Artificially prioritize these
    return candidate;
}

void cleanEvents(void)
{
    unsigned char i=0;
    unsigned char shift=0;
    // Always read at i+shift, write at i. Unless shift=0, of course.
    while(i+shift<event_num)
    {
        if(event_queue[i+shift].discarded)
        {
            shift++;
            continue;
        }
        if(shift)
            event_queue[i]=event_queue[i+shift];
        i++;
    }
    event_num-=shift;
}

void processInput(void)
{
    packageDetection();
    if(RAZ_RTC == 0)
        Clear_RTC();
    if(RAZ_CP == 0)
        clearPackageCounter();
    if(START_Sys == 0)
    {
        event_num=0;
        SIG_Erreur=1;
    }
}

void makeError(const char *message)
{
    addEvent(EventS(error,timestamp,message));
}

void removeUseless(void)
{
    // This function is a placeholder for now
}

// event constructors
struct event Eventp(enum event_type type,
                    unsigned int deadline,
                    enum package_types p)
{
    struct event e;
    e.type=type;
    e.deadline=deadline;
    e.p=p;
    e.discarded=0;
    return e;
}

struct event Event(enum event_type type,
                   unsigned int deadline)
{
    struct event e;
    e.type=type;
    e.deadline=deadline;
    e.discarded=0;
    return e;
}
struct event EventS(enum event_type type,
                    unsigned int deadline,
                    char * string)
{
    struct event e;
    e.type=type;
    e.deadline=deadline;
    e.discarded=0;
    e.string = string;
    return e;
}
