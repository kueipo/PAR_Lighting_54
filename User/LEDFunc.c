#include "LEDFunc.h"
#include "UserDefined.h"
#include "BspDriver_GPIO.h"

LEDTypeDef LED;

/**
 * @brief  LED模式功能
 * @param  无
 * @retval 无
 */
void LED_FunctionMode(void)
{
	switch(LED.Mode)
	{
		case c_Mode_DMX512_4Chan:    LedDMX512_4ChanMode(); break;
		case c_Mode_DMX512_8Chan:    LedDMX512_8ChanMode(); break;
		case c_Mode_RedLight:        LedRedLightMode();    break;
		case c_Mode_GreenLight:      LedGreenLightMode();  break;
		case c_Mode_BlueLight:       LedBlueLightMode();   break;
		case c_Mode_Glitter:         LedGlitterMode();     break;
		case c_Mode_OneColor:        LedOneColorMode();    break;
		case c_Mode_ColorJump:       LedColorJumpMode();   break;
		case c_Mode_ColorGradual:    LedColorGradualMode();break;
		case c_Mode_ColorPulse:      LedColorPulseMode();  break;
		case c_Mode_VoiceControl:    LedVoiceControlMode();break;
		default:break;
	}

	LED.CutRGB_Buf[LED_R] = LED.RGB_ARR[LED_R];
	LED.CutRGB_Buf[LED_G] = LED.RGB_ARR[LED_G];
	LED.CutRGB_Buf[LED_B] = LED.RGB_ARR[LED_B];
}

/**
  * @brief  LED模式功能定时执行
  * @param  无
  * @retval 无
  */
void LED_FunctionTimer(void)
{
	switch(LED.Mode)
	{
		case c_Mode_DMX512_4Chan:    LedDMX512_4ChanTimer();break;
		case c_Mode_DMX512_8Chan:    LedDMX512_8ChanTimer();break;
		case c_Mode_RedLight:        LedRedLightTimer();    break;
		case c_Mode_GreenLight:      LedGreenLightTimer();  break;
		case c_Mode_BlueLight:       LedBlueLightTimer();   break;
		case c_Mode_Glitter:         LedGlitterTimer();     break;
		case c_Mode_OneColor:        LedOneColorTimer();    break;
		case c_Mode_ColorJump:       LedColorJumpTimer();   break;
		case c_Mode_ColorGradual:    LedColorGradualTimer();break;
		case c_Mode_ColorPulse:      LedColorPulseTimer();  break;
		case c_Mode_VoiceControl:    LedVoiceControlTimer();break;
		default:break;
	}
}


//颜色对应的RGB值表格
const uint8_t RGBColorData[8][3] = {
	{255,0,  0  },        //红色
	{0,  255,0  },        //绿色
	{0,  0,  255},        //蓝色
	{200,235,20 },        //浅黄色
	{255,255,0  },        //黄色
	{255,0,  255},        //紫色
	{0,  255,255},        //浅蓝色
	{255,255,255},        //白色
};

////颜色对应的RGB值表格,红色除4
//const uint8_t RGBColorData[8][3] = {
//  {64, 0,  0  },        //红色
//  {0,  255,0  },        //绿色
//  {0,  0,  255},        //蓝色
//  {64, 235,20 },        //浅黄色
//  {64, 255,0  },        //黄色
//  {64, 0,  255},        //紫色
//  {0,  255,255},        //浅蓝色
//  {64, 255,255},        //白色
//};

//颜色数据表格对应颜色位置（与上面数组配合使用）
enum {
  c_Red=0,        //红色
  c_Green,        //绿色
  c_Blue,         //蓝色
  c_PaleYellow,   //浅黄色
  c_Yellow,       //黄色
  c_Purple,       //紫色
  c_Wathet,       //浅蓝色
  c_White,        //白色
};

/**
  * @brief  使用DMX512控制时模式判断
  * @param  ModeTemp:输入0-255通道值
  * @retval Mode DMX512控制模式
  */
