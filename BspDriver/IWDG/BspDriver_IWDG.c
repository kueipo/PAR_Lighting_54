#include "BspDriver_IWDG.h"
extern void Error_Handler(void);

IWDG_HandleTypeDef   IwdgHandle;

/**
  * @brief  �������Ź�����
  * @param  ��
  * @retval ��
  */
void APP_IWDG_Config(void)
{
  /* ʹ��LSIʱ�� */
  __HAL_RCC_LSI_ENABLE();
  /* �ȴ�ֱ��LSI READY��λ */
  while (READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) == 0U);
  
  IwdgHandle.Instance = IWDG;                                /* ѡ��IWDG */
  IwdgHandle.Init.Prescaler = IWDG_PRESCALER_32;             /* ����32��Ƶ */
  IwdgHandle.Init.Reload = (1000);                           /* IWDG��������װ��ֵΪ1000��1s */
  /* ��ʼ��IWDG */
  if (HAL_IWDG_Init(&IwdgHandle) != HAL_OK)                  
  {
    Error_Handler();
  }
}

/**
  * @brief  �������Ź�ι��
  * @param  ��
  * @retval ��
  */
void IWDG_FeedDogs(void)
{
  if (HAL_IWDG_Refresh(&IwdgHandle) != HAL_OK)  
  {
    Error_Handler();
  }
}
