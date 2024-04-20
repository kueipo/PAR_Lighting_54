/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "BspDriver_Timer16.h"
#include "BspDriver_GPIO.h"
#include "NixiteTube.h"
#include "NixiteTube_Driver.h"
#include "BspDriver_Usart.h"
#include "BspDriver_SysClk.h"
#include "BspDriver_Timer1.h"
#include "BspDriver_IWDG.h"
#include "Timer.h"
#include "LEDFunc.h"
#include "KeyFunc.h"
#include "EEPROM.h"
#include "Led.h"
#include <string.h>
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
unsigned short wdebugVlue;

/**
  * @brief  应用程序入口函数.
  * @retval int
  */

int main(void)
{
	/* 初始化所有外设，Flash接口，SysTick */
	HAL_Init();
	/* 系统时钟配置 */
	APP_SystemClockConfig();  
	HAL_Delay(500);            /* 延时500ms,重要!因为将SWD口作为了普通口,不延时下次会下载不进程序 */
	/* GPIO配置 */
	APP_GPIOConfig();
	/* 定时器配置 */
	APP_TIM16Config();
	/* UART1配置 */
	APP_USART1Config();
	/* PWM配置 */
	APP_TIM1_PWM_Config();

	LedPwmDutySetRed(100);
	LedPwmDutySetGreen(100);
	LedPwmDutySetBlue(100);
	/*用户数据初始化*/
	memset(&Timer,0,sizeof(Timer));
	memset(&LED,0,sizeof(LED));
	memset(&Key,0,sizeof(Key));
	memset(&NixieTube,0,sizeof(NixieTube));
	UserSetInit();
  
	/* IWDG配置 */
	//  APP_IWDG_Config();
  
	while(1)
	{
//		IWDG_FeedDogs();
		UserTimer1ms();//扫描显示
		UserTimer5ms();
		UserTimer100ms();//刷新显示
		LED_FunctionMode();
	}

	return 0;
}










/************************ (C) COPYRIGHT Puya *****END OF FILE****/