uint8_t DMX512ModeSelect(uint8_t ModeTemp)
{
	uint8_t Mode;
	if(ModeTemp <= 50)
	{
		Mode = c_DMX512_Mode_ChanCtrl;
	}
	else if(ModeTemp > 50 && ModeTemp <= 100)
	{
		Mode = c_DMX512_Mode_OneColor;
	}
	else if(ModeTemp > 100 && ModeTemp <= 150)
	{
		Mode = c_DMX512_Mode_ColorJump;
	}
	else if(ModeTemp > 150 && ModeTemp <= 200)
	{
		Mode = c_DMX512_Mode_ColorGradual;
	}
	else if(ModeTemp > 200 && ModeTemp <= 250)
	{
		Mode = c_DMX512_Mode_ColorPulse;
	}
	else if(ModeTemp > 250 && ModeTemp <= 255)
	{
		Mode = c_DMX512_Mode_VoiceControl;
	}
	return Mode;
}

/**
  * @brief  DMX512 4通道控制模式
  * @param  无
  * @retval 无
  */
void LedDMX512_4ChanMode(void)
{
	if(LED.ModeBit != c_Mode_DMX512_4Chan)
	{
		LED.ModeBit = c_Mode_DMX512_4Chan;
		LED.Step = 0;
		LED.Count5ms = 0;
		LED.ChangSpeed = 0;
		LED.GlitterBit = false;
		LED.OverallLight = 0;
		LED.RGB_ARR[LED_R] = LED.RGB_ARR[LED_G] = LED.RGB_ARR[LED_B] = 0;
	}

	if(LED.DMX512Data[4] > 0)
	{
		LED.GlitterBit = true;
	}
	else
	{
		LED.GlitterBit = false;
	}

	LED.OverallLight = (float)LED.DMX512Data[0]/255;
	if(LED.GlitterBit == false)
	{
		LED.RGB_ARR[LED_R] = (uint8_t)((float)LED.DMX512Data[1]*LED.OverallLight);
		LED.RGB_ARR[LED_G] = (uint8_t)((float)LED.DMX512Data[2]*LED.OverallLight);
		LED.RGB_ARR[LED_B] = (uint8_t)((float)LED.DMX512Data[3]*LED.OverallLight);
	}
}

/**
  * @brief  DMX512 4通道控制定时执行
  * @param  无
  * @retval 无
  */
void LedDMX512_4ChanTimer(void)
{
	uint8_t Speed;

	if(LED.GlitterBit == true)
	{
		switch(LED.Step)
		{
			case 0:
				LED.RGB_ARR[LED_R] = (uint8_t)((float)LED.DMX512Data[1]*LED.OverallLight);
				LED.RGB_ARR[LED_G] = (uint8_t)((float)LED.DMX512Data[2]*LED.OverallLight);
				LED.RGB_ARR[LED_B] = (uint8_t)((float)LED.DMX512Data[3]*LED.OverallLight);
				break;

			case 1:
				LED.RGB_ARR[LED_R] = 0;
				LED.RGB_ARR[LED_G] = 0;
				LED.RGB_ARR[LED_B] = 0;
				break;
			default:break;
		}
		if(++LED.Count5ms >= 2)    //10ms
		{
			LED.Count5ms = 0;
			if(LED.DMX512Data[4] >= 240)
			{
				Speed = 240;
			}
			else
			{
				Speed = LED.DMX512Data[4];
			}
			if(++LED.ChangSpeed > 255 - Speed)
			{
				LED.ChangSpeed = 0;
				if(LED.Step)
				{
					LED.Step = 0;
				}
				else
				{
					LED.Step = 1;
				}
			}
		}
	}
}

/**
 * @brief  DMX512 8通道控制模式
 * @param  无
 * @retval 无
 */
