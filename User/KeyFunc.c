#include "KeyFunc.h"
#include "LEDFunc.h"
#include "UserDefined.h"
#include "EEPROM.h"
#include "Timer.h"

#define LOOSEN_TIME					9    //400ms

#define KEY_PRESS_SHORT_TIME        8
#define KEY_UP_SHORT_TIME           8
#define KEY_PRESS_LONG_TIME         200
#define KEY_CONTINUE_TIME           220


KeyTypeDef Key;
_key_func key_scan_func;

void KeyFunc(uint16_t KeyCode);
void KeyPlusFunc(uint8_t Mode);
void KeyDownFunc(uint8_t Mode);



void KeyFunc(uint16_t KeyCode)
{
	switch(KeyCode)
	{
		case c_KeyValue_Nothing:
			Key.KeyStateBit = c_KeyValue_Nothing;
			break;

		case c_KeyValue_Menu:
			if(Key.KeyStateBit != c_KeyValue_Menu)
			{
				Key.KeyStateBit = c_KeyValue_Menu;
				if(++LED.Mode >= 12)
				{
					LED.Mode = 1;
				}
			}
			break;

		case c_KeyValue_Plus:
			if(Key.KeyStateBit != c_KeyValue_Plus)
			{
				Key.KeyStateBit = c_KeyValue_Plus;
				KeyPlusFunc(LED.Mode);
			}        
			break;

		case c_KeyValue_Down:
			if(Key.KeyStateBit != c_KeyValue_Down)
			{
				Key.KeyStateBit = c_KeyValue_Down;
				KeyDownFunc(LED.Mode);
			}
			break;

		case c_KeyValue_Enter:
			if(Key.KeyStateBit != c_KeyValue_Enter)
			{      
				Key.KeyStateBit = c_KeyValue_Enter;
				WriteUserSetDataIntoEEPROM();
			}
			break;

		case c_KeyValue_Plus_Hold:
			KeyPlusFunc(LED.Mode);
			break;

		case c_KeyValue_Down_Hold:
			KeyDownFunc(LED.Mode);
			break;

		default:break;
	}
	Key.KeyUserVlaue = 0;
}

void KeyPlusFunc(uint8_t Mode)
{
	switch(Mode)
	{
		case c_Mode_DMX512_4Chan:
		case c_Mode_DMX512_8Chan:
			if(Key.Dmx512Address < 512)
			{
				Key.Dmx512Address++;
			}
			else
			{
				Key.Dmx512Address = 1;
			}
			break;

		case c_Mode_RedLight:
			if(LED.KeyRedLight < 255)
			{
				LED.KeyRedLight++;
			}
			else
			{
				LED.KeyRedLight = 0;
			}
			break;

		case c_Mode_GreenLight:
			if(LED.KeyGreenLight < 255)
			{
				LED.KeyGreenLight++;
			}
			else
			{
				LED.KeyGreenLight = 0;
			}
			break;

		case c_Mode_BlueLight:
			if(LED.KeyBlueLight < 255)
			{
				LED.KeyBlueLight++;
			}
			else
			{
				LED.KeyBlueLight = 0;
			}
			break;

		case c_Mode_Glitter:
			if(LED.GlitterSpeed < 99)
			{
				LED.GlitterSpeed++;
			}
			else
			{
				LED.GlitterSpeed = 1;
			}
			break;

		case c_Mode_OneColor:
			if(LED.OneColorMode < 8)
			{
				LED.OneColorMode++;
			}
			else
			{
				LED.OneColorMode = 1;
			}
			break;

		case c_Mode_ColorJump:
			if(LED.ColorJumpSpeed < 99)
			{
				LED.ColorJumpSpeed++;
			}
			else
			{
				LED.ColorJumpSpeed = 1;
			}
			break;

		case c_Mode_ColorGradual:
			if(LED.ColorGradualSpeed < 99)
			{
				LED.ColorGradualSpeed++;
			}
			else
			{
				LED.ColorGradualSpeed = 1;
			}
			break;    

		case c_Mode_ColorPulse:
			if(LED.ColorPulseSpeed < 99)
			{
				LED.ColorPulseSpeed++;
			}
			else
			{
				LED.ColorPulseSpeed = 1;
			}
			break;

		case c_Mode_VoiceControl:
			if(LED.VioceCtrlMode < 9)
			{
				LED.VioceCtrlMode++;
			}
			else
			{
				LED.VioceCtrlMode = 1;
			}
			break;

		default:break;
	}  
}

