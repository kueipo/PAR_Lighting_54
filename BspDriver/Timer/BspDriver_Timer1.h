#ifndef __BSP_TIME1_H
#define __BSP_TIME1_H
#include "py32f0xx_hal.h"

extern void APP_TIM1_PWM_Config(void);
extern void Tim1PwmDutySetChan1(uint16_t duty);
extern void Tim1PwmDutySetChan2(uint16_t duty);
extern void Tim1PwmDutySetChan3(uint16_t duty);
extern void Tim1PwmDutySetChan4(uint16_t duty);

  
#endif /*__BSP_TIME1_H*/


