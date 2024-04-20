#ifndef _TIMER_H
#define _TIMER_H
#include "py32f0xx_hal.h"

/*�Զ����û���ʱ�ṹ��*/
typedef struct
{
	uint8_t Bit1ms;                 //1�����־λ
	uint8_t Bit5ms;                 //5�����־λ
	uint8_t Bit10ms;                //10�����־λ
	uint8_t Bit100ms;               //100�����־λ
	uint8_t Bit1s;                  //1���־λ
	uint16_t Count5ms;              //10�������
	uint16_t Count10ms;             //10�������
	uint16_t Count100ms;            //100�������
	uint16_t Count1s;               //1�����
	uint16_t CountMin;	
}TimerTypeDef;

extern TimerTypeDef Timer;

extern void UserTimer1ms(void);
extern void UserTimer5ms(void);
extern void UserTimer100ms(void);
extern void UserTimer1s(void);


#endif /*_TIMER_H*/

