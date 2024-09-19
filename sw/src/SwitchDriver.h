//SwitchDriver.h

#define leftswitch 1
#define rightswitch 2
#define enterswitch 4

#include <stdint.h>


//Initalizes the switches
void switchInit(void);

//Reads the debounced switch
uint8_t switchRead(uint8_t inputswitch);