unsigned char cModeChangeDelay, cMode, cNewMode;
void LedDMX512_8ChanMode(void)
{
	if (LED.ModeBit != c_Mode_DMX512_8Chan)
	{
		LED.ModeBit = c_Mode_DMX512_8Chan;
		LED.Step = 0;
		LED.Count5ms = 0;
		LED.ChangSpeed = 0;
		LED.GlitterBit = false;
		LED.OverallLight = 0;
		LED.RGB_ARR[LED_R] = LED.RGB_ARR[LED_G] = LED.RGB_ARR[LED_B] = 0;
	}

	LED.DMX512Mode = DMX512ModeSelect(LED.DMX512Data[5]);
	if (cMode != LED.DMX512Mode)
	{
		if (cMode != cNewMode)
		{
			cNewMode = cMode;
			cModeChangeDelay = 10; // 改变模式所需要的时间
		}
		else if (--cModeChangeDelay == 0)
		{
			cMode = LED.DMX512Mode;
		//	LED.DMX512Mode = cMode;
			if (LED.DMX512ModeBit != LED.DMX512Mode)
			{
				LED.DMX512ModeBit = LED.DMX512Mode;
				LED.Step = 0;
				LED.Count5ms = 0;
				LED.ChangSpeed = 0;
				LED.GlitterBit = false;
				LED.OverallLight = 0;
				LED.RGB_ARR[LED_R] = LED.RGB_ARR[LED_G] = LED.RGB_ARR[LED_B] = 0;
				if (LED.DMX512Mode == c_DMX512_Mode_ColorPulse)
				{
					LED.RGB_ARR[LED_R] = 252; // 浅红色
					LED.RGB_ARR[LED_G] = 157;
					LED.RGB_ARR[LED_B] = 154;
				}
				if (LED.DMX512Mode != c_DMX512_Mode_VoiceControl)
				{
					LED.ModeBit = c_DMX512_Mode_VoiceControl;
					LED.LightBit = false;
					LED.VioceCtrlColor = 0;
				}
			}
		}
	}

	switch (LED.DMX512Mode)
	{
	case c_DMX512_Mode_ChanCtrl:
		if (LED.DMX512Data[4] > 0)
		{
			LED.GlitterBit = true;
			LED.bShutter = true;
			LED.ChangSpeed = 200 - (190 * LED.DMX512Data[4]) / 255;
			if (LED.ChangSpeed != LED.LastChangSpeed)
			{
				LED.LastChangSpeed = LED.ChangSpeed;
				// LED.ChangSpeed = cTabFlash[LED.GlitterSpeed];
				LED.Count5ms = LED.ChangSpeed;
			}
		}
		else
		{
			LED.GlitterBit = false;
			LED.bShutter = false;
		}

		LED.OverallLight = (float)LED.DMX512Data[0] / 255;
		if (LED.GlitterBit == false)
		{
			LED.RGB_ARR[LED_R] = (uint8_t)((float)LED.DMX512Data[1] * LED.OverallLight);
			LED.RGB_ARR[LED_G] = (uint8_t)((float)LED.DMX512Data[2] * LED.OverallLight);
			LED.RGB_ARR[LED_B] = (uint8_t)((float)LED.DMX512Data[3] * LED.OverallLight);
		}
		break;
	default:
		break;
	}
}

/**
 * @brief  DMX512 8通道控制定时执行
 * @param  无
 * @retval 无
 */
