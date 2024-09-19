
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "SpeakerDriver.h"
#include "../inc/Timer1A.h"

//My theory is if we create a square wave that follwos a 1khz frequency and connect that to the
//gate of a mosfet, that should generate a 1khz frequency in the output of the mosfet which will lead to the speaker.

//We can use a timer to manage the frequency
uint8_t ON_OFF = 0;


void speakerInit()
{
			// Speaker is PB4
	
	    /* Port B Activation */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;               // enable GPIO Port B clock 
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1) == 0){};    // allow time for activating 
    
    /* Port B Set Up */
    GPIO_PORTB_CR_R = 0x10;                                // allow changes to PB4
    GPIO_PORTB_DIR_R = 0x10;                               // make PB4 output
			GPIO_PORTB_AMSEL_R &= ~0x10;                         // disable analog on PB4   X0F00 X00F0 -> XF0FF XFF0F. & These to get F00F
    GPIO_PORTB_PCTL_R &= ~GPIO_PCTL_PB4_M;            		 // configure PB4 as GPIO by clearing alternative ctrl bits in that mask

    GPIO_PORTB_AFSEL_R  &= ~0x10;                          // disable alt functtion on PB4
    GPIO_PORTB_DEN_R = 0x10;                               // enable digital I/O on PB4
	
			
		Timer1A_Init(&speakerOut,80000,2); // If the period is 1/80mHz, and we want 1 kHz
}

void speakerOut(void)
{
	//If Timer reachs count down, flip the output
	if(ON_OFF)
		GPIO_PORTB_DATA_R ^= 0x10;
	else
		GPIO_PORTB_DATA_R &= ~0x10;
}

void TurnOnAlarm()
{
	ON_OFF = 1;
}

void TurnOffAlarm()
{
	ON_OFF = 0;
}



