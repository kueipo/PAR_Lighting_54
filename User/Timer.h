#ifndef _TIMER_H
#define _TIMER_H
#include "py32f0xx_hal.h"

/*自定义用户定时结构体*/
typedef struct
{
	uint8_t Bit1ms;                 //1毫秒标志位
	uint8_t Bit5ms;                 //5毫秒标志位
	uint8_t Bit10ms;                //10毫秒标志位
	uint8_t Bit100ms;               //100毫秒标志位
	uint8_t Bit1s;                  //1秒标志位
	uint16_t Count5ms;              //10毫秒计数
	uint16_t Count10ms;             //10毫秒计数
	uint16_t Count100ms;            //100毫秒计数
	uint16_t Count1s;               //1秒计数
	uint16_t CountMin;	
}TimerTypeDef;

extern TimerTypeDef Timer;

extern void UserTimer1ms(void);
extern void UserTimer5ms(void);
extern void UserTimer100ms(void);
extern void UserTimer1s(void);


#endif /*_TIMER_H*/