void LedDMX512_8ChanTimer(void)
{
	uint8_t OneColorSelect = 0;
	uint8_t Speed, c;
	switch (LED.DMX512Mode)
	{
	case c_DMX512_Mode_ChanCtrl:
		if (LED.GlitterBit == true)
		{
			if (LED.Count5ms)
			{
				if (--LED.Count5ms == 0)
				{
					LED.Count5ms = LED.ChangSpeed;
				}
				else if (LED.Count5ms > 5)
				{
					for (c = 0; c < 3; c++)
					{
						LED.RGB_ARR[c] = 0;
					}
				}
				else
				{
					LED.RGB_ARR[LED_R] = (uint8_t)((float)LED.DMX512Data[1] * LED.OverallLight);
					LED.RGB_ARR[LED_G] = (uint8_t)((float)LED.DMX512Data[2] * LED.OverallLight);
					LED.RGB_ARR[LED_B] = (uint8_t)((float)LED.DMX512Data[3] * LED.OverallLight);
				}
			}
		}
		break;
	case c_DMX512_Mode_OneColor:
		if (LED.DMX512Data[6] <= 32)
		{
			OneColorSelect = c_OneColorMode_Red;
		}
		else if (LED.DMX512Data[6] > 32 && LED.DMX512Data[6] <= 64)
		{
			OneColorSelect = c_OneColorMode_Green;
		}
		else if (LED.DMX512Data[6] > 64 && LED.DMX512Data[6] <= 96)
		{
			OneColorSelect = c_OneColorMode_Blue;
		}
		else if (LED.DMX512Data[6] > 96 && LED.DMX512Data[6] <= 128)
		{
			OneColorSelect = c_OneColorMode_PaleYellow;
		}
		else if (LED.DMX512Data[6] > 128 && LED.DMX512Data[6] <= 160)
		{
			OneColorSelect = c_OneColorMode_Yellow;
		}
		else if (LED.DMX512Data[6] > 160 && LED.DMX512Data[6] <= 192)
		{
			OneColorSelect = c_OneColorMode_Purple;
		}
		else if (LED.DMX512Data[6] > 192 && LED.DMX512Data[6] <= 224)
		{
			OneColorSelect = c_OneColorMode_Wathet;
		}
		else if (LED.DMX512Data[6] > 224 && LED.DMX512Data[6] <= 255)
		{
			OneColorSelect = c_OneColorMode_White;
		}
		LedOneColorFunc(OneColorSelect);
		break;
	case c_DMX512_Mode_ColorJump:
		LedColorJumpFunc(255, LED.DMX512Data[6]);
		break;
	case c_DMX512_Mode_ColorGradual:
		LedColorGradualFunc(255, LED.DMX512Data[6]);
		break;
	case c_DMX512_Mode_ColorPulse:
		LedColorPulseFunc(255, LED.DMX512Data[6]);
		break;
	case c_DMX512_Mode_VoiceControl:
		MIC_Check();
		if (LED.MIC_Bit == true)
			LED.LightBit = true;
		if (LED.LightBit == true)
		{
			LED.Count5ms++;
			if (LED.Count5ms <= 10) // 1s
			{
				LED.RGB_ARR[LED_R] = RGBColorData[LED.VioceCtrlColor][0];
				LED.RGB_ARR[LED_G] = RGBColorData[LED.VioceCtrlColor][1];
				LED.RGB_ARR[LED_B] = RGBColorData[LED.VioceCtrlColor][2];
			}
			else if (LED.Count5ms <= 400) // 1s
			{
				LED.RGB_ARR[LED_R] = 0;
				LED.RGB_ARR[LED_G] = 0;
				LED.RGB_ARR[LED_B] = 0;
			}
			else
			{
				LED.LightBit = false;
				LED.Count5ms = 0;
				if (++LED.VioceCtrlColor > 7)
					LED.VioceCtrlColor = 0;
			}
		}
		break;
	default:
		break;
	}
}

/**
  * @brief  红色调光模式
  * @param  无
  * @retval 无
  */
void LedRedLightMode(void)
{
	if(LED.ModeBit != c_Mode_RedLight)
	{
		LED.ModeBit = c_Mode_RedLight;
		//LED.RGB_Buf[LED_R] = LED.RGB_Buf[LED_G] = LED.RGB_Buf[LED_B] = 0;
	}
	LED.bShutter = false;
	LED.RGB_ARR[LED_R] = LED.KeyRedLight;
	LED.RGB_ARR[LED_G] = LED.KeyGreenLight;
	LED.RGB_ARR[LED_B] = LED.KeyBlueLight;
}

/**
  * @brief  红色调光模式定制执行
  * @param  无
  * @retval 无
  */
void LedRedLightTimer(void)
{

}

/**
  * @brief  绿色调光模式
  * @param  无
  * @retval 无
  */
void LedGreenLightMode(void)
{
	if(LED.ModeBit != c_Mode_GreenLight)
	{
		LED.ModeBit = c_Mode_GreenLight;
		//LED.RGB_Buf[LED_R] = LED.RGB_Buf[LED_G] = LED.RGB_Buf[LED_B] = 0;
	}
	LED.bShutter = false;
	LED.RGB_ARR[LED_R] = LED.KeyRedLight;
	LED.RGB_ARR[LED_G] = LED.KeyGreenLight;
	LED.RGB_ARR[LED_B] = LED.KeyBlueLight;
}

/**
  * @brief  绿色调光模式定制执行
  * @param  无
  * @retval 无
  */
void LedGreenLightTimer(void)
{

}

/*
  * @brief  蓝色调光模式
  * @param  无
  * @retval 无
  */
void LedBlueLightMode(void)
{
	if(LED.ModeBit != c_Mode_BlueLight)
	{
		LED.ModeBit = c_Mode_BlueLight;
		//LED.RGB_Buf[LED_R] = LED.RGB_Buf[LED_G] = LED.RGB_Buf[LED_B] = 0;
	}
	LED.bShutter = false;
	LED.RGB_ARR[LED_R] = LED.KeyRedLight;
	LED.RGB_ARR[LED_G] = LED.KeyGreenLight;
	LED.RGB_ARR[LED_B] = LED.KeyBlueLight;
}

