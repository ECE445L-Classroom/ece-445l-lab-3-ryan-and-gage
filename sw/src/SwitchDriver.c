#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

#include "../inc/SysTick.h"

void switchInit() // We will be using pins PE0 PE1 and PE2. //Need to make these pulldown Resistor
{
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;     // 1) activate clock for Port E
  while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R4) == 0){};// ready?
  GPIO_PORTE_AMSEL_R &= ~0x07;      // 3) disable analog on PE0+ 1 + 2
  GPIO_PORTE_PCTL_R &= ~0x00000FFF; // 4) PCTL GPIO on PE0+ 1 + 2
  GPIO_PORTE_DIR_R &= ~0x07;        // 5) direction PE0+ 1 + 2input
  GPIO_PORTE_AFSEL_R &= ~0x07;      // 6) PE0+ 1 + 2 regular port function
  GPIO_PORTE_DEN_R |= 0x07;         // 7) enable PE0+ 1 + 2 digital port}
}
uint8_t switchRead(uint8_t inputswitch) //  Debounced but may not work
{
	uint8_t hold = 0;
	hold = GPIO_PORTE_DATA_R & inputswitch; 
	SysTick80_Wait10ms(1);
	if((GPIO_PORTE_DATA_R & inputswitch) == hold) {return (GPIO_PORTE_DATA_R & inputswitch); }
	
	else
	{
		SysTick80_Wait10ms(1);
		return (GPIO_PORTE_DATA_R & inputswitch); 
	}	
	
}

