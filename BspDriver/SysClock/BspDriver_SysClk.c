#include "BspDriver_SysClk.h"


/**
  * @brief  ����ִ�к���
  * @param  ��
  * @retval ��
  */
void Error_Handler(void)
{
  /* ����ѭ�� */
  while (1)
  {
  }
}

/**
  * @brief  ϵͳʱ�����ú���
  * @param  ��
  * @retval ��
  */
void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* �������� */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI; /* ѡ������HSE,HSI,LSI */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                          /* ����HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                          /* HSI 1��Ƶ */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_24MHz; /* ����HSIʱ��24MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                         /* �ر�HSE */
  /*RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz;*/
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                         /* �ر�LSI */

  /* �������� */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* ʱ��Դ���� */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* ѡ������ʱ�� HCLK,SYSCLK,PCLK1 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;         /* ѡ��HSI��Ϊϵͳʱ�� */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;             /* AHBʱ�� 1��Ƶ */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;              /* APBʱ�� 1��Ƶ */
  /* ����ʱ��Դ */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

