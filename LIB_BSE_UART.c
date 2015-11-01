/* 
   This program is designed to be compiled with Keil µVision4's ANSI C
   compiler, and ran on a 8051F020 microcontroller.
	 
   This file contains the files to configure the UART0, its clock and the
   functions used to read and write.
	 
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


#include "LIB_BSE_UART.h"


void CFG_Clock_UART0(void)
{
  PCON=0x80; //stub; this is bad
  // The Baud source clock is Timer1
  TCLK0 =0;
  RCLK0 =0;

  CKCON |= (1<<4); //T1M = 1, Timer1 uses system clock
	TR1=1; //Enable Timer 1

  
  TMOD |= (1<<5);
	TMOD &= ~(1<<4 + 1<<7 + 1<<6);
	
  PCON |= (1<<7); // SMOD0 = PCON^7 =1

  // CFG of TH1

  //TH1 = 256 - (1/16)*(SYSCLK/BAUDRATE); 
	TH1= 0xF4; //fa
  // According to the docementation,
  // TH1 should be 0xF4 for a baudrate of 115200

}


void CFG_UART0(void)
{
	CFG_Clock_UART0();
  // The mode1 is chosen:
  // Asynchronous, Timer1 or Timer2 overflow
  // 8 data bits, 1 Start+1 Stop bit 
  SM00 = 0;
  SM10 = 1;

  // UART0 receive enabled
  REN0 = 1;

  // Transmit Interrupt Flag
  // This flag should be set to 1, so that Putchar can put char
  TI0 = 1;
	
}


char Putchar(char c, int csg_tempo)
{
  if(csg_tempo ==0)
    return 0;

  else{
    if(TI0 ==1)
      {
	SBUF0 = c;
	TI0  = 0;
	return c;
      }
    else
      {
	// wait 100us
	int i=100;
	while(i>0)
	{
		i--;
		_nop_ ();
	}

	return Putchar(c,csg_tempo-1);
      }
  }
}

int Send_String(char* char_ptr)
{
  int csg_tempo = 5;
  int i = 0;
  char c_return;
  char* c_send = char_ptr;
  
  while(*c_send != '\0' )
    {
      c_return = Putchar(*c_send, csg_tempo);
      if(c_return == 0) return 0;
      i++;
      c_send++;
    }
  return i;
}


char Getchar(void)
{
  char c;
  if(RI0 == 1)
    {
      c =SBUF0;
      RI0 = 0;
      return c;
    }
  else
    {
      return 0;
    }

}

void demo1(void)
{
	char c = Getchar();
	if (c != 0)
		{
			Putchar(c,2);
			Putchar(c,2);
			return;
		}
	else
		{
			return;
		}
}

void demo2(void)
{
	static char c = 'e';
	char n = Getchar();
	if(n != 0)
	{
		c = n;
	}
	Putchar(c,2);
}

void CONV_Pes_Val(unsigned char value, char * string)
{
    string[2]=value%10+'0';
    string[1]=(value/10)%10+'0';
    string[0]=(value/100)%10+'0';
}

void CONV_HMSC(unsigned char value, char * string)
{
    string[2]=value%10+'0';
    string[1]=(value/10)%10+'0';
}

void sendStatus(void)
{
    struct packageCounter num_packages;
    num_packages = getPackageCounter();
    CONV_HMSC(RTC_Minutes,string_status_request+10);
    CONV_HMSC(RTC_Secondes,string_status_request+13);
    CONV_HMSC(RTC_5ms/2,string_status_request+16);

    CONV_HMSC(num_packages.num_packages1,
              string_status_request+26);
    CONV_HMSC(num_packages.num_packages1,
              string_status_request+29);

    CONV_HMSC(num_packages.num_packages2,
              string_status_request+39);
    CONV_HMSC(num_packages.num_packages2,
              string_status_request+42);

    CONV_HMSC(num_packages.num_packages3,
              string_status_request+52);
    CONV_HMSC(num_packages.num_packages3,
              string_status_request+55);

    CONV_HMSC(num_packages.num_packages
              -num_packages.num_packages1
              -num_packages.num_packages2
              -num_packages.num_packages3,
              string_status_request+65);
    CONV_HMSC(0,string_status_request+68);

    Send_String(string_status_request);

    // TODO : complete this function
}
void print(enum package_types type, unsigned char weigth)
{
    string_label[1]=type+'1';
    // TODO : add weight
    // x*2500/(255*Vref/2) ~ 6 (5.94)
    CONV_Pes_Val(6*weigth,string_label+12);

    CONV_HMSC(RTC_Minutes,string_label+24);
    CONV_HMSC(RTC_Secondes,string_label+27);
    CONV_HMSC(RTC_5ms/2,string_label+30);

    Putchar('M'); //could have been in the string
    Send_String(string_label);
    Putchar('m');
}
