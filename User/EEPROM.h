#ifndef _EEPROM_H
#define _EEPROM_H
#include "py32f0xx_hal.h"

void Error_Handler(void);
extern void WriteUserSetDataIntoEEPROM(void);
extern void UserSetInit(void);


#endif /*_EEPROM_H*/


