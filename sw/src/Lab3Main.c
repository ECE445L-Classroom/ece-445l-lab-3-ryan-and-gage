// Lab3Main.c
// Runs on LM4F120/TM4C123
// Uses ST7735.c to display the clock
// patterns to the LCD.
//    16-bit color, 128 wide by 160 high LCD
// Mark McDermott, Daniel Valvano and Jonathan Valvano
// Lab solution, do not post
// August 3,2024

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2024

 Copyright 2024 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// Specify your hardware connections, feel free to change
// PD0 is squarewave output to speaker
// PE0 is mode select
// PE1 is left
// PE2 is right 
// PE3 is up
// PE4 is down
// if alarm is sounding, any button will quiet the alarm

#include <stdio.h>
#include <stdint.h>
#include "../inc/ST7735.h"
#include "../inc/PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/Timer0A.h"
#include "Lab3.h"
#include "SwitchDriver.h"
#include "SpeakerDriver.h"
#include "SysDriver.h"
#include "../inc/LCDDisplay.h"
// ---------- Prototypes   -------------------------
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode

uint8_t state = 0;
//These are the following states:
// 0 = Visual/Idle
// 1 = Main Menu
// 2 = Set Time
// 3 = Set Alarm
// 4 = Set Visual 

uint8_t myInputs = 0;
int main(void){
	
  DisableInterrupts();
  PLL_Init(Bus80MHz);    // bus clock at 80 MHz
	switchInit();
	speakerInit();
	sysInit();
  // write this
  EnableInterrupts();
  while(1){
		
		myInputs = newInputs();
		
		switch (state) {
				case 0: //Visual/Idle
				Visuals(myInputs);
						break;

				case 1: //Main Menu
					MainMenu(myInputs);
						break;

				case 2: //Set Time
					SetTime(myInputs);
						break;

				case 3:  //Set Alarm
					SetAlarm(myInputs);
						break;

				case 4: //Set Visual 
					SetVisual(myInputs);
						break;

				default:  //Visual/Idle
						state = 0;
						break;
		}
		
  }
}


//Keep track of pressed buttons and when we have new inputs. 
uint8_t newInputs()
{
		switchRead(leftswitch);
		switchRead(rightswitch);
		switchRead(enterswitch);
	
	return 1;
}

void Visuals(uint8_t inputs)
{
}
void MainMenu(uint8_t inputs)
{
}
void SetTime(uint8_t inputs)
{
}
void SetAlarm(uint8_t inputs)
{
}

void SetVisual(uint8_t inputs)
{
}


