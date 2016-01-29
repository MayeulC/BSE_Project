/* This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This file contains Functions to configure and use the DAC0. This is
   one of the files that were given at the begining of the project.
   Its main purpose is to validate the ADC code by mirroring the voltage
   variations.

   Copyright (C) 2015  François Joly <francois.joly@cpe.fr>

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
/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_DAC
; 	TARGET MCUs	: C8051F020, 
; 	DESCRIPTION	: Fonctions Bas niveau pour le TP EMBARQUE
;
; 	REVISION 1.0
;
;---------------------------------------------------------------------------*/
//-------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>                    // SFR declarations
#include <intrins.h>  
//#include <Ports_Declarations_TP_Emb.h> 
//------------------------------------------------------------------------------


//*****************************************************************************
//FONCTIONS de MANIPULATION DU DAC0 - 
// Peut être utilisé pour tester le Fct de l'ADC
//*****************************************************************************

//*****************************************************************************	 
//Cfg_DAC0
//
//	 La conversion est déclenchée par écriture dans DAC0H (Fonction Send_to_DAC0)
// 
//*****************************************************************************
void CFG_DAC0(void)
{
	DAC0CN = 0;   // Stop DAC
				 // Update on Write to DAC0H
	DAC0CN  |= 0x04;   // 8 bits MSB dans DAC0H
	DAC0L = 0;		   // Init 4 bits LSB à 0
	DAC0CN  |= 0x80;   // DAC démarré
	DAC0H = 0;		   // Initialisation Sortie DAC = 0;
	
}

//*****************************************************************************	 
//Send_to_DAC0
//	  Utilisation du DAC en mode 8bits (les 8 bits de Pds Fort)
//
// 
//*****************************************************************************
void Send_to_DAC0(unsigned char Output_DAC)
{
   DAC0H = Output_DAC;	
	
}
