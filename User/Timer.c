#include "Timer.h"
#include "NixiteTube.h"
#include "BspDriver_Usart.h"
#include "KeyFunc.h"
#include "LEDFunc.h"
#include "Led.h"
/*�Զ����û���ʱ�ṹ��*/
TimerTypeDef Timer;

extern void ledseg_update_dispbuf(void);

//uint32_t Hp_test=0;

//uint32_t count=0;
/**
  * @brief  �û�����1msִ��һ��
  * @param  ��
  * @retval ��
  */
void UserTimer1ms(void)
{
	if(Timer.Bit1ms)
	{
		Timer.Bit1ms = 0;
		LED_Scan(NixieTube.DisplayBuf);
		MIC_Check();
	}
}

/**
  * @brief  �û�����5msִ��һ��
  * @param  ��
  * @retval ��
  */
void UserTimer5ms(void)
{
  if(Timer.Bit5ms)
  {
    Timer.Bit5ms = 0;
    KeyScan(Key.State);
    KeyFunc(Key.KeyUserVlaue);
    LED_FunctionTimer();
		LedDriver();
  }
}

/**
  * @brief  �û�����100msִ��һ��
  * @param  ��
  * @retval ��
  */
void UserTimer100ms(void)
{
  if(Timer.Bit100ms)
  {
    Timer.Bit100ms = 0;
    NixieTubeDisplay();
//    Hp_test++;
  }
}

/**
  * @brief  �û�����1sִ��һ��
  * @param  ��
  * @retval ��
  */
void UserTimer1s(void)
{
  if(Timer.Bit1s)
  {
    Timer.Bit1s = 0;
		
    // dmx outtime
		
  }
}


