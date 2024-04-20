#include "BspDriver_Timer1.h"

extern void Error_Handler(void);

#define  PULSE1_VALUE       10
#define  PULSE2_VALUE       10
#define  PULSE3_VALUE       100
#define  PULSE4_VALUE       255

//TIM1 PWM����ڶ���
#define TIMx_GPIO_PORT_CHANNEL1        GPIOA
#define TIMx_GPIO_PORT_CHANNEL2        GPIOB
#define TIMx_GPIO_PORT_CHANNEL3        GPIOA
#define TIMx_GPIO_PORT_CHANNEL4        GPIOA
#define TIMx_GPIO_PIN_CHANNEL1         GPIO_PIN_3
#define TIMx_GPIO_PIN_CHANNEL2         GPIO_PIN_3
#define TIMx_GPIO_PIN_CHANNEL3         GPIO_PIN_0
#define TIMx_GPIO_PIN_CHANNEL4         GPIO_PIN_1

/*TIM1ʱ���ṹ�嶨��*/
TIM_HandleTypeDef    TimHandle_Tim1;
/*����TIM1 PWM���ýṹ��*/
TIM_OC_InitTypeDef sConfig_Tim1;

/**
  * @brief  TIM1 PWM����ڳ�ʼ��
  * @param  ��
  * @retval ��
  */
static void APP_TIM1_GPIO(void)
{
  //����GPIO��ʼ���ṹ��
  GPIO_InitTypeDef   GPIO_InitStruct;                            
  /*GPIOAʱ��ʹ�� */
  __HAL_RCC_GPIOA_CLK_ENABLE();                             
  /*GPIOAʱ��ʹ�� */
  __HAL_RCC_GPIOB_CLK_ENABLE();                             
 /*���ù��� */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                   
  /* ���� */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                       
  /* ����*/
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  /*GPIOA3��ʼ��*/
  GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL1;
  GPIO_InitStruct.Alternate = GPIO_AF13_TIM1;
  HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL1, &GPIO_InitStruct);
  /*GPIOB3��ʼ��*/
  GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL2;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
  HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL2, &GPIO_InitStruct);
  /*GPIOA0��ʼ��*/
  GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL3;
  GPIO_InitStruct.Alternate = GPIO_AF13_TIM1;
  HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL3, &GPIO_InitStruct);
  /*GPIOA1��ʼ��*/
  GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL4;
  GPIO_InitStruct.Alternate = GPIO_AF13_TIM1;
  HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL4, &GPIO_InitStruct);  
}


/**
  * @brief  TIM1��ʼ������
  * @param  ��
  * @retval ��
  */
static void APP_TIM1_INIT(void)
{
  /* ѡ��TIM1 */
  TimHandle_Tim1.Instance = TIM1;    
  /*TIM1ʱ��ʹ�� */
  __HAL_RCC_TIM1_CLK_ENABLE();  
  /* �Զ���װ��ֵ */
  TimHandle_Tim1.Init.Period            = 2000;                                     
  /* Ԥ��ƵΪ24-1 */
  TimHandle_Tim1.Init.Prescaler         = 1;      //24-1                             
  /* ʱ�Ӳ���Ƶ */
  TimHandle_Tim1.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                  
  /* ���ϼ���*/
  TimHandle_Tim1.Init.CounterMode       = TIM_COUNTERMODE_UP;                      
  /* ���ظ����� */
  TimHandle_Tim1.Init.RepetitionCounter = 1 - 1;                                   
  /* �Զ���װ�ؼĴ���û�л��� */
  TimHandle_Tim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;          
  /* ����ʱ�ӳ�ʼ�� */
  if (HAL_TIM_Base_Init(&TimHandle_Tim1) != HAL_OK)                                
  {
    Error_Handler();
  }
//  HAL_NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 0, 0);   /* ??????? */
//  HAL_NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);           /* ??TIM1?? */
}

/**
  * @brief  TIM1 PWM����
  * @param  ��
  * @retval ��
  */
