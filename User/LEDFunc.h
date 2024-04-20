#ifndef _LED_FUNC_H
#define _LED_FUNC_H
#include "py32f0xx_hal.h"
#include "BspDriver_Timer1.h"

//功能模式
#define c_Mode_DMX512_4Chan       1        //DMX512 4通道模式
#define c_Mode_DMX512_8Chan       2        //DMX512 8通道模式
#define c_Mode_RedLight           3        //红色调光模式
#define c_Mode_GreenLight         4        //绿色调光模式
#define c_Mode_BlueLight          5        //蓝色调光模式
#define c_Mode_Glitter            6        //频闪模式
#define c_Mode_OneColor           7        //8个颜色切换模式
#define c_Mode_ColorJump          8        //七彩跳变模式
#define c_Mode_ColorGradual       9        //七彩渐变模式
#define c_Mode_ColorPulse         10       //七彩脉变模式
#define c_Mode_VoiceControl       11       //声控模式

//DMX512控制时模式
#define c_DMX512_Mode_ChanCtrl       1     //0-50通道控制
#define c_DMX512_Mode_OneColor       2     //51-100常用颜色输出8种
#define c_DMX512_Mode_ColorJump      3     //101-150七彩跳变
#define c_DMX512_Mode_ColorGradual   4     //151-200七彩渐变
#define c_DMX512_Mode_ColorPulse     5     //201-250七彩脉变
#define c_DMX512_Mode_VoiceControl   6     //251-255声控

//RGB修改PWM占空比
#define   LedPwmDutySetRed(x)       Tim1PwmDutySetChan1(x)
#define   LedPwmDutySetGreen(x)     Tim1PwmDutySetChan3(x)
#define   LedPwmDutySetBlue(x)      Tim1PwmDutySetChan2(x)
#define   LedPwmDutySetWhite(x)     Tim1PwmDutySetChan4(x)

//RGB_Buf[3]数组位置定义
#define  LED_R  0     //位置0为红色
#define  LED_G  1     //位置1为绿色
#define  LED_B  2     //位置2为蓝色

//单色模式8个颜色定义
//#define  c_OneColorMode_Red         1    //红色
//#define  c_OneColorMode_White       2    //白色
//#define  c_OneColorMode_Wathet      3    //浅蓝色
//#define  c_OneColorMode_Purple      4    //粉色
//#define  c_OneColorMode_Yellow      5    //黄色
//#define  c_OneColorMode_PaleYellow  6    //浅黄色
//#define  c_OneColorMode_Blue        7    //蓝色
//#define  c_OneColorMode_Green       8    //绿色

#define  c_OneColorMode_Red         1    //红色
#define  c_OneColorMode_Green       2    //绿色
#define  c_OneColorMode_Blue        3    //蓝色
#define  c_OneColorMode_PaleYellow  4    //浅黄色
#define  c_OneColorMode_Yellow      5    //黄色
#define  c_OneColorMode_Purple      6    //粉色
#define  c_OneColorMode_Wathet      7    //浅蓝色
#define  c_OneColorMode_White       8    //白色





/*自定义结构体*/
typedef struct
{
	uint8_t bShutter;
	uint8_t Mode;                 //灯光模式
	uint8_t ModeBit;              //灯光模式位防重复进入
	uint8_t DMX512Data[7];        //DMX512串口接收到的数据
	uint8_t RGB_ARR[3];           //led红绿蓝PWM值数组
	uint8_t B_RGB_Buf[3];         //led红绿蓝PWM值数组
	uint8_t CutRGB_Buf[3];        //led红绿蓝PWM值数组/x
	uint8_t RedLightOld;          //led红色PWM旧值，值变化时更新PWM值
	uint8_t GreenLightOld;        //led绿色PWM旧值，值变化时更新PWM值
	uint8_t BlueLightOld;         //led蓝色PWM旧值，值变化时更新PWM值
	uint8_t Step;                 //灯光运行步骤
	uint16_t Count5ms;            //5ms计时
	uint8_t KeyRedLight;          //红色调光模式亮度
	uint8_t KeyGreenLight;        //绿色调光模式亮度
	uint8_t KeyBlueLight;         //蓝色调光模式亮度
	uint8_t GlitterSpeed;         //频闪速度
	uint8_t LastGlitterSpeed;     //频闪速度
	uint8_t OneColorMode;         //单色模式
	uint8_t ChangSpeed;           //灯光速度
	uint8_t LastChangSpeed;       //灯光速度
	uint8_t ColorJumpSpeed;       //七彩跳变速度（无DMX512时） 
	uint8_t ColorGradualSpeed;    //七彩渐变速度（无DMX512时）
	uint8_t ColorPulseSpeed;      //七彩脉变速度（无DMX512时）
	uint8_t MIC_Count;            //声音传感器信号计时
	uint8_t MIC_Bit;              //声音传感器信号标志
	uint8_t VioceCtrlMode;        //声音控制模式
	uint8_t LightBit;             //声音控制时灯亮标志为
	uint8_t VioceCtrlColor;       //声音控制灯颜色
	uint8_t DMX512Mode;           //DMX512模式
	uint8_t DMX512ModeBit;        //DMX512模式位防重复进入
	uint8_t GlitterBit;           //
	float OverallLight;           //
	uint8_t DMX512OnLine;					// dmx
}LEDTypeDef;

extern LEDTypeDef LED;


void LedDMX512_4ChanMode(void);
void LedDMX512_8ChanMode(void);
void LedRedLightMode(void);
void LedGreenLightMode(void);
void LedBlueLightMode(void);
void LedGlitterMode(void);
void LedOneColorMode(void);
void LedColorJumpMode(void);
void LedColorGradualMode(void);
void LedColorPulseMode(void);
void LedVoiceControlMode(void);

void LedDMX512_4ChanTimer(void);
void LedDMX512_8ChanTimer(void);
void LedRedLightTimer(void);
void LedGreenLightTimer(void);
void LedBlueLightTimer(void);
void LedGlitterTimer(void);
void LedOneColorTimer(void);
void LedColorJumpTimer(void);
void LedColorGradualTimer(void);
void LedColorPulseTimer(void);
void LedVoiceControlTimer(void);

void LedOneColorFunc(uint8_t Color);
void LedColorJumpFunc(uint8_t SpeedLevel, uint8_t Speed);
void LedColorGradualFunc(uint8_t SpeedLevel, uint8_t Speed);
void LedColorPulseFunc(uint8_t SpeedLevel, uint8_t Speed);

extern void LED_FunctionMode(void);
extern void LED_FunctionTimer(void);
extern void MIC_Check(void);

#endif /*_LED_FUNC_H*/