/*
  * @brief  蓝色调光模式定时执行
  * @param  无
  * @retval 无
  */
void LedBlueLightTimer(void)
{

}

/*
 * @brief  频闪模式
 * @param  无
 * @retval 无
 */

void LedGlitterMode(void)
{
	unsigned char c;

	if (LED.ModeBit != c_Mode_Glitter)
	{
		LED.ModeBit = c_Mode_Glitter;
		LED.Step = 0;

		for (c = 0; c < 3; c++)
		{
			LED.B_RGB_Buf[c] = LED.RGB_ARR[c];
		}

		LED.bShutter = true;
		LED.ChangSpeed = 200 - (190 * LED.GlitterSpeed) / 99;
		LED.Count5ms = LED.ChangSpeed;
		LED.RGB_ARR[LED_R] = LED.RGB_ARR[LED_G] = LED.RGB_ARR[LED_B] = 0;
	}
}

/*
 * @brief  频闪模式定时执行
 * @param  无
 * @retval 无
 */
void LedGlitterTimer(void)
{
	unsigned char c;

	if (LED.Count5ms)
	{
		if (--LED.Count5ms == 0)
		{
			LED.Count5ms = LED.ChangSpeed;
		}
		else if (LED.Count5ms > 5)
		{
			for (c = 0; c < 3; c++)
			{
				LED.RGB_ARR[c] = 0;
			}
		}
		else
		{
			for (c = 0; c < 3; c++)
			{
				LED.RGB_ARR[c] = LED.B_RGB_Buf[c];
			}
		}
	}

	LED.ChangSpeed = 220 - LED.GlitterSpeed * 2; //cTabFlash[LED.GlitterSpeed];
	if (LED.Count5ms > LED.ChangSpeed)
	{
		LED.Count5ms = LED.ChangSpeed;
	}
}

/*
  * @brief  单色模式
  * @param  无
  * @retval 无
  */
void LedOneColorMode(void)
{
	if(LED.ModeBit != c_Mode_OneColor)
	{
		LED.ModeBit = c_Mode_OneColor;
		LED.RGB_ARR[LED_R] = LED.RGB_ARR[LED_G] = LED.RGB_ARR[LED_B] = 0;
	}
	LED.bShutter = true;
	LedOneColorFunc(LED.OneColorMode);
}

/*
  * @brief  单色模式定时执行
  * @param  无
  * @retval 无
  */
void LedOneColorTimer(void)
{

}

/*
  * @brief  单色灯光功能函数
  * @param  Color:颜色
  * @retval 无
  */
void LedOneColorFunc(uint8_t Color)
{
	switch(Color)
	{
		case c_OneColorMode_Red:
			LED.RGB_ARR[LED_R] = RGBColorData[c_Red][0];
			LED.RGB_ARR[LED_G] = RGBColorData[c_Red][1];
			LED.RGB_ARR[LED_B] = RGBColorData[c_Red][2];
			break;
		case c_OneColorMode_White:
			LED.RGB_ARR[LED_R] = RGBColorData[c_White][0];
			LED.RGB_ARR[LED_G] = RGBColorData[c_White][1];
			LED.RGB_ARR[LED_B] = RGBColorData[c_White][2];
			break;
		case c_OneColorMode_Wathet:
			LED.RGB_ARR[LED_R] = RGBColorData[c_Wathet][0];
			LED.RGB_ARR[LED_G] = RGBColorData[c_Wathet][1];
			LED.RGB_ARR[LED_B] = RGBColorData[c_Wathet][2];
			break;
		case c_OneColorMode_Purple:
			LED.RGB_ARR[LED_R] = RGBColorData[c_Purple][0];
			LED.RGB_ARR[LED_G] = RGBColorData[c_Purple][1];
			LED.RGB_ARR[LED_B] = RGBColorData[c_Purple][2];
			break;
		case c_OneColorMode_Yellow:
			LED.RGB_ARR[LED_R] = RGBColorData[c_Yellow][0];
			LED.RGB_ARR[LED_G] = RGBColorData[c_Yellow][1];
			LED.RGB_ARR[LED_B] = RGBColorData[c_Yellow][2];
			break;
		case c_OneColorMode_PaleYellow:
			LED.RGB_ARR[LED_R] = RGBColorData[c_PaleYellow][0];
			LED.RGB_ARR[LED_G] = RGBColorData[c_PaleYellow][1];
			LED.RGB_ARR[LED_B] = RGBColorData[c_PaleYellow][2];
			break;
		case c_OneColorMode_Blue:
			LED.RGB_ARR[LED_R] = RGBColorData[c_Blue][0];
			LED.RGB_ARR[LED_G] = RGBColorData[c_Blue][1];
			LED.RGB_ARR[LED_B] = RGBColorData[c_Blue][2];
			break;
		case c_OneColorMode_Green:
			LED.RGB_ARR[LED_R] = RGBColorData[c_Green][0];
			LED.RGB_ARR[LED_G] = RGBColorData[c_Green][1];
			LED.RGB_ARR[LED_B] = RGBColorData[c_Green][2];
			break;
		default:break;
	}
}

