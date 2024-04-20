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

#define CHANNEL_NUM  7//dmx实际有效通道数

uint16_t Usart_Data;
uint8_t  USART_DR;
uint8_t  RB8;

uint8_t  END_FLG_RX = 0;//接收通讯帧完成标志
uint8_t  REV_DAT_OK = 0;//接收的数据正确或错误标志位   1为正确   0为错误

//uint16_t frame_num=0;            //接收dmx数据帧计数器
uint16_t ichannel=0;             //dmx通道计数器

uint8_t sc_flag=0;               //接收start_code标志位
uint8_t start_code=0;            //dmx第0帧start_code缓存
uint8_t dmx_flag=0;              //接收dmx数据帧标志位
uint8_t dmx_dat[7];              //接收dmx数据缓存

uint8_t dmx_pwm_c;
uint8_t dmx_pwm_o;
uint8_t dmx_pwm_y;
uint8_t dmx_pwm_w;

uint8_t dmx_pwm_b;
uint8_t dmx_pwm_g;
uint8_t dmx_pwm_r;

uint8_t  Dmx_PwmRefleshFlag;      //Dmx_pwm刷新标志位//置1:表示有新的dmx数据包接收完成//等待处理

//uint16_t Address=1;              //DMX地址

enum {IDLE, BRK,SB_DMX, SB_RDM, SSC_RDM, LEN_RDM, CHECKH_RDM, CHECKL_RDM,SB_SMI};	//Rx states

