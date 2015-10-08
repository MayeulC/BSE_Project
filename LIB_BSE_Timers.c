#include "LIB_BSE_Timers.h"


void Config_Timer2(void)
{
  T2CON = 0x00; // Resetting different parametres

  CKCON&= (1<<5); // CKCON.5 = T2M when set to one uses SYSCLK/12

  TM2RL = T2RLDVAL;
  TMR2  = 0xffff;
  ET2   = 1; //Activation of Timer2
  PT2   = 0; // Priority of Timer2 (change this afterwards)

  T2CON |= 1<<2; // Activating Timer2

}

void ISR_Timer2(void) interrrupt 5
{
  // Controlling the RTC

  // If it works correctly, Timer2 overflows every 5ms.
  RTC_5ms += 1;
  if (RTC_5ms == 200) // 200*5ms = 1s
    RTC_Secondes += 1;
  if (RTC_Secondes == 60) // 60s = 1m
    RTC_Minutes +=1;
  if (RTC_Minutes == 60) // 60m = 1h
    RTC_Heures +=1;

  // LED

}


void Clear_RTC(void)
{
  RTC_5ms      =0;
  RTC_Secondes =0;
  RTC_Minutes  =0;
  RTC_Heures   =0;
}
