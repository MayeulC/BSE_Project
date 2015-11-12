#include "LIB_BSE_ADC.h"

void CFG_VREF(void)
{
    REF0CN=3; // AD0VRS configured to use Vref0 pin as the reference voltage.
              // Internal voltage reference is enabled, as well as the Bias generator.
	
}

void CFG_ADC0(void)
{
    CFG_VREF();
    AMX0CF &= ~(1<<1); // AIN23IC = 0 to configure AIN3 as a single-ended input

    // Below is the clock configuration. The datasheet (p58) specifies a clockrate
    //  of CLKsar0=2.5MHz, which means that SYSCLK/CLKsar0-1=7.8 ~ 8.
    //  This is the value we put in AD0SC
    ADC0CF = (8<<3) + 1;
    ADC0CN = 0x81; // Conversion initiated on AD0BUSY flag,  data is right-justified,
                   //  Also activates ADC0 in continuous tracking mode.

    AMX0SL=3; // Channel select register configured to read from AIN3, this shouldn't
              //  change.
}

unsigned char ACQ_ADC(void)
{
    unsigned char not_timed_out=ADC_TIMEOUT;
    AD0INT=0;  // Clears the conversion complete flag
    AD0BUSY=1; // Initiates the measurement
    while(not_timed_out && !AD0INT)
        not_timed_out--;

		AD0BUSY=0;
		AD0INT=0;
    if(!not_timed_out) // timed out
        return 0;
		
    return ADC0H;
}
