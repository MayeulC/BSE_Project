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
    enum package_types current_weighed=OTHER;
    static boolean scale_free=TRUE; //Yes, this is an assumption

    if(event_num == 0)
        return; // nothing to do

    processInput();

    unsigned char next = nextEvent();
    switch(event_queue[next].type) {
        case PPA_push:
            //TODO : check that it hasn't expired
            if(!scale_free)
                break; //just discard it, there is nothing we can do
            Pulse_P20(); //push PPA
            // Todo : check if plate is free before doing so
            switch((enum package_types)(event_queue[next].meta)){
                case TYPE1:
                    addEvent({LED1_ON,timestamp});
                    addEvent({LED1_OFF,timestamp+100/T2PERIOD});
                    break;
                case TYPE2:
                    addEvent({LED2_ON,timestamp});
                    addEvent({LED2_OFF,timestamp+100/T2PERIOD});
                    break;
                case TYPE3:
                default:
                    addEvent({LEDR_ON,timestamp});
                    addEvent({LEDR_OFF,timestamp+100/T2PERIOD});
            }
            scale_free=FALSE;
            current_weighed=(enum package_types)(event_queue[next].meta);
            addEvent({START_PES,timestamp});
            addEvent({STOP_PES,timestamp+1});
            break;
        case PPB_push:
            Pulse_P21(); //push PPB
            scale_free=TRUE;
            current_weighed=OTHER;
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
            // Call print function  (with "M ..... m")
            // note : 5ms ~= 500char@115200 bauds
            break;
        case QUERY_STATUS:
            // Print status
            break;
        case error:
        default:
            event_num=0;
            SIG_Erreur=1;
            send_error_info(event_queue[next].meta);
    }
    // Since we proceeded it, it is no longer useful. We however
    // add a "backdoor" for packages that might get pushed later
    event_queue[next].discarded=!event_queue[next].discarded;

    if(event_num > EVENT_QUEUE_AUTO_REMOVE_THRESHOLD)
        removeUseless();
    else if(event_num > EVENT_QUEUE_AUTO_CLEAN_THRESHOLD)
        cleanEvents();
}

void addEvent(struct event e) //Note : this must be called in an interrupt-safe way (TODO)
{
    event_num++;
    event_queue[event_num]=e;
}

int nextEvent(void) // TODO : make this less dumb
{
    unsigned char i=0;
    unsigned char candidate=0;
    unsigned int bestDeadline=-1; // TODO : change to something meaningful

    if(event_num == 0)
        return NULL; // Skip a few corner cases

    while(i<event_num)
    {
        if(!event_queue[i].discarded) // If still valid, we continue
        {
            if(bestDeadline>event_queue[i].deadline)
            {
                candidate=i;
                bestDeadline=event_queue[i].deadline;
            }
            if(event_queue[i].type == error ||
               event_queue[i].type == reset) // These are of the utmost importance
                return i; // must be processed as soon as possible
        }
    }

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
    if(RAZ_CP)
        clearPackageCounter();
    if(RAZ_Sys)
    {
        event_num=0;
        SIG_Erreur=0;
    }
}

void makeError(const char *message)
{
    addEvent({error,timestamp,message});
}

void removeUseless(void)
{
    // This function is a placeholder for now
}