/*
  * @brief  七彩跳变模式
  * @param  无
  * @retval 无
  */
void LedColorJumpMode(void)
{
	if(LED.ModeBit != c_Mode_ColorJump)
	{
		LED.bShutter = true;
		LED.ModeBit = c_Mode_ColorJump;
		LED.Step = 0;
		LED.Count5ms = 0;
		LED.ChangSpeed = 0;
		LED.RGB_ARR[LED_R] = LED.RGB_ARR[LED_G] = LED.RGB_ARR[LED_B] = 0;
	}
}

/*
 * @brief  七彩跳变模式定时执行
 * @param  无
 * @retval 无
 */
void LedColorJumpTimer(void)
{
	LedColorJumpFunc(99, LED.ColorJumpSpeed);
}

/*
 * @brief  七彩跳变功能函数
 * @param  SpeedLevel灯光变化调整等级，使用DMX512为255级，否则为99级
 * @param  Speed灯光变化速度，使用DMX512为0-255级，否则为0-99级
 * @retval 无
 */
void LedColorJumpFunc(uint8_t SpeedLevel, uint8_t Speed)
{
	LED.RGB_ARR[LED_R] = RGBColorData[LED.Step][0];
	LED.RGB_ARR[LED_G] = RGBColorData[LED.Step][1];
	LED.RGB_ARR[LED_B] = RGBColorData[LED.Step][2];

	if (++LED.Count5ms >= 2) // 10ms
	{
		LED.Count5ms = 0;
		if (++LED.ChangSpeed >= SpeedLevel - Speed)
		{
			LED.ChangSpeed = 0;
			if (++LED.Step > 7)
				LED.Step = 0;
		}
	}
}

/*
 * @brief  七彩渐变模式
 * @param  无
 * @retval 无
 */
void LedColorGradualMode(void)
{
	if (LED.ModeBit != c_Mode_ColorGradual)
	{
		LED.ModeBit = c_Mode_ColorGradual;
		LED.Step = 0;
		LED.ChangSpeed = 0;
		LED.RGB_ARR[LED_R] = LED.RGB_ARR[LED_G] = LED.RGB_ARR[LED_B] = 0;
	}
}

/*
 * @brief  七彩渐变模式定时执行
 * @param  无
 * @retval 无
 */
void LedColorGradualTimer(void)
{
	LedColorGradualFunc(99, LED.ColorGradualSpeed);
}

/*
 * @brief  七彩渐变功能函数
 * @param  SpeedLevel灯光变化调整等级，使用DMX512为255级，否则为99级
 * @param  Speed灯光变化速度，使用DMX512为0-255级，否则为0-99级
 * @retval 无
 */
