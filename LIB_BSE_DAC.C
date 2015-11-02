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
