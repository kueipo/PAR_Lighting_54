/**
  ******************************************************************************
  * @file    py32f0xx_it.c
  * @author  MCU Application Team
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "py32f0xx_it.h"

/* Private includes ----------------------------------------------------------*/
extern TIM_HandleTypeDef    TimHandle;

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*          Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/* PY32F0xx Peripheral Interrupt Handlers                                     */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_py32f002xx.s).                   */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */

/*void PPP_IRQHandler(void)
{
}*/


/**
  * @brief TMI16
  */
#include "Timer.h"
extern TIM_HandleTypeDef TimHandle_tim16;
void TIM16_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle_tim16);
  Timer.Bit1ms = 1;
  if(++Timer.Count5ms >= 5)
  {
    Timer.Count5ms = 0;
    Timer.Bit5ms = 1;
  }

  if(++Timer.Count100ms >= 100)
  {
    Timer.Count100ms = 0;
    Timer.Bit100ms = 1;
    if(++Timer.Count1s >= 10)
    {
      Timer.Count1s = 0;
      Timer.Bit1s = 1;
    }
  }
}

/**
  * @brief Uart1
  */
extern UART_HandleTypeDef UartHandle_Uart1;
uint8_t cRxIndex1=0,cRxIndex2=0,LedFinishBit=0,RkFinishBit=0;
//extern uint8_t RxDisplayBuf[9];

#define CHANNEL_NUM  7//dmxʵ����Чͨ����

uint16_t Usart_Data;
uint8_t  USART_DR;
uint8_t  RB8;

uint8_t  END_FLG_RX = 0;//����ͨѶ֡��ɱ�־
uint8_t  REV_DAT_OK = 0;//���յ�������ȷ������־λ   1Ϊ��ȷ   0Ϊ����

//uint16_t frame_num=0;            //����dmx����֡������
uint16_t ichannel=0;             //dmxͨ��������

uint8_t sc_flag=0;               //����start_code��־λ
uint8_t start_code=0;            //dmx��0֡start_code����
uint8_t dmx_flag=0;              //����dmx����֡��־λ
uint8_t dmx_dat[7];              //����dmx���ݻ���

uint8_t dmx_pwm_c;
uint8_t dmx_pwm_o;
uint8_t dmx_pwm_y;
uint8_t dmx_pwm_w;

uint8_t dmx_pwm_b;
uint8_t dmx_pwm_g;
uint8_t dmx_pwm_r;

uint8_t  Dmx_PwmRefleshFlag;      //Dmx_pwmˢ�±�־λ//��1:��ʾ���µ�dmx���ݰ��������//�ȴ�����

//uint16_t Address=1;              //DMX��ַ

enum {IDLE, BRK,SB_DMX, SB_RDM, SSC_RDM, LEN_RDM, CHECKH_RDM, CHECKL_RDM,SB_SMI};	//Rx states