void KeyDownFunc(uint8_t Mode)
{
	switch(LED.Mode)
	{
		case c_Mode_DMX512_4Chan:
		case c_Mode_DMX512_8Chan:
			if(Key.Dmx512Address > 1)
			{
				Key.Dmx512Address--;
			}
			else
			{
				Key.Dmx512Address = 512;
			}
			break;

		case c_Mode_RedLight:
			if(LED.KeyRedLight > 0)
			{
				LED.KeyRedLight--;
			}
			else
			{
				LED.KeyRedLight = 255;
			}
			break;

		case c_Mode_GreenLight:
			if(LED.KeyGreenLight > 0)
			{
				LED.KeyGreenLight--;
			}
			else
			{
				LED.KeyGreenLight = 255;
			}
			break;

		case c_Mode_BlueLight:
			if(LED.KeyBlueLight > 0)
			{
				LED.KeyBlueLight--;
			}
			else
			{
				LED.KeyBlueLight = 255;
			}
			break;

		case c_Mode_Glitter:
			if(LED.GlitterSpeed > 1)
			{
				LED.GlitterSpeed--;
			}
			else
			{
				LED.GlitterSpeed = 99;
			}
			break;

		case c_Mode_OneColor:
			if(LED.OneColorMode > 1)
			{
				LED.OneColorMode--;
			}
			else
			{
				LED.OneColorMode = 8;
			}
			break;

		case c_Mode_ColorJump:
			if(LED.ColorJumpSpeed > 1)
			{
				LED.ColorJumpSpeed--;
			}
			else
			{
				LED.ColorJumpSpeed = 99;
			}
			break;

		case c_Mode_ColorGradual:
			if(LED.ColorGradualSpeed > 1)
			{
				LED.ColorGradualSpeed--;
			}
			else
			{
				LED.ColorGradualSpeed = 99;
			}
			break;

		case c_Mode_ColorPulse:
			if(LED.ColorPulseSpeed > 1)
			{
				LED.ColorPulseSpeed--;
			}
			else
			{
				LED.ColorPulseSpeed = 99;
			}
			break;

		case c_Mode_VoiceControl:
			if(LED.VioceCtrlMode > 1)
			{
				LED.VioceCtrlMode--;
			}
			else
			{
				LED.VioceCtrlMode = 9;
			}
			break;

		default:break;    
	}  
}


