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

#include "LIB_BSE_Packages.h"

void packageDetection(void)
{
    //Note : a state machine implementation could have been done here
    static unsigned char previousStatus=0;
    static unsigned int statusChange=0; //Timestamp
    unsigned char status=DETECT;
    unsigned int deltaT;
    unsigned int package_length; //mm
    enum package_types type;
    unsigned int deadline;
    
    if(status!=previousStatus)
    {
        deltaT=timestamp-statusChange; //duration of the transit /T2PERIOD
			  if(deltaT>-deltaT) //timer overflow occured
				    deltaT=-deltaT;
        statusChange=timestamp;
        if(status==0 & previousStatus == 1) // falling edge, package detected
        {
					  previousStatus=status;
            //TODO : we also need to detect small intervals.

            package_length=((deltaT*T2PERIOD)*CONVASPEED)/100;// n*ms*cm/s
            if(package_length > MAXPACKAGELENGTH ||
                    deltaT>(65535/(T2PERIOD*CONVASPEED))-1) // overflow check
            {
                makeError(string_e_package_too_big);
                return;
            }

            if((package_length+PACKAGE_GAUGE_TOLERANCE)%50
                    > 2*PACKAGE_GAUGE_TOLERANCE) //exceeds tolerance
            {
                addEvent(Event(LEDR_ON,timestamp));
                addEvent(Event(LEDR_OFF,timestamp+100/T2PERIOD));
                return; // note : 5cm+-tol is accepted. probably not a big deal.
            }
            switch((package_length+PACKAGE_GAUGE_TOLERANCE)/50){
            case 2: //10cm+-tolerance
                type=TYPE1;
                deadline=TRAVELTIME+(5000)/(CONVASPEED*T2PERIOD);
                num_packages.num_packages++;
                num_packages.num_packages1++;
						    addEvent(Event(LED1_ON,timestamp));
                addEvent(Event(LED1_OFF,timestamp+100/T2PERIOD));
                break;
            case 3: //15cm
                type=TYPE2;
                deadline=TRAVELTIME+(7500)/(CONVASPEED*T2PERIOD);
                num_packages.num_packages++;
                num_packages.num_packages2++;
						    addEvent(Event(LED2_ON,timestamp));
                addEvent(Event(LED2_OFF,timestamp+100/T2PERIOD));
                break;
            case 4: //20cm
                type=TYPE3;
                deadline=TRAVELTIME+(10000)/(CONVASPEED*T2PERIOD);
                num_packages.num_packages++;
                num_packages.num_packages3++;
						    addEvent(Event(LED3_ON,timestamp));
                addEvent(Event(LED3_OFF,timestamp+100/T2PERIOD));
                break;
            default:
                num_packages.num_packages++;
						    addEvent(Event(LEDR_ON,timestamp));
                addEvent(Event(LEDR_OFF,timestamp+100/T2PERIOD));
                return;
            }
            addEvent(Eventp(PPA_push,deadline+timestamp,type));
        }
				else
				{
					previousStatus=status;
				}
    }
}

void clearPackageCounter(void)
{
    struct packageCounter pc={0};
		num_packages=pc;
}

struct packageCounter getPackageCounter(void)
{
    return num_packages;
}