#include "LEDFunc.h"
#include "KeyFunc.h"
//DMX512���ݸ�ʽ:MTBP+BREAK+MAB+(Start Code = 1λ��ʼλ+8λ��+2λֹͣλ)+(1֡����10λ = λ��ʼλ+8����+2λֹͣλ)...���512֡���ݣ�ע�⣺��ʼλ���ڵ�����ΪUART����ʱ��������
void USART1_IRQHandler(void)
{
//	uint32_t isrflags = READ_REG((&UartHandle_Uart1)->Instance->SR);
//
//	if ((isrflags & USART_SR_RXNE) != RESET)//���ձ�־
//	{
//		Usart_Data = (&UartHandle_Uart1)->Instance->DR;

//		RB8=(Usart_Data&0x0100)>>8;                     //��ʵ���յ�����Ϊ8λ���ݼ���λֹͣλ���˴�ȡ��8λΪ��һλֹͣλ
//		USART_DR = (Usart_Data&0x00FF);                   //ȡ0-7λ8λʹ������
//		if(RB8==0)                                      //��ʼ����ΪBREAK,RB8ֹͣλΪ0
//		{
//			sc_flag=1;                                    //��ʼ�ֽڱ�־λ��1,׼������������start_code
//			return;                                       //������break,���������жϺ���
//		}

//		if((RB8==1)&&(sc_flag==1))                      //������ʼ�ֽ�start_code,��ʱRB8Ϊstart_codeֹͣλΪ1
//		{
//			sc_flag=0;                                    //��0��ʼ�ֽڱ�־λ
//			start_code=USART_DR;                          //������յ�����ʼ�ֽ�
//			if(start_code==0x00)                          //�˶���ʼ�ֽ��Ƿ�Ϊ0x00
//			{
//				frame_num=0;                              //dmx����֡��������0
//				ichannel=0;                               //dmxͨ����������0
//				dmx_flag=1;                               //dmx����֡��־λ��1,׼������������dmx����֡
//				return;                                   //������start_code��ʼ֡,���������жϺ���
//			}
//			else                                          //��ʼ�ֽڲ�Ϊ0x00,����start_code=0xAA��ʾdmxд��ַ����(�û��Զ���)
//			{
//				start_code=0;                               //�����ʼ�ֽ�start_code
//				return;                                     //������start_code��ʼ֡,���������жϺ���
//			}
//		}
//		if((RB8==1)&&(dmx_flag==1))                     //����dmx���ݰ�(���ݰ�����֡���ȿ���Ϊ:1-512֡����)  //����ʹ�õ����ݽ���RB8λֹͣλ
//		{
//			/*******************************************************************************************************/
//			frame_num++;                                  //dmx֡������++
//			if((Key.Dmx512Address<=frame_num)&&(frame_num<Key.Dmx512Address+CHANNEL_NUM))//�Ƚϵ�ǰ�ӻ���ַ//CHANNEL_NUMΪʵ����Чͨ����//DMX512�����ܿ��ƺܶ�ӻ���Ҫѡȡ�ʹӻ���ַ��������ݶα���
//			{
//				dmx_dat[ichannel]=USART_DR;                 //��ȡ���յ���dmx����֡
//				ichannel++;                                 //dmxͨ��������++
//				if(ichannel>=CHANNEL_NUM)                   //���ͨ������������ʵ����Чͨ����CHANNEL_NUM,�Ϳ��Ա���������
//				{
//					LED.DMX512Data[0] = dmx_dat[0];
//					LED.DMX512Data[1] = dmx_dat[1];
//					LED.DMX512Data[2] = dmx_dat[2];
//					LED.DMX512Data[3] = dmx_dat[3];
//					LED.DMX512Data[4] = dmx_dat[4];
//					LED.DMX512Data[5] = dmx_dat[5];
//					LED.DMX512Data[6] = dmx_dat[6];
//					Dmx_PwmRefleshFlag=1;                    //Dmx_pwmˢ�±�־λ��1//��ʾ���µ�dmx���ݰ��������
//				}
//			}
//			if(frame_num>=192)                           //�����512������֡������ɡ���1֡-��512֡��
//			{
//				frame_num=0;                               //dmx����֡��������0
//				ichannel=0;                                //dmxͨ����������0
//				dmx_flag=0;                                //dmx��������֡��־λ��0������dmx����֡������,��������һ��dmx�����+���չ��̡�
//			}
//			return;                                      //������һ֡,���������жϺ���
//		}
//	}
//	else
//	{
//		HAL_UART_IRQHandler(&UartHandle_Uart1);
//	}

	uint32_t isrflags = READ_REG((&UartHandle_Uart1)->Instance->SR);
	uint8_t   RXDAT = 0;
	static uint8_t  RxState = IDLE;
	static uint8_t  STA_FLG_RX = 0;//��ʼ��ͨѶ֡��־
	static uint8_t  RDM_CNT = 0;
	static uint16_t CheckSum = 0;
	static uint16_t DMX_CNT = 0;

	if ((isrflags & USART_SR_RXNE) != RESET)//���ձ�־
	{
		Usart_Data = (&UartHandle_Uart1)->Instance->DR;

		RB8 = (Usart_Data&0x0100)>>8;                     //��ʵ���յ�����Ϊ8λ���ݼ���λֹͣλ���˴�ȡ��8λΪ��һλֹͣλ
		USART_DR = (Usart_Data&0x00FF);                   //ȡ0-7λ8λʹ������

		if(END_FLG_RX)return ;//ǰһ֡����δ�����꣬����������

		if(RB8 == 0)
		{
			if(USART_DR == 0)
			{
				/*��ʼ�����µ�����֡*/
				STA_FLG_RX = 1;
				RxState = BRK;//���յ�BREAK
			}
		}

		if(STA_FLG_RX)
		{
			if(RB8 == 1)
			{
				switch(RxState)
				{
					case BRK:
							/*�жϿ�̨����ģʽ*/
							if(USART_DR == 0x00)//DMXģʽ
							{
								RxState = SB_DMX;
								DMX_CNT = 0;
							}
							else if(USART_DR == 0xcc)//RDMģʽ
							{
								RxState = SB_RDM;
							}
//							else if(USART_DR == 0xaa)//����ģʽ
//							{
//								RxState = SB_SMI;
//								DMX_CNT = 0;MISI = 2;
//							}
							else
							{
								RxState = IDLE;
							}
							break;
//					case SB_SMI:
//							DMX_CNT++;
//							DMX[DMX_CNT - 1] = RXDAT;//�����������
//
//							if(DMX_CNT >= 7)
//							{
//								DMX_CNT = 0;
//								STA_FLG_RX = 0;
//							}
//							break;
					case SB_DMX:
							DMX_CNT++;
							if(DMX_CNT >= Key.Dmx512Address && DMX_CNT <= Key.Dmx512Address + 6)
							{
								LED.DMX512Data[DMX_CNT - Key.Dmx512Address] = USART_DR;//�����������
							}
							else
							{
								if(DMX_CNT == 512)
								{
									DMX_CNT = 0;
									STA_FLG_RX = 0;
								}
							}
							break;
//					case SB_RDM:
//							if(USART_DR == 0x01)//���յ�������Ϊ0x01
//							{
//								RxState = SSC_RDM;
//								RDM_CNT = 3;
//							}
//							break;
//					case SSC_RDM:
//							RDM[2] = RXDAT;//�������ݳ�������
//							if(RDM[2] < sizeof(RDM))//������ճ���С�ڽ������鳤�����ж�Ϊ��ȷ�����Խ���
//							{
//									CheckSum = 0xcd + RDM[2];
//									RxState = LEN_RDM;
//							}
//							break;
//					case LEN_RDM:
//							RDM[RDM_CNT++] = RXDAT;//��������
//							CheckSum += RXDAT;//����У���
//							if (RDM[2] == RDM_CNT) RxState = CHECKH_RDM;
//							break;
//					case CHECKH_RDM:
//							/*У���λ*/
//							if(RXDAT == ((CheckSum&0xff00)>>8))
//							{
//									RxState = CHECKL_RDM;
//							}
//							else
//							{
//									REV_DAT_OK = 0;
//							}
//							break;
//					case CHECKL_RDM:
//							/*У���λ*/
//							if(RXDAT == (CheckSum&0x00ff))
//							{
//									END_FLG_RX = 1;//�����������
//									STA_FLG_RX = 0;
//									REV_DAT_OK = 1;//����������ȷ
//							}
//							else
//							{
//									REV_DAT_OK = 0;
//							}
//							break;
					default:break;
				}
			}
		}
//		if((RB8==1)&&(sc_flag==1))                      //������ʼ�ֽ�start_code,��ʱRB8Ϊstart_codeֹͣλΪ1
//		{
//			sc_flag=0;                                    //��0��ʼ�ֽڱ�־λ
//			start_code=USART_DR;                          //������յ�����ʼ�ֽ�
//			if(start_code==0x00)                          //�˶���ʼ�ֽ��Ƿ�Ϊ0x00
//			{
//				frame_num=0;                              //dmx����֡��������0
//				ichannel=0;                               //dmxͨ����������0
//				dmx_flag=1;                               //dmx����֡��־λ��1,׼������������dmx����֡
//				return;                                   //������start_code��ʼ֡,���������жϺ���
//			}
//			else                                          //��ʼ�ֽڲ�Ϊ0x00,����start_code=0xAA��ʾdmxд��ַ����(�û��Զ���)
//			{
//				start_code=0;                               //�����ʼ�ֽ�start_code
//				return;                                     //������start_code��ʼ֡,���������жϺ���
//			}
//		}
//		if((RB8==1)&&(dmx_flag==1))                     //����dmx���ݰ�(���ݰ�����֡���ȿ���Ϊ:1-512֡����)  //����ʹ�õ����ݽ���RB8λֹͣλ
//		{
//			/*******************************************************************************************************/
//			frame_num++;                                  //dmx֡������++
//			if((Key.Dmx512Address<=frame_num)&&(frame_num<Key.Dmx512Address+CHANNEL_NUM))//�Ƚϵ�ǰ�ӻ���ַ//CHANNEL_NUMΪʵ����Чͨ����//DMX512�����ܿ��ƺܶ�ӻ���Ҫѡȡ�ʹӻ���ַ��������ݶα���
//			{
//				dmx_dat[ichannel]=USART_DR;                 //��ȡ���յ���dmx����֡
//				ichannel++;                                 //dmxͨ��������++
//				if(ichannel>=CHANNEL_NUM)                   //���ͨ������������ʵ����Чͨ����CHANNEL_NUM,�Ϳ��Ա���������
//				{
//					LED.DMX512Data[0] = dmx_dat[0];
//					LED.DMX512Data[1] = dmx_dat[1];
//					LED.DMX512Data[2] = dmx_dat[2];
//					LED.DMX512Data[3] = dmx_dat[3];
//					LED.DMX512Data[4] = dmx_dat[4];
//					LED.DMX512Data[5] = dmx_dat[5];
//					LED.DMX512Data[6] = dmx_dat[6];
//					Dmx_PwmRefleshFlag=1;                    //Dmx_pwmˢ�±�־λ��1//��ʾ���µ�dmx���ݰ��������
//				}
//			}
//			if(frame_num>=192)                           //�����512������֡������ɡ���1֡-��512֡��
//			{
//				frame_num=0;                               //dmx����֡��������0
//				ichannel=0;                                //dmxͨ����������0
//				dmx_flag=0;                                //dmx��������֡��־λ��0������dmx����֡������,��������һ��dmx�����+���չ��̡�
//			}
//			return;                                      //������һ֡,���������жϺ���
//		}
		HAL_UART_IRQHandler(&UartHandle_Uart1);
	}
//	else
//	{
//		HAL_UART_IRQHandler(&UartHandle_Uart1);
//	}
}


