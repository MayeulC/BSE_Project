/* This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This file contains Function declarations of LIB_BSE_DAC.C

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

//------------------------------------------------------------------------------





//*****************************************************************************
//FONCTIONS de MANIPULATION DU DAC0 -
// Peut étre utilisé pour tester le Fct de l'ADC
//*****************************************************************************

//*****************************************************************************
//Cfg_DAC0
//
//	 La conversion est déclenchée par écriture dans DAC0H (Fonction Send_to_DAC0)
//
//*****************************************************************************
void CFG_DAC0(void);

//*****************************************************************************
//Send_to_DAC0
//	  Utilisation du DAC en mode 8bits (les 8 bits de Pds Fort)
//
//
//*****************************************************************************
void Send_to_DAC0(unsigned char Output_DAC);
