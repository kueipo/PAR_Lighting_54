#include "BspDriver_Timer1.h"

extern void Error_Handler(void);

#define  PULSE1_VALUE       10
#define  PULSE2_VALUE       10
#define  PULSE3_VALUE       100
#define  PULSE4_VALUE       255

//TIM1 PWM输出口定义
#define TIMx_GPIO_PORT_CHANNEL1        GPIOA
#define TIMx_GPIO_PORT_CHANNEL2        GPIOB
#define TIMx_GPIO_PORT_CHANNEL3        GPIOA
#define TIMx_GPIO_PORT_CHANNEL4        GPIOA
#define TIMx_GPIO_PIN_CHANNEL1         GPIO_PIN_3
#define TIMx_GPIO_PIN_CHANNEL2         GPIO_PIN_3
#define TIMx_GPIO_PIN_CHANNEL3         GPIO_PIN_0
#define TIMx_GPIO_PIN_CHANNEL4         GPIO_PIN_1

/*TIM1时基结构体定义*/
TIM_HandleTypeDef    TimHandle_Tim1;
/*定义TIM1 PWM配置结构体*/
TIM_OC_InitTypeDef sConfig_Tim1;

/**
  * @brief  TIM1 PWM输出口初始化
  * @param  无
  * @retval 无
  */
static void APP_TIM1_GPIO(void)
{
  //定义GPIO初始化结构体
  GPIO_InitTypeDef   GPIO_InitStruct;                            
  /*GPIOA时钟使能 */
  __HAL_RCC_GPIOA_CLK_ENABLE();                             
  /*GPIOA时钟使能 */
  __HAL_RCC_GPIOB_CLK_ENABLE();                             
 /*复用功能 */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                   
  /* 上拉 */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                       
  /* 高速*/
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  /*GPIOA3初始化*/
  GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL1;
  GPIO_InitStruct.Alternate = GPIO_AF13_TIM1;
  HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL1, &GPIO_InitStruct);
  /*GPIOB3初始化*/
  GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL2;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
  HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL2, &GPIO_InitStruct);
  /*GPIOA0初始化*/
  GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL3;
  GPIO_InitStruct.Alternate = GPIO_AF13_TIM1;
  HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL3, &GPIO_InitStruct);
  /*GPIOA1初始化*/
  GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL4;
  GPIO_InitStruct.Alternate = GPIO_AF13_TIM1;
  HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL4, &GPIO_InitStruct);  
}


/**
  * @brief  TIM1初始化函数
  * @param  无
  * @retval 无
  */
static void APP_TIM1_INIT(void)
{
  /* 选择TIM1 */
  TimHandle_Tim1.Instance = TIM1;    
  /*TIM1时钟使能 */
  __HAL_RCC_TIM1_CLK_ENABLE();  
  /* 自动重装载值 */
  TimHandle_Tim1.Init.Period            = 2000;                                     
  /* 预分频为24-1 */
  TimHandle_Tim1.Init.Prescaler         = 1;      //24-1                             
  /* 时钟不分频 */
  TimHandle_Tim1.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                  
  /* 向上计数*/
  TimHandle_Tim1.Init.CounterMode       = TIM_COUNTERMODE_UP;                      
  /* 不重复计数 */
  TimHandle_Tim1.Init.RepetitionCounter = 1 - 1;                                   
  /* 自动重装载寄存器没有缓冲 */
  TimHandle_Tim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;          
  /* 基础时钟初始化 */
  if (HAL_TIM_Base_Init(&TimHandle_Tim1) != HAL_OK)                                
  {
    Error_Handler();
  }
//  HAL_NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 0, 0);   /* ??????? */
//  HAL_NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);           /* ??TIM1?? */
}

/**
  * @brief  TIM1 PWM配置
  * @param  无
  * @retval 无
  */
