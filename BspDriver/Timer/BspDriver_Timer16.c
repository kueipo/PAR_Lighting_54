#include "BspDriver_Timer16.h"

TIM_HandleTypeDef TimHandle_tim16;
extern void Error_Handler(void);
  

  
/**
  * @brief  ��ʱ��16����
  * @param  ��
  * @retval ��
  */
void APP_TIM16Config(void)
{
	/* ��ʱ������ */
  __HAL_RCC_TIM16_CLK_ENABLE();                                              /* ��TIM16ʱ�� */          
  TimHandle_tim16.Instance = TIM16;                                          /* ѡ��TIM16 */
  TimHandle_tim16.Init.Period            = 24 - 1;                           /* �Զ���װ��ֵ */
  TimHandle_tim16.Init.Prescaler         = 1000 - 1;                         /* Ԥ��ƵΪ1000-1 */
  TimHandle_tim16.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* ʱ�Ӳ���Ƶ */
  TimHandle_tim16.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* ���ϼ��� */
  TimHandle_tim16.Init.RepetitionCounter = 1 - 1;                            /* ���ظ����� */
  TimHandle_tim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* �Զ���װ�ؼĴ���û�л��� */
  if (HAL_TIM_Base_Init(&TimHandle_tim16) != HAL_OK)                         /* TIM16��ʼ�� */
  {
    Error_Handler();
  }

  if (HAL_TIM_Base_Start_IT(&TimHandle_tim16) != HAL_OK)                     /* TIM16ʹ����������ʹ���ж�*/
  {
    Error_Handler();
  }
}