#include "py32f0xx_ll_tim.h"
#include "LEDFunc.h"
#include "UserDefined.h"

uint16_t Gradual_Speed = 0;
uint8_t Gradual_R = 0, Gradual_G = 0, Gradual_B = 0;

void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
	// HAL_TIM_IRQHandler(&TimHandle_Tim1);
	if ((LL_TIM_ReadReg(TIM1, SR) & LL_TIM_SR_UIF) == 1 && LL_TIM_IsEnabledIT_UPDATE(TIM1))
	{
		LL_TIM_ClearFlag_UPDATE(TIM1);

		if ((LED.Mode == c_Mode_DMX512_4Chan && LED.GlitterBit == false) ||
				(LED.Mode == c_Mode_DMX512_8Chan && LED.GlitterBit == false && LED.DMX512Mode == c_DMX512_Mode_ChanCtrl))
		{
			if (++Gradual_Speed >= 50)
			{
				Gradual_Speed = 0;

				if (Gradual_R != LED.CutRGB_Buf[LED_R])
				{
					if (Gradual_R < LED.CutRGB_Buf[LED_R])
						Gradual_R++;
					else if (Gradual_R > LED.CutRGB_Buf[LED_R])
						Gradual_R--;

					LedPwmDutySetRed(Gradual_R);
				}

				if (Gradual_G != LED.CutRGB_Buf[LED_G])
				{
					if (Gradual_G < LED.CutRGB_Buf[LED_G])
						Gradual_G++;
					else if (Gradual_G > LED.CutRGB_Buf[LED_G])
						Gradual_G--;

					LedPwmDutySetGreen(Gradual_G);
				}

				if (Gradual_B != LED.CutRGB_Buf[LED_B])
				{
					if (Gradual_B < LED.CutRGB_Buf[LED_B])
						Gradual_B++;
					else if (Gradual_B > LED.CutRGB_Buf[LED_B])
						Gradual_B--;

					LedPwmDutySetBlue(Gradual_B);
				}
			}
		}
		else
		{
			if (LED.RedLightOld != LED.CutRGB_Buf[LED_R])
			{
				LED.RedLightOld = LED.CutRGB_Buf[LED_R];
				LedPwmDutySetRed(LED.CutRGB_Buf[LED_R]);
			}
			if (LED.GreenLightOld != LED.CutRGB_Buf[LED_G])
			{
				LED.GreenLightOld = LED.CutRGB_Buf[LED_G];
				LedPwmDutySetGreen(LED.CutRGB_Buf[LED_G]);
			}
			if (LED.BlueLightOld != LED.CutRGB_Buf[LED_B])
			{
				LED.BlueLightOld = LED.CutRGB_Buf[LED_B];
				LedPwmDutySetBlue(LED.CutRGB_Buf[LED_B]);
			}
		}
	}
}

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
