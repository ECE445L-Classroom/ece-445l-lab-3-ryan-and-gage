//SwitchDriver.h

#define leftswitch 0
#define rightswitch 1
#define enterswitch 2

#include <stdint.h>

//Initalizes the switches
void switchinit(void);

//Reads the switch
uint8_t switchRead(uint8_t inputswitch);

