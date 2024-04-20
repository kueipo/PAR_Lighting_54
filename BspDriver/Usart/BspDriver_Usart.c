#include "BspDriver_Usart.h"
extern void Error_Handler(void);

//����UART1�ṹ��
UART_HandleTypeDef UartHandle_Uart1;

/**
  * @brief  USART���ú���
  * @param  ��
  * @retval ��
  */
void APP_USART1Config(void)
{
  //����UART1��������ڽṹ��
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  //��GPIOFʱ��
  __HAL_RCC_GPIOF_CLK_ENABLE();
  /* ��USART1ʱ�� */
  __HAL_RCC_USART1_CLK_ENABLE();

  
  //����UART1��������ڳ�ʼ��PF0 RX,PF1 TX
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
  
  //����UART1��ʼ��
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
  __HAL_UART_ENABLE_IT(&UartHandle_Uart1, UART_IT_RXNE);//�жϽ���ʹ��
}