//5ms
void KeyScan(uint8_t value)
{
	static uint16_t key_code = 0;
	static uint8_t key_value = 0;
	static uint8_t keyBack = 0;
	
	key_value = value;
	key_code = 0;
	
	if(key_value == 0XFF || key_value == 0)
	{       //����ֵΪ0
		if(++key_scan_func.key_up_time > 500) key_scan_func.key_up_time = 500;		//����ʱ��++ ����ɨ����ʱ�����2.5��  ɨ�����ϼ�ʱ����2.5��
		if(key_scan_func.key_up_time < 16)//����ɨ�����ϼ�ʱС��80ms����
		{                   
			return;
		}
		else if(key_scan_func.key_up_time < LOOSEN_TIME)//����ɨ�����ϼ�ʱС��45ms
		{          
			if(key_scan_func.double_click_flag==1)//����
			{               				
				key_scan_func.key_press_time_double = key_scan_func.key_press_time;      //˫������ʱ����ڰ�������ʱ��
				key_scan_func.key_press_time = 0;                  //��������ʱ�����0
				key_scan_func.double_click_flag=2;                 //˫����ʱ��־Ϊ2
			}
		}
	 	else if(key_scan_func.key_up_time < LOOSEN_TIME+10)//����ɨ�����ϼ�ʱС�� 95ms, ����80ms
		{         
			if(key_scan_func.double_click_flag == 2)//����˫����־Ϊ2
			{                   
				key_scan_func.key_press_time = key_scan_func.key_press_time_double;   //��������ʱ����� ˫������ʱ��
				key_scan_func.double_click_flag = 0;                    //˫����ʱ��־Ϊ0
			}
			
			if(key_scan_func.key_press_time >= KEY_PRESS_LONG_TIME)//���簴������ʱ�� ���ڵ��� 1��
			{     	
				key_code = keyBack | KEY_LONG_UP;                       //������
				key_scan_func.double_click_flag=0;                      //˫����ʱ��־Ϊ0
			} 
			else if(key_scan_func.key_press_time >= KEY_PRESS_SHORT_TIME)//���簴������ʱ�� ���ڵ��� 40ms
			{     	
				if(key_scan_func.double_click_flag==3)//˫����ʱ��־Ϊ3
				{               
					 key_code = keyBack | KEY_DOUBLE;                   //����Ϊ˫����		
				}
				else//˫����ʱ��־��Ϊ3
				{                                    
			 		 key_code = keyBack | KEY_SHORT_UP;       //����Ϊ�̰�����	 
				}
				
				key_scan_func.double_click_flag=0;             //˫����ʱ��־Ϊ0
			}
			key_scan_func.key_press_time = 0;             //������ѹ��ʱΪ0
			key_scan_func.key_up_time = 0xfff;            //��������ʱ��Ϊ4095
			key_scan_func.key_up_value = key_value;       //��������ֵΪ��õİ���ֵ
			keyBack = 0;
		}
		else
		{                                          		  //���簴�����ϼ�ʱ����95ms
			key_scan_func.double_click_flag=0;            //˫����ʱ��־����0
			key_scan_func.key_press_time = 0;             //�������¼�ʱΪ0
			key_scan_func.key_up_time = 0xfff;            //��������ʱ��Ϊ4095
		} 	 		
	}
	else
	{                                            //����ֵ��Ϊ0���а�������
		key_scan_func.key_up_time = 0;           //�������ϼ�ʱΪ0
		if(++key_scan_func.key_press_time > 500) key_scan_func.key_press_time = 500;      //����ʱ��++ ����ʱ�����2.5�룬����ʱ�����500
		if(key_scan_func.double_click_flag==2)//����˫����ʱ��־����2
		{                    
			if(key_scan_func.key_press_time == KEY_PRESS_SHORT_TIME)//KEY_PRESS_SHORT_TIME  //���簴��ʱ�����40ms
			{ 
				keyBack = key_value ;	                              //��ֵ���ص��ڰ���ֵ
				key_scan_func.double_click_flag=3;                    //˫����ʱ��־����3
			}
		}
		else
		{                                                   
			if(key_scan_func.key_press_time == KEY_PRESS_SHORT_TIME)  //KEY_PRESS_SHORT_TIME      //���簴��ʱ�����40ms
			{ 
			    key_code = key_value | KEY_SHORT_DOWN;                //����ֵ���� ����ֵ �̰�
			   
				key_scan_func.double_click_flag = 1;                  //��������
				keyBack = key_value;                                  //��������ֵΪ����ֵ	
			}
		    else if(key_scan_func.key_press_time == KEY_PRESS_LONG_TIME)//���簴������ʱ�����1��
			{   
				key_code = key_value | KEY_LONG_DOWN;                   //��������ڰ���ֵ ����
				keyBack = key_value;                                    //�������� ���� ����ֵ
			}
			else if(key_scan_func.key_press_time == KEY_CONTINUE_TIME)//���簴������ʱ�����1.1��
			{      
				key_scan_func.key_press_time = KEY_PRESS_LONG_TIME;     //��������ʱ�����1��
				key_code = key_value | KEY_HOLD;                        //��������� ����ֵ ����
				keyBack = key_value;                                    //��ֵ���� ���� ����ֵ
			}
	  	}
	}
	
	if(value != key_scan_func.keyPreValue)//�������°���ֵ�������ϴΰ�����ֵ
	{        
		if(key_scan_func.double_click_flag==0)//����˫����ʱ��־����0
		{      
     		 key_scan_func.keyPreValue = value;      //�ϴε�ֵ����Ϊ�˴ε�ֵ
		
	 		 key_scan_func.key_press_time = 0;         //������ѹ���ܵ���0
	 		 key_scan_func.key_up_time = 0;            //��������ʱ�����0
		}
	} 
	
	if(key_code != 0)//�����벻����0
	{                
		Key.KeyUserVlaue = key_code;
	}
}

