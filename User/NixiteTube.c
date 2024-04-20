#include "NixiteTube.h"
#include "KeyFunc.h"
#include "LEDFunc.h"
#include "NixiteTube_Driver.h"
#include <string.h>

NixieTubeTypeDef NixieTube;

/*接收显示数据数组*/
static void CleanAllDisplay(void);
static void DMX512_4ChanModeDisplay(void);
static void DMX512_8ChanModeDisplay(void);
static void RedLightModeDisplay(void);
static void GreenLightModeDisplay(void);
static void BlueLightModeDisplay(void);
static void GlitterModeDisplay(void);
static void OneColorModeDisplay(void);
static void ColorJumpModeDisplay(void);
static void ColorGradualModeDisplay(void);
static void ColorPulseModeDisplay(void);
static void VoiceControlModeDisplay(void);
static void ThreeNumbersDisplay(uint16_t Number);
static void TwoNumbersDisplay(uint16_t Number);


/**
 * @brief  数码管显示功能
 * @param  无
 * @retval 无
 */
void NixieTubeDisplay(void)
{
  CleanAllDisplay();
  switch (LED.Mode)
  {
  case c_Mode_DMX512_4Chan:
    DMX512_4ChanModeDisplay();
    break;
  case c_Mode_DMX512_8Chan:
    DMX512_8ChanModeDisplay();
    break;
  case c_Mode_RedLight:
    RedLightModeDisplay();
    break;
  case c_Mode_GreenLight:
    GreenLightModeDisplay();
    break;
  case c_Mode_BlueLight:
    BlueLightModeDisplay();
    break;
  case c_Mode_Glitter:
    GlitterModeDisplay();
    break;
  case c_Mode_OneColor:
    OneColorModeDisplay();
    break;
  case c_Mode_ColorJump:
    ColorJumpModeDisplay();
    break;
  case c_Mode_ColorGradual:
    ColorGradualModeDisplay();
    break;
  case c_Mode_ColorPulse:
    ColorPulseModeDisplay();
    break;
  case c_Mode_VoiceControl:
    VoiceControlModeDisplay();
    break;
  default:
    break;
  }
}

/**
 * @brief  数码管显示功能
 * @param  无
 * @retval 无
 */
static void CleanAllDisplay(void)
{
  memset(NixieTube.DisplayBuf, 0, sizeof(NixieTube.DisplayBuf));
}

/**
 * @brief  数码管4通道显示模式
 * @param  无
 * @retval 无
 */
static void DMX512_4ChanModeDisplay(void)
{
  NixieTube.DisplayBuf[1] |= LED_BIT_1B; //"d"
  NixieTube.DisplayBuf[2] |= LED_BIT_1C;
  NixieTube.DisplayBuf[3] |= LED_BIT_1D;
  NixieTube.DisplayBuf[4] |= LED_BIT_1E;
  NixieTube.DisplayBuf[5] |= LED_BIT_1G;
  ThreeNumbersDisplay(Key.Dmx512Address);
}

/**
 * @brief  数码管8通道显示模式
 * @param  无
 * @retval 无
 */
static void DMX512_8ChanModeDisplay(void)
{
  NixieTube.DisplayBuf[0] |= LED_BIT_1A; //"A"
  NixieTube.DisplayBuf[1] |= LED_BIT_1B;
  NixieTube.DisplayBuf[2] |= LED_BIT_1C | LED_BIT_1F;
  NixieTube.DisplayBuf[4] |= LED_BIT_1E;
  NixieTube.DisplayBuf[5] |= LED_BIT_1G;
  ThreeNumbersDisplay(Key.Dmx512Address);
}

/**
 * @brief  数码管红灯调光显示模式
 * @param  无
 * @retval 无
 */
static void RedLightModeDisplay(void)
{
  NixieTube.DisplayBuf[4] |= LED_BIT_1E; //"r"
  NixieTube.DisplayBuf[5] |= LED_BIT_1G;
  ThreeNumbersDisplay(LED.KeyRedLight);
}

/**
 * @brief  数码管绿灯调光显示模式
 * @param  无
 * @retval 无
 */
static void GreenLightModeDisplay(void)
{
  NixieTube.DisplayBuf[0] |= LED_BIT_1A; //"G"
  NixieTube.DisplayBuf[2] |= LED_BIT_1C | LED_BIT_1F;
  NixieTube.DisplayBuf[3] |= LED_BIT_1D;
  NixieTube.DisplayBuf[4] |= LED_BIT_1E;
  ThreeNumbersDisplay(LED.KeyGreenLight);
}

/**
 * @brief  数码管蓝灯调光显示模式
 * @param  无
 * @retval 无
 */
static void BlueLightModeDisplay(void)
{
  NixieTube.DisplayBuf[2] |= LED_BIT_1C | LED_BIT_1F; //"b"
  NixieTube.DisplayBuf[3] |= LED_BIT_1D;
  NixieTube.DisplayBuf[4] |= LED_BIT_1E;
  NixieTube.DisplayBuf[5] |= LED_BIT_1G;
  ThreeNumbersDisplay(LED.KeyBlueLight);
}

/**
 * @brief  数码管频闪显示模式
 * @param  无
 * @retval 无
 */
static void GlitterModeDisplay(void)
{
  NixieTube.DisplayBuf[0] |= LED_BIT_1A; //"F"
  NixieTube.DisplayBuf[2] |= LED_BIT_1F;
  NixieTube.DisplayBuf[4] |= LED_BIT_1E;
  NixieTube.DisplayBuf[5] |= LED_BIT_1G;

  NixieTube.DisplayBuf[0] |= LED_BIT_2G; //"H"
  NixieTube.DisplayBuf[1] |= LED_BIT_2B;
  NixieTube.DisplayBuf[2] |= LED_BIT_2F | LED_BIT_2C;
  NixieTube.DisplayBuf[5] |= LED_BIT_2E;
  TwoNumbersDisplay(LED.GlitterSpeed);
}