static void APP_TIM1_PWM(void)
{
  /*�������Ϊ��תģʽ */
  sConfig_Tim1.OCMode       = TIM_OCMODE_PWM1;                                     
  /*OCͨ������ߵ�ƽ��Ч */
  sConfig_Tim1.OCPolarity   = TIM_OCPOLARITY_HIGH;                                 
  /*�������ʹ�ܹر� */
  sConfig_Tim1.OCFastMode   = TIM_OCFAST_DISABLE;                                  
  /*OCNͨ������ߵ�ƽ��Ч */
  sConfig_Tim1.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                
  /*����״̬OC1N����͵�ƽ */
  sConfig_Tim1.OCNIdleState = TIM_OCNIDLESTATE_RESET;                              
  /*����״̬OC1����͵�ƽ*/
  sConfig_Tim1.OCIdleState  = TIM_OCIDLESTATE_RESET;  
  /*PWMͨ��1ռ�ձ�����Ϊ0��ʹ��*/
  Tim1PwmDutySetChan1(0);
  /*PWMͨ��2ռ�ձ�����Ϊ0��ʹ��*/
  Tim1PwmDutySetChan2(0);
  /*PWMͨ��3ռ�ձ�����Ϊ0��ʹ��*/
  Tim1PwmDutySetChan3(0);
  /*PWMͨ��4ռ�ձ�����Ϊ0��ʹ��*/
  Tim1PwmDutySetChan4(0);
  if (HAL_TIM_Base_Start_IT(&TimHandle_Tim1) != HAL_OK)                     /* TIM1????,????? */
  {
    /* Starting Error */
    Error_Handler();
  }
}

/**
  * @brief  TIM1 PWM���ú���
  * @param  ��
  * @retval ��
  */
void APP_TIM1_PWM_Config(void)
{
  APP_TIM1_GPIO();
  APP_TIM1_INIT();
  APP_TIM1_PWM();
}

/**
  * @brief  TIM1 PWMͨ��1ռ�ձ�����
  * @param  ��
  * @retval ��
  */
void Tim1PwmDutySetChan1(uint16_t duty)
{
  /*CC1ֵΪduty��ռ�ձ�=duty/255*/
  sConfig_Tim1.Pulse = duty;
  /* ͨ��1���� */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle_Tim1, &sConfig_Tim1, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* ͨ��1��ʼ���PWM */
  if (HAL_TIM_PWM_Start(&TimHandle_Tim1, TIM_CHANNEL_1) != HAL_OK)                  
  {
    Error_Handler();
  }    
}

/**
  * @brief  TIM1 PWMͨ��2ռ�ձ�����
  * @param  ��
  * @retval ��
  */
void Tim1PwmDutySetChan2(uint16_t duty)
{
  /*CC2ֵΪduty��ռ�ձ�=duty/255*/
  sConfig_Tim1.Pulse = duty;
  /* ͨ��2���� */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle_Tim1, &sConfig_Tim1, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* ͨ��1��ʼ���PWM */
  if (HAL_TIM_PWM_Start(&TimHandle_Tim1, TIM_CHANNEL_2) != HAL_OK)                  
  {
    Error_Handler();
  }    
}

/**
  * @brief  TIM1 PWMͨ��3ռ�ձ�����
  * @param  ��
  * @retval ��
  */
void Tim1PwmDutySetChan3(uint16_t duty)
{
  /*CC3ֵΪduty��ռ�ձ�=duty/255*/
  sConfig_Tim1.Pulse = duty;
  /* ͨ��3���� */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle_Tim1, &sConfig_Tim1, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* ͨ��1��ʼ���PWM */
  if (HAL_TIM_PWM_Start(&TimHandle_Tim1, TIM_CHANNEL_3) != HAL_OK)                  
  {
    Error_Handler();
  }    
}

/**
  * @brief  TIM1 PWMͨ��4ռ�ձ�����
  * @param  ��
  * @retval ��
  */
void Tim1PwmDutySetChan4(uint16_t duty)
{
  /*CC3ֵΪduty��ռ�ձ�=duty/255*/
  sConfig_Tim1.Pulse = duty;
  /* ͨ��3���� */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle_Tim1, &sConfig_Tim1, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* ͨ��1��ʼ���PWM */
  if (HAL_TIM_PWM_Start(&TimHandle_Tim1, TIM_CHANNEL_3) != HAL_OK)                  
  {
    Error_Handler();
  }    
}