void LedColorGradualFunc(uint8_t SpeedLevel, uint8_t Speed)
{
	if (++LED.ChangSpeed >= SpeedLevel - Speed)
	{
		LED.ChangSpeed = 0;
		switch (LED.Step)
		{
		case 0:
			LED.RGB_ARR[LED_R] = 255; // 红色-->黄色
			LED.RGB_ARR[LED_G] += 1;
			LED.RGB_ARR[LED_B] = 0;
			if (LED.RGB_ARR[LED_G] >= 255)
				LED.Step = 1;
			break;
		case 1:
			LED.RGB_ARR[LED_R] -= 1; // 黄色-->绿色
			LED.RGB_ARR[LED_G] = 255;
			LED.RGB_ARR[LED_B] = 0;
			if (LED.RGB_ARR[LED_R] == 0)
				LED.Step = 2;
			break;

		case 2:
			LED.RGB_ARR[LED_R] = 0; // 绿色-->青色
			LED.RGB_ARR[LED_G] = 255;
			LED.RGB_ARR[LED_B] += 1;
			if (LED.RGB_ARR[LED_B] >= 255)
				LED.Step = 3;
			break;

		case 3:
			LED.RGB_ARR[LED_R] = 0; // 青色-->蓝色
			LED.RGB_ARR[LED_G] -= 1;
			LED.RGB_ARR[LED_B] = 255;
			if (LED.RGB_ARR[LED_G] == 0)
				LED.Step = 4;
			break;

		case 4:
			LED.RGB_ARR[LED_R] += 1; // 蓝色-->紫色
			LED.RGB_ARR[LED_G] = 0;
			LED.RGB_ARR[LED_B] = 255;
			if (LED.RGB_ARR[LED_R] >= 255)
				LED.Step = 5;
			break;

		case 5:
			LED.RGB_ARR[LED_R] = 255; // 紫色-->红色
			LED.RGB_ARR[LED_G] = 0;
			LED.RGB_ARR[LED_B] -= 1;
			if (LED.RGB_ARR[LED_B] == 0)
				LED.Step = 0;
			break;

		default:
			break;
		}
	}
}

/*
  * @brief  七彩跳变模式
  * @param  无
  * @retval 无
  */
void LedColorPulseMode(void)
{
	if(LED.ModeBit != c_Mode_ColorPulse)
	{
		LED.ModeBit = c_Mode_ColorPulse;
		LED.Step = 0;
		LED.Count5ms = 0;
		LED.RGB_ARR[LED_R] = 255;     //浅红色
		LED.RGB_ARR[LED_G] = 255;
		LED.RGB_ARR[LED_B] = 255;
	}
}

/*
  * @brief  七彩跳变模式定时执行
  * @param  无
  * @retval 无
  */
void LedColorPulseTimer(void)
{
	LedColorPulseFunc(99,LED.ColorPulseSpeed);
}

/*
  * @brief  七彩跳变功能函数
  * @param  无
  * @retval 无
  */

const uint8_t RGBColor[3][3] = {
  {255,0,  0  },        //红色
  {0,  255,0  },        //绿色
  {0,  0,  255},        //蓝色
};

void LedColorPulseFunc(uint8_t SpeedLevel, uint8_t Speed)
{
	unsigned char c;
	if(++LED.ChangSpeed >= SpeedLevel - Speed)
	{
		LED.ChangSpeed = 0;
		for (c = 0; c < 3; c++)
		{
			if (LED.RGB_ARR[c] != RGBColor[LED.Step][c])
			{
				if (LED.RGB_ARR[c] > RGBColor[LED.Step][c])
				{
					LED.RGB_ARR[c] -= 1;
				}
				else
				{
					LED.RGB_ARR[c] = RGBColor[LED.Step][c];
				}
			}
		}

		if ((LED.RGB_ARR[0] == RGBColor[LED.Step][0])
			&&(LED.RGB_ARR[1] == RGBColor[LED.Step][1])
		  &&(LED.RGB_ARR[2] == RGBColor[LED.Step][2]))
		{
			LED.Step++;
			if (LED.Step >= 3)
			{
				LED.Step = 0;
			}
		}

//    switch(LED.Step)
//    {
//      case 0:
//      {
//        if(LED.RGB_Buf[LED_R])
//          LED.RGB_Buf[LED_R] -= 1;           //浅红色-->红色
//        if(LED.RGB_Buf[LED_G])
//          LED.RGB_Buf[LED_G] -= 1;
//        if(LED.RGB_Buf[LED_B])
//          LED.RGB_Buf[LED_B] -= 1;
//        if(++LED.Count5ms >= 100)   //500ms
//        {
//          LED.Count5ms = 0;
//          LED.RGB_Buf[LED_R] = 0;          //浅黄色
//          LED.RGB_Buf[LED_G] = 255;
//          LED.RGB_Buf[LED_B] = 0;
//          LED.Step = 1;
//        }
//      }
//      break;
//
//      case 1:
//      {
//        if(LED.RGB_Buf[LED_R])
//          LED.RGB_Buf[LED_R] -= 1;           //浅黄色-->绿色
//        if(LED.RGB_Buf[LED_G])
//          LED.RGB_Buf[LED_G] -= 1;
//        if(LED.RGB_Buf[LED_B])
//          LED.RGB_Buf[LED_B] -= 1;
//        if(++LED.Count5ms >= 100)    //500ms
//        {
//          LED.Count5ms = 0;
//          LED.RGB_Buf[LED_R] = 0;             //浅蓝色
//          LED.RGB_Buf[LED_G] = 255;
//          LED.RGB_Buf[LED_B] = 255;
//          LED.Step = 2;
//        }
//      }
//      break;
//
//      case 2:
//      {
//        if(LED.RGB_Buf[LED_R])
//          LED.RGB_Buf[LED_R] -= 1;            //浅黄色-->绿色
//        if(LED.RGB_Buf[LED_G])
//          LED.RGB_Buf[LED_G] -= 1;
//        if(LED.RGB_Buf[LED_B])
//          LED.RGB_Buf[LED_B] -= 1;
//        if(++LED.Count5ms >= 100)     //500ms
//        {
//          LED.Count5ms = 0;
//          LED.RGB_Buf[LED_R] = 252;          //浅红色
//          LED.RGB_Buf[LED_G] = 157;
//          LED.RGB_Buf[LED_B] = 154;
//          LED.Step = 0;
//        }
//      }
//      break;
//
//      default:
//        break;
//    }
	}
}

