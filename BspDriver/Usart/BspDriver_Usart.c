#include "BspDriver_Usart.h"
extern void Error_Handler(void);

//定义UART1结构体
UART_HandleTypeDef UartHandle_Uart1;

/**
  * @brief  USART配置函数
  * @param  无
  * @retval 无
  */
void APP_USART1Config(void)
{
  //定义UART1输入输出口结构体
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  //打开GPIOF时钟
  __HAL_RCC_GPIOF_CLK_ENABLE();
  /* 打开USART1时钟 */
  __HAL_RCC_USART1_CLK_ENABLE();

  
  //配置UART1输入输出口初始化PF0 RX,PF1 TX
  GPIO_InitStruct.Pin       = GPIO_PIN_1;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF8_USART1;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
  GPIO_InitStruct.Pin 			= GPIO_PIN_0;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF8_USART1;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
  
  //配置UART1初始化
  UartHandle_Uart1.Instance          = USART1;
  UartHandle_Uart1.Init.BaudRate     = 250000;
  UartHandle_Uart1.Init.WordLength   = UART_WORDLENGTH_9B;
  UartHandle_Uart1.Init.StopBits     = UART_STOPBITS_1;
  UartHandle_Uart1.Init.Parity       = UART_PARITY_NONE;
  UartHandle_Uart1.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle_Uart1.Init.Mode         = UART_MODE_TX_RX;
  if (HAL_UART_DeInit(&UartHandle_Uart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UART_Init(&UartHandle_Uart1) != HAL_OK)
  {
    Error_Handler();
  }
  __HAL_UART_ENABLE_IT(&UartHandle_Uart1, UART_IT_RXNE);//中断接收使能
}

