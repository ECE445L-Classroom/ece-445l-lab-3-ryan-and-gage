#include <stdint.h>

void LCDDisplay_Init();

void DisplayTimeLightMode(uint16_t hour, uint16_t minute, uint16_t second);

void DisplayTimeDarkMode(uint16_t hour, uint16_t minute, uint16_t second);

void DisplayDigitalTime();

void AlarmStateBlinking();