#include "Timer.h"
#include "NixiteTube.h"
#include "BspDriver_Usart.h"
#include "KeyFunc.h"
#include "LEDFunc.h"
#include "Led.h"
/*自定义用户定时结构体*/
TimerTypeDef Timer;

extern void ledseg_update_dispbuf(void);

//uint32_t Hp_test=0;

//uint32_t count=0;
/**
  * @brief  用户程序1ms执行一次
  * @param  无
  * @retval 无
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
  * @brief  用户程序5ms执行一次
  * @param  无
  * @retval 无
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
  * @brief  用户程序100ms执行一次
  * @param  无
  * @retval 无
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
  * @brief  用户程序1s执行一次
  * @param  无
  * @retval 无
  */
void UserTimer1s(void)
{
  if(Timer.Bit1s)
  {
    Timer.Bit1s = 0;
		
    // dmx outtime
		
  }
}



