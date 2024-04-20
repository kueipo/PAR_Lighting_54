#include "BspDriver_Timer16.h"

TIM_HandleTypeDef TimHandle_tim16;
extern void Error_Handler(void);
  

  
/**
  * @brief  定时器16配置
  * @param  无
  * @retval 无
  */
void APP_TIM16Config(void)
{
	/* 定时器配置 */
  __HAL_RCC_TIM16_CLK_ENABLE();                                              /* 打开TIM16时钟 */          
  TimHandle_tim16.Instance = TIM16;                                          /* 选择TIM16 */
  TimHandle_tim16.Init.Period            = 24 - 1;                           /* 自动重装载值 */
  TimHandle_tim16.Init.Prescaler         = 1000 - 1;                         /* 预分频为1000-1 */
  TimHandle_tim16.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* 时钟不分频 */
  TimHandle_tim16.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* 向上计数 */
  TimHandle_tim16.Init.RepetitionCounter = 1 - 1;                            /* 不重复计数 */
  TimHandle_tim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* 自动重装载寄存器没有缓冲 */
  if (HAL_TIM_Base_Init(&TimHandle_tim16) != HAL_OK)                         /* TIM16初始化 */
  {
    Error_Handler();
  }

  if (HAL_TIM_Base_Start_IT(&TimHandle_tim16) != HAL_OK)                     /* TIM16使能启动，并使能中断*/
  {
    Error_Handler();
  }
}

