#ifndef _LED_FUNC_H
#define _LED_FUNC_H
#include "py32f0xx_hal.h"
#include "BspDriver_Timer1.h"

//����ģʽ
#define c_Mode_DMX512_4Chan       1        //DMX512 4ͨ��ģʽ
#define c_Mode_DMX512_8Chan       2        //DMX512 8ͨ��ģʽ
#define c_Mode_RedLight           3        //��ɫ����ģʽ
#define c_Mode_GreenLight         4        //��ɫ����ģʽ
#define c_Mode_BlueLight          5        //��ɫ����ģʽ
#define c_Mode_Glitter            6        //Ƶ��ģʽ
#define c_Mode_OneColor           7        //8����ɫ�л�ģʽ
#define c_Mode_ColorJump          8        //�߲�����ģʽ
#define c_Mode_ColorGradual       9        //�߲ʽ���ģʽ
#define c_Mode_ColorPulse         10       //�߲�����ģʽ
#define c_Mode_VoiceControl       11       //����ģʽ

//DMX512����ʱģʽ
#define c_DMX512_Mode_ChanCtrl       1     //0-50ͨ������
#define c_DMX512_Mode_OneColor       2     //51-100������ɫ���8��
#define c_DMX512_Mode_ColorJump      3     //101-150�߲�����
#define c_DMX512_Mode_ColorGradual   4     //151-200�߲ʽ���
#define c_DMX512_Mode_ColorPulse     5     //201-250�߲�����
#define c_DMX512_Mode_VoiceControl   6     //251-255����

//RGB�޸�PWMռ�ձ�
#define   LedPwmDutySetRed(x)       Tim1PwmDutySetChan1(x)
#define   LedPwmDutySetGreen(x)     Tim1PwmDutySetChan3(x)
#define   LedPwmDutySetBlue(x)      Tim1PwmDutySetChan2(x)
#define   LedPwmDutySetWhite(x)     Tim1PwmDutySetChan4(x)

//RGB_Buf[3]����λ�ö���
#define  LED_R  0     //λ��0Ϊ��ɫ
#define  LED_G  1     //λ��1Ϊ��ɫ
#define  LED_B  2     //λ��2Ϊ��ɫ

//��ɫģʽ8����ɫ����
//#define  c_OneColorMode_Red         1    //��ɫ
//#define  c_OneColorMode_White       2    //��ɫ
//#define  c_OneColorMode_Wathet      3    //ǳ��ɫ
//#define  c_OneColorMode_Purple      4    //��ɫ
//#define  c_OneColorMode_Yellow      5    //��ɫ
//#define  c_OneColorMode_PaleYellow  6    //ǳ��ɫ
//#define  c_OneColorMode_Blue        7    //��ɫ
//#define  c_OneColorMode_Green       8    //��ɫ

#define  c_OneColorMode_Red         1    //��ɫ
#define  c_OneColorMode_Green       2    //��ɫ
#define  c_OneColorMode_Blue        3    //��ɫ
#define  c_OneColorMode_PaleYellow  4    //ǳ��ɫ
#define  c_OneColorMode_Yellow      5    //��ɫ
#define  c_OneColorMode_Purple      6    //��ɫ
#define  c_OneColorMode_Wathet      7    //ǳ��ɫ
#define  c_OneColorMode_White       8    //��ɫ





/*�Զ���ṹ��*/
typedef struct
{
	uint8_t bShutter;
	uint8_t Mode;                 //�ƹ�ģʽ
	uint8_t ModeBit;              //�ƹ�ģʽλ���ظ�����
	uint8_t DMX512Data[7];        //DMX512���ڽ��յ�������
	uint8_t RGB_ARR[3];           //led������PWMֵ����
	uint8_t B_RGB_Buf[3];         //led������PWMֵ����
	uint8_t CutRGB_Buf[3];        //led������PWMֵ����/x
	uint8_t RedLightOld;          //led��ɫPWM��ֵ��ֵ�仯ʱ����PWMֵ
	uint8_t GreenLightOld;        //led��ɫPWM��ֵ��ֵ�仯ʱ����PWMֵ
	uint8_t BlueLightOld;         //led��ɫPWM��ֵ��ֵ�仯ʱ����PWMֵ
	uint8_t Step;                 //�ƹ����в���
	uint16_t Count5ms;            //5ms��ʱ
	uint8_t KeyRedLight;          //��ɫ����ģʽ����
	uint8_t KeyGreenLight;        //��ɫ����ģʽ����
	uint8_t KeyBlueLight;         //��ɫ����ģʽ����
	uint8_t GlitterSpeed;         //Ƶ���ٶ�
	uint8_t LastGlitterSpeed;     //Ƶ���ٶ�
	uint8_t OneColorMode;         //��ɫģʽ
	uint8_t ChangSpeed;           //�ƹ��ٶ�
	uint8_t LastChangSpeed;       //�ƹ��ٶ�
	uint8_t ColorJumpSpeed;       //�߲������ٶȣ���DMX512ʱ�� 
	uint8_t ColorGradualSpeed;    //�߲ʽ����ٶȣ���DMX512ʱ��
	uint8_t ColorPulseSpeed;      //�߲������ٶȣ���DMX512ʱ��
	uint8_t MIC_Count;            //�����������źż�ʱ
	uint8_t MIC_Bit;              //�����������źű�־
	uint8_t VioceCtrlMode;        //��������ģʽ
	uint8_t LightBit;             //��������ʱ������־Ϊ
	uint8_t VioceCtrlColor;       //�������Ƶ���ɫ
	uint8_t DMX512Mode;           //DMX512ģʽ
	uint8_t DMX512ModeBit;        //DMX512ģʽλ���ظ�����
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