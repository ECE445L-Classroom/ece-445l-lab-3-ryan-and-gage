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

uint32_t Alarm_Time = 0xFFFFFFFF;
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
		
		if(myInputs)
			TurnOffAlarm();
		
		//Check For Alarm
		if(getTime() == Alarm_Time)
		{
			TurnOnAlarm();
		}
		
		
		
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
		uint8_t oldLeft; 
		uint8_t oldRight;
		uint8_t oldEnter;

uint8_t newInputs() // Will give us the most the posEdge of each input
{
		oldLeft = switchRead(leftswitch);
		oldRight = switchRead(rightswitch);
		oldEnter = switchRead(enterswitch);
	
		if(switchRead(leftswitch) && ~oldLeft)
		{
			return leftswitch;
		}
		else if(switchRead(rightswitch) && ~oldRight)
		{
			return rightswitch;
		}
		else if(switchRead(enterswitch) && ~oldEnter)
		{
			return enterswitch;
		}
	
	return 0;
}

void Visuals(uint8_t inputs)
{
	//Make a call to show the clock
	
	if(inputs) //We had a button press, so we should go to main menu
		state = 1;
}


uint8_t menuPointer = 0; //For all menus, there will be several options. We will use the same pointer between them,
//which will be updated by left and right swith calls, and this will get reset between state changes. 

void MainMenu(uint8_t inputs) // Done But Needs update screen
{
	//Update the visual on screen
	
	if(inputs & leftswitch)
	{
		if(menuPointer>0) // Only move to the left if we are not at the far left
		{
			menuPointer--;
		}
		
	}
	else if(inputs & rightswitch)
	{
		if(menuPointer<4) // Only move to the right if we are not at the far right
		{
			menuPointer++;
		}
	}
		
	else if(inputs & enterswitch)
	{
		state = menuPointer + 2; //Should work out as long as we order the menu options the same order of the time, alarm, visual
		menuPointer = 0;
	}

}


uint8_t SetHour = 0;
uint8_t SetMinute = 0;
uint8_t SetSecond = 0;
uint8_t ChangeValue = 0;

void SetTime(uint8_t inputs) // Done But Needs update screen
{
	//Update the visual on screen
	if(ChangeValue)
	{
		if(inputs & enterswitch) ChangeValue = 0;
		
		else if(menuPointer == 0) // Hour
		{
			if(inputs & leftswitch) 
				SetHour = (SetHour - 1)%60;

				
				else if(inputs & rightswitch)
					SetHour = (SetHour + 1)%60;
		}
			
		else if(menuPointer == 1) // Minute
		{
			if(inputs & leftswitch)
				SetMinute = (SetMinute - 1)%60;
				else if(inputs & rightswitch)
					SetMinute = (SetMinute + 1)%60;
		}
		
		else
		{
			if(inputs & leftswitch) // Second
				SetSecond = (SetSecond - 1)%60;
				
				else if(inputs & rightswitch)
					SetSecond = (SetSecond + 1)%60;
		}
	}
	
	else // Not Updating the Time
	{
		if(inputs & leftswitch)
	{
		if(menuPointer>0) // Only move to the left if we are not at the far left
		{
			menuPointer--;
		}
		
	}
	else if(inputs & rightswitch)
	{
		if(menuPointer<4) // Only move to the right if we are not at the far right
		{
			menuPointer++;
		}
	}
		
	else if(inputs & enterswitch)
	{
		if(menuPointer <3)
		ChangeValue = 1;
		
		else if(menuPointer == 3)//Confirm
		{
			updateTime(SetHour * 3600 + SetMinute * 60 + SetSecond);
				SetHour = 0;
				SetMinute = 0;
				SetSecond = 0;
				menuPointer =0;
				state = 0;
		}
		else //Exit
		{
				SetHour = 0;
				SetMinute = 0;
				SetSecond = 0;
			menuPointer =0;
			state = 0;
		}
	}
	}
	
	
	
		
	
}
void SetAlarm(uint8_t inputs)
{
	//Update the visual on screen
	if(ChangeValue)
	{
		if(inputs & enterswitch) ChangeValue = 0;
		
		else if(menuPointer == 0) // Hour
		{
			if(inputs & leftswitch) 
				SetHour = (SetHour - 1)%60;

				
				else if(inputs & rightswitch)
					SetHour = (SetHour + 1)%60;
		}
			
		else // Minute
		{
			if(inputs & leftswitch)
				SetMinute = (SetMinute - 1)%60;
				else if(inputs & rightswitch)
					SetMinute = (SetMinute + 1)%60;
		}
	}
		
	
	else // Not Updating the Time
	{
		if(inputs & leftswitch)
	{
		if(menuPointer>0) // Only move to the left if we are not at the far left
		{
			menuPointer--;
		}
		
	}
	else if(inputs & rightswitch)
	{
		if(menuPointer<3) // Only move to the right if we are not at the far right
		{
			menuPointer++;
		}
	}
		
	else if(inputs & enterswitch)
	{
		if(menuPointer <2)
		ChangeValue = 1;
		
		else if(menuPointer == 2)//Confirm
		{
				Alarm_Time = SetHour * 3600 + SetMinute * 60 + SetSecond;
				SetHour = 0;
				SetMinute = 0;
				SetSecond = 0;
				menuPointer =0;
				state = 0;
		}
		else //Exit
		{
				SetHour = 0;
				SetMinute = 0;
				SetSecond = 0;
			menuPointer =0;
			state = 0;
		}
	}
	}
	
	
	
		
	
}

void SetVisual(uint8_t inputs)
{
	//Update the visual on screen
		if(inputs & leftswitch)
	{
		if(menuPointer>0) // Only move to the left if we are not at the far left
		{
			menuPointer--;
		}
		
	}
	else if(inputs & rightswitch)
	{
		if(menuPointer<2) // Only move to the right if we are not at the far right
		{
			menuPointer++;
		}
	}
		
	else if(inputs & enterswitch)
	{
		if(menuPointer==0) // Update visual
		{
		}
			
		else if( menuPointer==1) // Update visual
		{
		}
			
		else
		{
		state = 0; //Should work out as long as we order the menu options the same order of the time, alarm, visual
		menuPointer = 0;
		}
	}

}


