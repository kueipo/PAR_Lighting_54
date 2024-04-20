#ifndef __BSP_ADC_H
#define __BSP_ADC_H
#include "py32f0xx_hal.h"

extern unsigned int adc_value[9];

extern ADC_HandleTypeDef hadc;
extern void APP_ADCConfig(void);
extern void ADC_ValGet(void);


#endif /*__BSP_ADC_H*/