#include "LEDFunc.h"
#include "KeyFunc.h"
//DMX512数据格式:MTBP+BREAK+MAB+(Start Code = 1位开始位+8位低+2位停止位)+(1帧数据10位 = 位开始位+8数据+2位停止位)...最多512帧数据，注意：开始位存在但不作为UART的真时接收数据
void USART1_IRQHandler(void)
{
//	uint32_t isrflags = READ_REG((&UartHandle_Uart1)->Instance->SR);
//
//	if ((isrflags & USART_SR_RXNE) != RESET)//接收标志
//	{
//		Usart_Data = (&UartHandle_Uart1)->Instance->DR;

//		RB8=(Usart_Data&0x0100)>>8;                     //真实接收的数据为8位数据加两位停止位，此处取第8位为第一位停止位
//		USART_DR = (Usart_Data&0x00FF);                   //取0-7位8位使用数据
//		if(RB8==0)                                      //开始数据为BREAK,RB8停止位为0
//		{
//			sc_flag=1;                                    //起始字节标志位置1,准备接下来接收start_code
//			return;                                       //接收完break,必须跳出中断函数
//		}

//		if((RB8==1)&&(sc_flag==1))                      //接收起始字节start_code,此时RB8为start_code停止位为1
//		{
//			sc_flag=0;                                    //清0起始字节标志位
//			start_code=USART_DR;                          //保存接收到的起始字节
//			if(start_code==0x00)                          //核对起始字节是否为0x00
//			{
//				frame_num=0;                              //dmx数据帧计数器清0
//				ichannel=0;                               //dmx通道计数器清0
//				dmx_flag=1;                               //dmx数据帧标志位置1,准备接下来接收dmx数据帧
//				return;                                   //接收完start_code起始帧,必须跳出中断函数
//			}
//			else                                          //起始字节不为0x00,比如start_code=0xAA表示dmx写地址功能(用户自定义)
//			{
//				start_code=0;                               //清除起始字节start_code
//				return;                                     //接收完start_code起始帧,必须跳出中断函数
//			}
//		}
//		if((RB8==1)&&(dmx_flag==1))                     //接收dmx数据包(数据包所含帧长度可以为:1-512帧数据)  //真正使用的数据接收RB8位停止位
//		{
//			/*******************************************************************************************************/
//			frame_num++;                                  //dmx帧计数器++
//			if((Key.Dmx512Address<=frame_num)&&(frame_num<Key.Dmx512Address+CHANNEL_NUM))//比较当前从机地址//CHANNEL_NUM为实际有效通道数//DMX512主机能控制很多从机，要选取和从机地址相符的数据段保存
//			{
//				dmx_dat[ichannel]=USART_DR;                 //读取接收到的dmx数据帧
//				ichannel++;                                 //dmx通道计数器++
//				if(ichannel>=CHANNEL_NUM)                   //如果通道计数器超过实际有效通道数CHANNEL_NUM,就可以保存数据了
//				{
//					LED.DMX512Data[0] = dmx_dat[0];
//					LED.DMX512Data[1] = dmx_dat[1];
//					LED.DMX512Data[2] = dmx_dat[2];
//					LED.DMX512Data[3] = dmx_dat[3];
//					LED.DMX512Data[4] = dmx_dat[4];
//					LED.DMX512Data[5] = dmx_dat[5];
//					LED.DMX512Data[6] = dmx_dat[6];
//					Dmx_PwmRefleshFlag=1;                    //Dmx_pwm刷新标志位置1//表示有新的dmx数据包接收完成
//				}
//			}
//			if(frame_num>=192)                           //如果第512个数据帧接收完成【第1帧-第512帧】
//			{
//				frame_num=0;                               //dmx数据帧计数器清0
//				ichannel=0;                                //dmx通道计数器清0
//				dmx_flag=0;                                //dmx接收数据帧标志位清0【表明dmx数据帧接收完,将进入下一个dmx包检测+接收过程】
//			}
//			return;                                      //接收完一帧,必须跳出中断函数
//		}
//	}
//	else
//	{
//		HAL_UART_IRQHandler(&UartHandle_Uart1);
//	}

	uint32_t isrflags = READ_REG((&UartHandle_Uart1)->Instance->SR);
	uint8_t   RXDAT = 0;
	static uint8_t  RxState = IDLE;
	static uint8_t  STA_FLG_RX = 0;//开始新通讯帧标志
	static uint8_t  RDM_CNT = 0;
	static uint16_t CheckSum = 0;
	static uint16_t DMX_CNT = 0;

	if ((isrflags & USART_SR_RXNE) != RESET)//接收标志
	{
		Usart_Data = (&UartHandle_Uart1)->Instance->DR;

		RB8 = (Usart_Data&0x0100)>>8;                     //真实接收的数据为8位数据加两位停止位，此处取第8位为第一位停止位
		USART_DR = (Usart_Data&0x00FF);                   //取0-7位8位使用数据

		if(END_FLG_RX)return ;//前一帧数据未处理完，丢弃新数据

		if(RB8 == 0)
		{
			if(USART_DR == 0)
			{
				/*开始接收新的数据帧*/
				STA_FLG_RX = 1;
				RxState = BRK;//接收到BREAK
			}
		}

		if(STA_FLG_RX)
		{
			if(RB8 == 1)
			{
				switch(RxState)
				{
					case BRK:
							/*判断控台数据模式*/
							if(USART_DR == 0x00)//DMX模式
							{
								RxState = SB_DMX;
								DMX_CNT = 0;
							}
							else if(USART_DR == 0xcc)//RDM模式
							{
								RxState = SB_RDM;
							}
//							else if(USART_DR == 0xaa)//主从模式
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
//							DMX[DMX_CNT - 1] = RXDAT;//存入接收数组
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
								LED.DMX512Data[DMX_CNT - Key.Dmx512Address] = USART_DR;//存入接收数组
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
//							if(USART_DR == 0x01)//接收到的数据为0x01
//							{
//								RxState = SSC_RDM;
//								RDM_CNT = 3;
//							}
//							break;
//					case SSC_RDM:
//							RDM[2] = RXDAT;//接收数据长度数据
//							if(RDM[2] < sizeof(RDM))//如果接收长度小于接收数组长度则判断为正确，可以接收
//							{
//									CheckSum = 0xcd + RDM[2];
//									RxState = LEN_RDM;
//							}
//							break;
//					case LEN_RDM:
//							RDM[RDM_CNT++] = RXDAT;//接收数据
//							CheckSum += RXDAT;//计算校验和
//							if (RDM[2] == RDM_CNT) RxState = CHECKH_RDM;
//							break;
//					case CHECKH_RDM:
//							/*校验高位*/
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
//							/*校验低位*/
//							if(RXDAT == (CheckSum&0x00ff))
//							{
//									END_FLG_RX = 1;//接收数据完成
//									STA_FLG_RX = 0;
//									REV_DAT_OK = 1;//接收数据正确
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
//		if((RB8==1)&&(sc_flag==1))                      //接收起始字节start_code,此时RB8为start_code停止位为1
//		{
//			sc_flag=0;                                    //清0起始字节标志位
//			start_code=USART_DR;                          //保存接收到的起始字节
//			if(start_code==0x00)                          //核对起始字节是否为0x00
//			{
//				frame_num=0;                              //dmx数据帧计数器清0
//				ichannel=0;                               //dmx通道计数器清0
//				dmx_flag=1;                               //dmx数据帧标志位置1,准备接下来接收dmx数据帧
//				return;                                   //接收完start_code起始帧,必须跳出中断函数
//			}
//			else                                          //起始字节不为0x00,比如start_code=0xAA表示dmx写地址功能(用户自定义)
//			{
//				start_code=0;                               //清除起始字节start_code
//				return;                                     //接收完start_code起始帧,必须跳出中断函数
//			}
//		}
//		if((RB8==1)&&(dmx_flag==1))                     //接收dmx数据包(数据包所含帧长度可以为:1-512帧数据)  //真正使用的数据接收RB8位停止位
//		{
//			/*******************************************************************************************************/
//			frame_num++;                                  //dmx帧计数器++
//			if((Key.Dmx512Address<=frame_num)&&(frame_num<Key.Dmx512Address+CHANNEL_NUM))//比较当前从机地址//CHANNEL_NUM为实际有效通道数//DMX512主机能控制很多从机，要选取和从机地址相符的数据段保存
//			{
//				dmx_dat[ichannel]=USART_DR;                 //读取接收到的dmx数据帧
//				ichannel++;                                 //dmx通道计数器++
//				if(ichannel>=CHANNEL_NUM)                   //如果通道计数器超过实际有效通道数CHANNEL_NUM,就可以保存数据了
//				{
//					LED.DMX512Data[0] = dmx_dat[0];
//					LED.DMX512Data[1] = dmx_dat[1];
//					LED.DMX512Data[2] = dmx_dat[2];
//					LED.DMX512Data[3] = dmx_dat[3];
//					LED.DMX512Data[4] = dmx_dat[4];
//					LED.DMX512Data[5] = dmx_dat[5];
//					LED.DMX512Data[6] = dmx_dat[6];
//					Dmx_PwmRefleshFlag=1;                    //Dmx_pwm刷新标志位置1//表示有新的dmx数据包接收完成
//				}
//			}
//			if(frame_num>=192)                           //如果第512个数据帧接收完成【第1帧-第512帧】
//			{
//				frame_num=0;                               //dmx数据帧计数器清0
//				ichannel=0;                                //dmx通道计数器清0
//				dmx_flag=0;                                //dmx接收数据帧标志位清0【表明dmx数据帧接收完,将进入下一个dmx包检测+接收过程】
//			}
//			return;                                      //接收完一帧,必须跳出中断函数
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
