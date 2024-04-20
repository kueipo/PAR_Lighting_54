#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H
#include "py32f0xx_hal.h"
#include "py32f0xx_ll_gpio.h"


//out put
//SEG1
#define SEG1_GPIO_PIN    LL_GPIO_PIN_4    //5      //key4
#define SEG1_GPIO_PORT   GPIOF

//SEG2
#define SEG2_GPIO_PIN    LL_GPIO_PIN_0    //17     //key3
#define SEG2_GPIO_PORT   GPIOB

//SEG3
#define SEG3_GPIO_PIN    LL_GPIO_PIN_2    //13     //key2
#define SEG3_GPIO_PORT   GPIOA

//SEG4
#define SEG4_GPIO_PIN    LL_GPIO_PIN_1    //19    //key1
#define SEG4_GPIO_PORT   GPIOB

//SEG5
#define SEG5_GPIO_PIN    LL_GPIO_PIN_4     //15
#define SEG5_GPIO_PORT   GPIOA

//SEG6
#define SEG6_GPIO_PIN    LL_GPIO_PIN_7
#define SEG6_GPIO_PORT   GPIOA

//input
#define MIC_GPIO_PIN    LL_GPIO_PIN_2
#define MIC_GPIO_PORT   GPIOB
#define MIC_GPIO_READ   LL_GPIO_IsInputPinSet(MIC_GPIO_PORT,MIC_GPIO_PIN)


extern void APP_GPIOConfig(void);


#endif /*__BSP_GPIO_H*/






