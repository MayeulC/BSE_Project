/*
   This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.

   This file contains the GPIO declarations, that assign GPIO pins to
   the different functions performed. This is one of the starting files
   that were given at the begining of the project.

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

//------------------------------------------------------------------------------------
// Déclarations des GPIOs Projet BSE 2013
//------------------------------------------------------------------------------------
//
// AUTH: FJ
// DATE: 03-09-2013
// Target: C8051F02x
//
// Tool chain: KEIL Eval 'c'
//


//-----------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F02x
//-----------------------------------------------------------------------------

sfr16 DP       = 0x82;                 // data pointer
sfr16 TMR3RL   = 0x92;                 // Timer3 reload value
sfr16 TMR3     = 0x94;                 // Timer3 counter
sfr16 ADC0     = 0xbe;                 // ADC0 data
sfr16 ADC0GT   = 0xc4;                 // ADC0 greater than window
sfr16 ADC0LT   = 0xc6;                 // ADC0 less than window
sfr16 RCAP2    = 0xca;                 // Timer2 capture/reload
sfr16 T2       = 0xcc;                 // Timer2
sfr16 RCAP4    = 0xe4;                 // Timer4 capture/reload
sfr16 T4       = 0xf4;                 // Timer4
sfr16 DAC0     = 0xd2;                 // DAC0 data
sfr16 DAC1     = 0xd5;                 // DAC1 data

// Eléments présents sur la carte 8051FO20
sbit  LED = P1^6;         // green LED: '1' = ON; '0' = OFF
sbit Pushbutton = P3^7;
// Elements standard de port
sbit P2__0 = P2^0;
sbit P2__1 = P2^1;
sbit P2__2 = P2^2;
sbit P2__3 = P2^3;
sbit P2__4 = P2^4;
sbit P2__5 = P2^5;
sbit P2__6 = P2^6;
sbit P2__7 = P2^7;
sbit P3__0 = P3^0;
sbit P3__1 = P3^1;
sbit P3__2 = P3^2;
sbit P3__3 = P3^3;
sbit P3__4 = P3^4;
sbit P3__5 = P3^5;
sbit P3__6 = P3^6;
sbit P3__7 = P3^7;

// Eléments de l'application Pilotage d'un système de tri
sbit Tst4 = P3^4;
sbit Test_1 = P3^4;
sbit Tst5 = P3^5;
sbit Test_2 = P3^5;
sbit Tst6 = P3^6;
sbit Tst7 = P3^7;
sbit DETECT = P2^2;
sbit RAZ_RTC = P3^0;
sbit START_Sys = P3^1;
sbit RAZ_CP = P2^7;
sbit CHG_DCT = P2^6;
sbit CT3_DCT = P2^5;
sbit CT2_DCT = P2^4;
sbit CT1_DCT = P2^3;
sbit SIG_Erreur = P3^2;
sbit Decl_PP2 = P2^1;
sbit Decl_PP1 = P2 ^0;
sbit Decl_PES = P3^3;
