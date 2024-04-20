#include "BspDriver_ADC.h"
extern void Error_Handler(void);

unsigned int adc_value[9];

//����ADC�ṹ��
ADC_HandleTypeDef hadc;
ADC_ChannelConfTypeDef sConfig;
ADC_AnalogWDGConfTypeDef      ADCAnalogWDGConfig;

/**
  * @brief  ADC���ú���
  * @param  ��
  * @retval ��
  */
void APP_ADCConfig(void)
{
  /*ADC1 GPIO����*/
  GPIO_InitTypeDef GPIO_InitStruct = {0};                                   /*����GPIO�ṹ��*/
  __HAL_RCC_GPIOA_CLK_ENABLE();                                             /*��ADC1 GPIOʱ�� */
  
  GPIO_InitStruct.Pin = (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2|GPIO_PIN_3 |
                        GPIO_PIN_4 | GPIO_PIN_5| GPIO_PIN_6 | GPIO_PIN_7);
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;                                  /* �������� */
  GPIO_InitStruct.Pull = GPIO_NOPULL;                                       /* ��ʹ������ */
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);                                   /* GPIO��ʼ�� */
  
  /*ADC1����*/
  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();
  __HAL_RCC_ADC_CLK_ENABLE();                                                /* ʹ��ADCʱ�� */

  hadc.Instance = ADC1;
  if (HAL_ADCEx_Calibration_Start(&hadc) != HAL_OK)                          /* ADCУ׼ */
  {
    Error_Handler();
  }

  hadc.Instance                   = ADC1;                                    /* ADC*/
  hadc.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV32;               /* ģ��ADCʱ��ԴΪPCLK*/
  hadc.Init.Resolution            = ADC_RESOLUTION_12B;                      /* ת���ֱ���12bit*/
  hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;                     /* �����Ҷ��� */
  hadc.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;              /* ɨ�����з�������(��ͨ��0��ͨ��11)*/
  hadc.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;                     /* ADC_EOC_SINGLE_CONV:���β��� ; ADC_EOC_SEQ_CONV:���в���*/
  hadc.Init.LowPowerAutoWait      = ENABLE;                                  /* ENABLE=��ȡADCֵ��,��ʼ��һ��ת�� ; DISABLE=ֱ��ת�� */
  hadc.Init.ContinuousConvMode    = DISABLE;                                 /* ����ת��ģʽ */
  hadc.Init.DiscontinuousConvMode = DISABLE;                                 /* ��ʹ�ܷ�����ģʽ */
  hadc.Init.ExternalTrigConv      = ADC_SOFTWARE_START;                      /* ������� */
  hadc.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;           /* ���������� */
  hadc.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;                /* ADC_OVR_DATA_OVERWRITTEN=����ʱ����,ADC_OVR_DATA_PRESERVED=������ֵ*/
  hadc.Init.SamplingTimeCommon    = ADC_SAMPLETIME_41CYCLES_5;               /* ͨ������ʱ��Ϊ41.5ADCʱ������ */
  if (HAL_ADC_Init(&hadc) != HAL_OK)                                         /* ADC��ʼ��*/
  {
    Error_Handler();
  }
  
  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                            /*�����Ƿ�����, �����õ�ͨ������,������ADC_RANK_NONE */
  sConfig.Channel      = ADC_CHANNEL_0;                                      /* ���ò���ͨ�� */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                      /*  ����ADCͨ�� */
  {
    Error_Handler();
  }
  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                            /*�����Ƿ�����, �����õ�ͨ������,������ADC_RANK_NONE */
  sConfig.Channel      = ADC_CHANNEL_1;                                      /* ���ò���ͨ�� */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                      /*  ����ADCͨ�� */
  {
    Error_Handler();
  }

  sConfig.Rank		  = ADC_RANK_CHANNEL_NUMBER;							                 /*�����Ƿ�����, �����õ�ͨ������,������ADC_RANK_NONE */
  sConfig.Channel	  = ADC_CHANNEL_2;									                     	 /* ���ò���ͨ�� */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)						           /*	����ADCͨ�� */
  {
    Error_Handler();
  }
  sConfig.Rank		  = ADC_RANK_CHANNEL_NUMBER;							                 /*�����Ƿ�����, �����õ�ͨ������,������ADC_RANK_NONE */
  sConfig.Channel	  = ADC_CHANNEL_3;									                     	 /* ���ò���ͨ�� */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)						           /*	����ADCͨ�� */
  {
    Error_Handler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                            /*�����Ƿ�����, �����õ�ͨ������,������ADC_RANK_NONE */
  sConfig.Channel      = ADC_CHANNEL_4;                                      /* ���ò���ͨ�� */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                      /*  ����ADCͨ�� */
  {
    Error_Handler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                            /*�����Ƿ�����, �����õ�ͨ������,������ADC_RANK_NONE */
  sConfig.Channel      = ADC_CHANNEL_5;                                      /* ���ò���ͨ�� */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                      /*  ����ADCͨ�� */
  {
    Error_Handler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                            /*�����Ƿ�����, �����õ�ͨ������,������ADC_RANK_NONE */
  sConfig.Channel      = ADC_CHANNEL_6;                                      /* ���ò���ͨ�� */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                      /*  ����ADCͨ�� */
  {
    Error_Handler();
  }
  
  sConfig.Rank		   = ADC_RANK_CHANNEL_NUMBER;							                 /*�����Ƿ�����, �����õ�ͨ������,������ADC_RANK_NONE */
  sConfig.Channel	   = ADC_CHANNEL_7; 									                     /* ���ò���ͨ�� */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) 					           /*  ����ADCͨ�� */
  {
    Error_Handler();
  }
}

/**
  * @brief  ADC���ú���
  * @param  ��
  * @retval ��
  */
void ADC_ValGet(void)
{
  uint8_t i;
  HAL_ADC_Start(&hadc);                          /* ADC����*/
  for (i = 0; i < 8; i++)                        /* ��ȡADC1 0-7ͨ����ADCֵ*/
  {
    HAL_ADC_PollForConversion(&hadc, 1000);      /* �ȴ�ADCת�� */
    adc_value[i] = HAL_ADC_GetValue(&hadc);      /* ��ȡADֵ  */
  }
}

