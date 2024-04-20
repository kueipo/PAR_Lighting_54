#include "BspDriver_ADC.h"
extern void Error_Handler(void);

unsigned int adc_value[9];

//定义ADC结构体
ADC_HandleTypeDef hadc;
ADC_ChannelConfTypeDef sConfig;
ADC_AnalogWDGConfTypeDef      ADCAnalogWDGConfig;

/**
  * @brief  ADC配置函数
  * @param  无
  * @retval 无
  */
void APP_ADCConfig(void)
{
  /*ADC1 GPIO配置*/
  GPIO_InitTypeDef GPIO_InitStruct = {0};                                   /*定义GPIO结构体*/
  __HAL_RCC_GPIOA_CLK_ENABLE();                                             /*打开ADC1 GPIO时钟 */
  
  GPIO_InitStruct.Pin = (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2|GPIO_PIN_3 |
                        GPIO_PIN_4 | GPIO_PIN_5| GPIO_PIN_6 | GPIO_PIN_7);
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;                                  /* 浮空输入 */
  GPIO_InitStruct.Pull = GPIO_NOPULL;                                       /* 不使能上拉 */
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);                                   /* GPIO初始化 */
  
  /*ADC1配置*/
  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();
  __HAL_RCC_ADC_CLK_ENABLE();                                                /* 使能ADC时钟 */

  hadc.Instance = ADC1;
  if (HAL_ADCEx_Calibration_Start(&hadc) != HAL_OK)                          /* ADC校准 */
  {
    Error_Handler();
  }

  hadc.Instance                   = ADC1;                                    /* ADC*/
  hadc.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV32;               /* 模拟ADC时钟源为PCLK*/
  hadc.Init.Resolution            = ADC_RESOLUTION_12B;                      /* 转换分辨率12bit*/
  hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;                     /* 数据右对齐 */
  hadc.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;              /* 扫描序列方向：向上(从通道0到通道11)*/
  hadc.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;                     /* ADC_EOC_SINGLE_CONV:单次采样 ; ADC_EOC_SEQ_CONV:序列采样*/
  hadc.Init.LowPowerAutoWait      = ENABLE;                                  /* ENABLE=读取ADC值后,开始下一次转换 ; DISABLE=直接转换 */
  hadc.Init.ContinuousConvMode    = DISABLE;                                 /* 单次转换模式 */
  hadc.Init.DiscontinuousConvMode = DISABLE;                                 /* 不使能非连续模式 */
  hadc.Init.ExternalTrigConv      = ADC_SOFTWARE_START;                      /* 软件触发 */
  hadc.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;           /* 触发边沿无 */
  hadc.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;                /* ADC_OVR_DATA_OVERWRITTEN=过载时覆盖,ADC_OVR_DATA_PRESERVED=保留旧值*/
  hadc.Init.SamplingTimeCommon    = ADC_SAMPLETIME_41CYCLES_5;               /* 通道采样时间为41.5ADC时钟周期 */
  if (HAL_ADC_Init(&hadc) != HAL_OK)                                         /* ADC初始化*/
  {
    Error_Handler();
  }
  
  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                            /*设置是否排行, 想设置单通道采样,需配置ADC_RANK_NONE */
  sConfig.Channel      = ADC_CHANNEL_0;                                      /* 设置采样通道 */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                      /*  配置ADC通道 */
  {
    Error_Handler();
  }
  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                            /*设置是否排行, 想设置单通道采样,需配置ADC_RANK_NONE */
  sConfig.Channel      = ADC_CHANNEL_1;                                      /* 设置采样通道 */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                      /*  配置ADC通道 */
  {
    Error_Handler();
  }

  sConfig.Rank		  = ADC_RANK_CHANNEL_NUMBER;							                 /*设置是否排行, 想设置单通道采样,需配置ADC_RANK_NONE */
  sConfig.Channel	  = ADC_CHANNEL_2;									                     	 /* 设置采样通道 */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)						           /*	配置ADC通道 */
  {
    Error_Handler();
  }
  sConfig.Rank		  = ADC_RANK_CHANNEL_NUMBER;							                 /*设置是否排行, 想设置单通道采样,需配置ADC_RANK_NONE */
  sConfig.Channel	  = ADC_CHANNEL_3;									                     	 /* 设置采样通道 */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)						           /*	配置ADC通道 */
  {
    Error_Handler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                            /*设置是否排行, 想设置单通道采样,需配置ADC_RANK_NONE */
  sConfig.Channel      = ADC_CHANNEL_4;                                      /* 设置采样通道 */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                      /*  配置ADC通道 */
  {
    Error_Handler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                            /*设置是否排行, 想设置单通道采样,需配置ADC_RANK_NONE */
  sConfig.Channel      = ADC_CHANNEL_5;                                      /* 设置采样通道 */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                      /*  配置ADC通道 */
  {
    Error_Handler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                            /*设置是否排行, 想设置单通道采样,需配置ADC_RANK_NONE */
  sConfig.Channel      = ADC_CHANNEL_6;                                      /* 设置采样通道 */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                      /*  配置ADC通道 */
  {
    Error_Handler();
  }
  
  sConfig.Rank		   = ADC_RANK_CHANNEL_NUMBER;							                 /*设置是否排行, 想设置单通道采样,需配置ADC_RANK_NONE */
  sConfig.Channel	   = ADC_CHANNEL_7; 									                     /* 设置采样通道 */
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) 					           /*  配置ADC通道 */
  {
    Error_Handler();
  }
}

/**
  * @brief  ADC配置函数
  * @param  无
  * @retval 无
  */
void ADC_ValGet(void)
{
  uint8_t i;
  HAL_ADC_Start(&hadc);                          /* ADC开启*/
  for (i = 0; i < 8; i++)                        /* 获取ADC1 0-7通道的ADC值*/
  {
    HAL_ADC_PollForConversion(&hadc, 1000);      /* 等待ADC转换 */
    adc_value[i] = HAL_ADC_GetValue(&hadc);      /* 获取AD值  */
  }
}

