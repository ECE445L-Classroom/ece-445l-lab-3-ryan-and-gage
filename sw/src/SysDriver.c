#include <stdint.h>
#include "../inc/SysTickInts.h"

uint32_t totalSeconds = 0;
void sysInit()
{
	SysTick_Init(80000000); // Every second
}

void SysTick_Handler() // We will use this to keep track of clock
{
	totalSeconds ++;
	//Increment a variable on seconds
}


uint32_t getTime()
{
	return totalSeconds;
}

void updateTime(uint32_t newSeconds)
{
	totalSeconds = newSeconds;
}