/*
 * @brief  声音控制灯光模式
 * @param  无
 * @retval 无
 */
void LedVoiceControlMode(void)
{
	if (LED.ModeBit != c_Mode_VoiceControl)
	{
		LED.ModeBit = c_Mode_VoiceControl;
		LED.Count5ms = 0;
		LED.LightBit = false;
		LED.bShutter = true;
		LED.RGB_ARR[LED_R] = LED.RGB_ARR[LED_G] = LED.RGB_ARR[LED_B] = 0;
	}
}

/*
  * @brief  声音控制灯光模式定时执行
  * @param  无
  * @retval 无
  */
unsigned short wDebugValue;
void LedVoiceControlTimer(void)
{
	MIC_Check();
	if (LED.MIC_Bit == true)
		LED.LightBit = true;
	if (LED.VioceCtrlMode == 9)
	{
		if (LED.LightBit == true)
		{
			wDebugValue++;
			LED.LightBit = false;
			LED.Count5ms = 1000;
			LED.RGB_ARR[LED_R] = RGBColorData[LED.VioceCtrlColor][0];
			LED.RGB_ARR[LED_G] = RGBColorData[LED.VioceCtrlColor][1];
			LED.RGB_ARR[LED_B] = RGBColorData[LED.VioceCtrlColor][2];
		}
		else if (LED.Count5ms) // 500ms
		{
			LED.Count5ms--;
			if (LED.Count5ms == 950)
			{
				if (++LED.VioceCtrlColor > 7)
					LED.VioceCtrlColor = 0;
			}
			if (LED.Count5ms == 0)
			{
				LED.RGB_ARR[LED_R] = 0;
				LED.RGB_ARR[LED_G] = 0;
				LED.RGB_ARR[LED_B] = 0;
			}
		}
	}
	else
	{
		if (LED.LightBit == true)
		{
			LED.Count5ms++;
			if (LED.Count5ms <= 10) // 500ms
			{
				LED.RGB_ARR[LED_R] = RGBColorData[LED.VioceCtrlMode - 1][0];
				LED.RGB_ARR[LED_G] = RGBColorData[LED.VioceCtrlMode - 1][1];
				LED.RGB_ARR[LED_B] = RGBColorData[LED.VioceCtrlMode - 1][2];
			}
			else if (LED.Count5ms <= 50) // 500ms
			{
				LED.RGB_ARR[LED_R] = 0;
				LED.RGB_ARR[LED_G] = 0;
				LED.RGB_ARR[LED_B] = 0;
			}
			else
			{
				LED.LightBit = false;
				LED.Count5ms = 0;
			}
		}
	}
}

/*
 * @brief  声音传感器检测
 * @param  无
 * @retval 无
 */
void MIC_Check(void)
{
	if (MIC_GPIO_READ)
	{
		if (++LED.MIC_Count >= 2)
			LED.MIC_Bit = true;
	}
	else
	{
		LED.MIC_Count = 0;
		LED.MIC_Bit = false;
	}
}