/**
 * @brief  数码管单色显示模式
 * @param  无
 * @retval 无
 */
static void OneColorModeDisplay(void)
{
  NixieTube.DisplayBuf[0] |= LED_BIT_1A; //"C"
  NixieTube.DisplayBuf[2] |= LED_BIT_1F;
  NixieTube.DisplayBuf[3] |= LED_BIT_1D;
  NixieTube.DisplayBuf[4] |= LED_BIT_1E;

  NixieTube.DisplayBuf[2] |= LED_BIT_2F; //"L"
  NixieTube.DisplayBuf[4] |= LED_BIT_2D;
  NixieTube.DisplayBuf[5] |= LED_BIT_2E;
  TwoNumbersDisplay(LED.OneColorMode);
}

/**
 * @brief  数码管跳变显示模式
 * @param  无
 * @retval 无
 */
static void ColorJumpModeDisplay(void)
{
  NixieTube.DisplayBuf[0] |= LED_BIT_1A; //"C"
  NixieTube.DisplayBuf[2] |= LED_BIT_1F;
  NixieTube.DisplayBuf[3] |= LED_BIT_1D;
  NixieTube.DisplayBuf[4] |= LED_BIT_1E;

  NixieTube.DisplayBuf[0] |= LED_BIT_2A; //"C"
  NixieTube.DisplayBuf[2] |= LED_BIT_2F;
  NixieTube.DisplayBuf[4] |= LED_BIT_2D;
  NixieTube.DisplayBuf[5] |= LED_BIT_2E;
  TwoNumbersDisplay(LED.ColorJumpSpeed);
}

/**
 * @brief  数码管跳变显示模式
 * @param  无
 * @retval 无
 */
static void ColorGradualModeDisplay(void)
{
  NixieTube.DisplayBuf[1] |= LED_BIT_1B; //"d"
  NixieTube.DisplayBuf[2] |= LED_BIT_1C;
  NixieTube.DisplayBuf[3] |= LED_BIT_1D;
  NixieTube.DisplayBuf[4] |= LED_BIT_1E;
  NixieTube.DisplayBuf[5] |= LED_BIT_1G;

  NixieTube.DisplayBuf[0] |= LED_BIT_2A | LED_BIT_2G; //"E"
  NixieTube.DisplayBuf[2] |= LED_BIT_2F;
  NixieTube.DisplayBuf[4] |= LED_BIT_2D;
  NixieTube.DisplayBuf[5] |= LED_BIT_2E;
  TwoNumbersDisplay(LED.ColorGradualSpeed);
}

/**
 * @brief  数码管渐变显示模式
 * @param  无
 * @retval 无
 */
static void ColorPulseModeDisplay(void)
{
  NixieTube.DisplayBuf[0] |= LED_BIT_1A; //"C"
  NixieTube.DisplayBuf[2] |= LED_BIT_1F;
  NixieTube.DisplayBuf[3] |= LED_BIT_1D;
  NixieTube.DisplayBuf[4] |= LED_BIT_1E;

  NixieTube.DisplayBuf[0] |= LED_BIT_2A | LED_BIT_2G; //"P"
  NixieTube.DisplayBuf[1] |= LED_BIT_2B;
  NixieTube.DisplayBuf[2] |= LED_BIT_2F;
  NixieTube.DisplayBuf[5] |= LED_BIT_2E;
  TwoNumbersDisplay(LED.ColorPulseSpeed);
}

/**
 * @brief  数码管脉变显示模式
 * @param  无
 * @retval 无
 */
static void VoiceControlModeDisplay(void)
{
  NixieTube.DisplayBuf[0] |= LED_BIT_1A; //"S"
  NixieTube.DisplayBuf[2] |= LED_BIT_1C | LED_BIT_1F;
  NixieTube.DisplayBuf[3] |= LED_BIT_1D;
  NixieTube.DisplayBuf[5] |= LED_BIT_1G;

  NixieTube.DisplayBuf[1] |= LED_BIT_2B; //"U"
  NixieTube.DisplayBuf[2] |= LED_BIT_2F | LED_BIT_2C;
  NixieTube.DisplayBuf[4] |= LED_BIT_2D;
  NixieTube.DisplayBuf[5] |= LED_BIT_2E;
  TwoNumbersDisplay(LED.VioceCtrlMode);
}

/**
 * @brief  数码管显示三位数字
 * @param  无
 * @retval 无
 */
static void ThreeNumbersDisplay(uint16_t Number)
{
  uint16_t Hundreds = 0, decade = 0, TheUint = 0, i;
  if (Number > 999)
    return;
  Hundreds = Number / 100 % 10;
  decade = Number / 10 % 10;
  TheUint = Number % 10;
  for (i = 0; i < 6; i++)
  {
    NixieTube.DisplayBuf[i] |= Number2[Hundreds][i];
    NixieTube.DisplayBuf[i] |= Number3[decade][i];
    NixieTube.DisplayBuf[i] |= Number4[TheUint][i];
  }
}

/**
 * @brief  数码管显示两位数字
 * @param  无
 * @retval 无
 */
static void TwoNumbersDisplay(uint16_t Number)
{
  uint16_t decade = 0;
  uint16_t TheUint = 0;
  uint16_t i;

  if (Number > 99)
    return;

  decade = Number / 10 % 10;
  TheUint = Number % 10;

  for (i = 0; i < 6; i++)
  {
    NixieTube.DisplayBuf[i] |= Number3[decade][i];
    NixieTube.DisplayBuf[i] |= Number4[TheUint][i];
  }
}
