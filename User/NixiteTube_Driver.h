#ifndef __NIXITE_TUBE_DRIVER_H 
#define __NIXITE_TUBE_DRIVER_H
#include "py32f0xx_hal.h"

//数码管段位
#define  LED_BIT_1     0x01
#define  LED_BIT_2     0x02
#define  LED_BIT_3     0x04
#define  LED_BIT_4     0x08
#define  LED_BIT_5     0x10
#define  LED_BIT_6     0x20

//buf0
#define  LED_BIT_2G     0x02    
#define  LED_BIT_4E     0x04   
#define  LED_BIT_2A     0x08    
#define  LED_BIT_3F     0x10     
#define  LED_BIT_1A     0x20
//buf1
#define  LED_BIT_1B     0x01     
#define  LED_BIT_4B     0x04     
#define  LED_BIT_2B     0x08     
#define  LED_BIT_3D     0x10     
#define  LED_BIT_4G     0x20   
//buf2
#define  LED_BIT_1C     0x01   
#define  LED_BIT_2F     0x02     
#define  LED_BIT_2C     0x08     
#define  LED_BIT_3E     0x10    
#define  LED_BIT_1F     0x20     
//buf3
#define  LED_BIT_1D     0x01
#define  LED_BIT_3A     0x02
#define  LED_BIT_4C     0x04
#define  LED_BIT_3G     0x10
//buf4
#define  LED_BIT_1E     0x01
#define  LED_BIT_3B     0x02
#define  LED_BIT_4D     0x04
#define  LED_BIT_2D     0x08
//buf5
#define  LED_BIT_1G     0x01    
#define  LED_BIT_3C     0x02  
#define  LED_BIT_4F     0x04  
#define  LED_BIT_2E     0x08    
#define  LED_BIT_4A     0x10 

//SEG1-6口高低控制
#define  SEG1_LOW()     SEG1_GPIO_CofigOutput(0);
#define  SEG1_HIGHT()   SEG1_GPIO_CofigOutput(1);
#define  SEG2_LOW()     SEG2_GPIO_CofigOutput(0);
#define  SEG2_HIGHT()   SEG2_GPIO_CofigOutput(1);
#define  SEG3_LOW()     SEG3_GPIO_CofigOutput(0);
#define  SEG3_HIGHT()   SEG3_GPIO_CofigOutput(1);
#define  SEG4_LOW()     SEG4_GPIO_CofigOutput(0);
#define  SEG4_HIGHT()   SEG4_GPIO_CofigOutput(1);
#define  SEG5_LOW()     SEG5_GPIO_CofigOutput(0);
#define  SEG5_HIGHT()   SEG5_GPIO_CofigOutput(1);
#define  SEG6_LOW()     SEG6_GPIO_CofigOutput(0);
#define  SEG6_HIGHT()   SEG6_GPIO_CofigOutput(1);


extern const uint8_t Number1[10][6];
extern const uint8_t Number2[10][6];
extern const uint8_t Number3[10][6];
extern const uint8_t Number4[10][6];


#endif /*__NIXITE_TUBE_DRIVER_H*/
