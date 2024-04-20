#include "BspDriver_IWDG.h"
extern void Error_Handler(void);

IWDG_HandleTypeDef   IwdgHandle;

/**
  * @brief  独立看门狗配置
  * @param  无
  * @retval 无
  */
void APP_IWDG_Config(void)
{
  /* 使能LSI时钟 */
  __HAL_RCC_LSI_ENABLE();
  /* 等待直到LSI READY置位 */
  while (READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) == 0U);
  
  IwdgHandle.Instance = IWDG;                                /* 选择IWDG */
  IwdgHandle.Init.Prescaler = IWDG_PRESCALER_32;             /* 配置32分频 */
  IwdgHandle.Init.Reload = (1000);                           /* IWDG计数器重装载值为1000，1s */
  /* 初始化IWDG */
  if (HAL_IWDG_Init(&IwdgHandle) != HAL_OK)                  
  {
    Error_Handler();
  }
}

/**
  * @brief  独立看门狗喂狗
  * @param  无
  * @retval 无
  */
void IWDG_FeedDogs(void)
{
  if (HAL_IWDG_Refresh(&IwdgHandle) != HAL_OK)  
  {
    Error_Handler();
  }
}