static void APP_TIM1_PWM(void)
{
  /*输出配置为翻转模式 */
  sConfig_Tim1.OCMode       = TIM_OCMODE_PWM1;                                     
  /*OC通道输出高电平有效 */
  sConfig_Tim1.OCPolarity   = TIM_OCPOLARITY_HIGH;                                 
  /*输出快速使能关闭 */
  sConfig_Tim1.OCFastMode   = TIM_OCFAST_DISABLE;                                  
  /*OCN通道输出高电平有效 */
  sConfig_Tim1.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                
  /*空闲状态OC1N输出低电平 */
  sConfig_Tim1.OCNIdleState = TIM_OCNIDLESTATE_RESET;                              
  /*空闲状态OC1输出低电平*/
  sConfig_Tim1.OCIdleState  = TIM_OCIDLESTATE_RESET;  
  /*PWM通道1占空比设置为0并使能*/
  Tim1PwmDutySetChan1(0);
  /*PWM通道2占空比设置为0并使能*/
  Tim1PwmDutySetChan2(0);
  /*PWM通道3占空比设置为0并使能*/
  Tim1PwmDutySetChan3(0);
  /*PWM通道4占空比设置为0并使能*/
  Tim1PwmDutySetChan4(0);
  if (HAL_TIM_Base_Start_IT(&TimHandle_Tim1) != HAL_OK)                     /* TIM1????,????? */
  {
    /* Starting Error */
    Error_Handler();
  }
}

/**
  * @brief  TIM1 PWM配置函数
  * @param  无
  * @retval 无
  */
void APP_TIM1_PWM_Config(void)
{
  APP_TIM1_GPIO();
  APP_TIM1_INIT();
  APP_TIM1_PWM();
}

/**
  * @brief  TIM1 PWM通道1占空比设置
  * @param  无
  * @retval 无
  */
void Tim1PwmDutySetChan1(uint16_t duty)
{
  /*CC1值为duty，占空比=duty/255*/
  sConfig_Tim1.Pulse = duty;
  /* 通道1配置 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle_Tim1, &sConfig_Tim1, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* 通道1开始输出PWM */
  if (HAL_TIM_PWM_Start(&TimHandle_Tim1, TIM_CHANNEL_1) != HAL_OK)                  
  {
    Error_Handler();
  }    
}

/**
  * @brief  TIM1 PWM通道2占空比设置
  * @param  无
  * @retval 无
  */
void Tim1PwmDutySetChan2(uint16_t duty)
{
  /*CC2值为duty，占空比=duty/255*/
  sConfig_Tim1.Pulse = duty;
  /* 通道2配置 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle_Tim1, &sConfig_Tim1, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* 通道1开始输出PWM */
  if (HAL_TIM_PWM_Start(&TimHandle_Tim1, TIM_CHANNEL_2) != HAL_OK)                  
  {
    Error_Handler();
  }    
}

/**
  * @brief  TIM1 PWM通道3占空比设置
  * @param  无
  * @retval 无
  */
void Tim1PwmDutySetChan3(uint16_t duty)
{
  /*CC3值为duty，占空比=duty/255*/
  sConfig_Tim1.Pulse = duty;
  /* 通道3配置 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle_Tim1, &sConfig_Tim1, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* 通道1开始输出PWM */
  if (HAL_TIM_PWM_Start(&TimHandle_Tim1, TIM_CHANNEL_3) != HAL_OK)                  
  {
    Error_Handler();
  }    
}

/**
  * @brief  TIM1 PWM通道4占空比设置
  * @param  无
  * @retval 无
  */
void Tim1PwmDutySetChan4(uint16_t duty)
{
  /*CC3值为duty，占空比=duty/255*/
  sConfig_Tim1.Pulse = duty;
  /* 通道3配置 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle_Tim1, &sConfig_Tim1, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* 通道1开始输出PWM */
  if (HAL_TIM_PWM_Start(&TimHandle_Tim1, TIM_CHANNEL_3) != HAL_OK)                  
  {
    Error_Handler();
  }    
}



