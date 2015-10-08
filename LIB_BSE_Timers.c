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
