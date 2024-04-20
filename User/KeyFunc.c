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
	{       //按键值为0
		if(++key_scan_func.key_up_time > 500) key_scan_func.key_up_time = 500;		//向上时间++ 假如扫键上时间大于2.5秒  扫键向上计时等于2.5秒
		if(key_scan_func.key_up_time < 16)//假如扫键向上计时小于80ms返回
		{                   
			return;
		}
		else if(key_scan_func.key_up_time < LOOSEN_TIME)//假如扫键向上计时小于45ms
		{          
			if(key_scan_func.double_click_flag==1)//按键
			{               				
				key_scan_func.key_press_time_double = key_scan_func.key_press_time;      //双击按键时间等于按键按下时间
				key_scan_func.key_press_time = 0;                  //按键按下时间等于0
				key_scan_func.double_click_flag=2;                 //双击计时标志为2
			}
		}
	 	else if(key_scan_func.key_up_time < LOOSEN_TIME+10)//假如扫键向上计时小于 95ms, 大于80ms
		{         
			if(key_scan_func.double_click_flag == 2)//假如双击标志为2
			{                   
				key_scan_func.key_press_time = key_scan_func.key_press_time_double;   //按键按下时间等于 双击按键时间
				key_scan_func.double_click_flag = 0;                    //双击计时标志为0
			}
			
			if(key_scan_func.key_press_time >= KEY_PRESS_LONG_TIME)//假如按键按下时间 大于等于 1秒
			{     	
				key_code = keyBack | KEY_LONG_UP;                       //长按键
				key_scan_func.double_click_flag=0;                      //双击计时标志为0
			} 
			else if(key_scan_func.key_press_time >= KEY_PRESS_SHORT_TIME)//假如按键按下时间 大于等于 40ms
			{     	
				if(key_scan_func.double_click_flag==3)//双击计时标志为3
				{               
					 key_code = keyBack | KEY_DOUBLE;                   //按键为双击键		
				}
				else//双击计时标志不为3
				{                                    
			 		 key_code = keyBack | KEY_SHORT_UP;       //按键为短按向上	 
				}
				
				key_scan_func.double_click_flag=0;             //双击计时标志为0
			}
			key_scan_func.key_press_time = 0;             //按键按压计时为0
			key_scan_func.key_up_time = 0xfff;            //按键向上时间为4095
			key_scan_func.key_up_value = key_value;       //按键向上值为测得的按键值
			keyBack = 0;
		}
		else
		{                                          		  //假如按键向上计时大于95ms
			key_scan_func.double_click_flag=0;            //双击计时标志等于0
			key_scan_func.key_press_time = 0;             //按键按下计时为0
			key_scan_func.key_up_time = 0xfff;            //按键向上时间为4095
		} 	 		
	}
	else
	{                                            //按键值不为0，有按键按下
		key_scan_func.key_up_time = 0;           //按键向上计时为0
		if(++key_scan_func.key_press_time > 500) key_scan_func.key_press_time = 500;      //按键时间++ 按键时间大于2.5秒，按键时间等于500
		if(key_scan_func.double_click_flag==2)//假如双击计时标志等于2
		{                    
			if(key_scan_func.key_press_time == KEY_PRESS_SHORT_TIME)//KEY_PRESS_SHORT_TIME  //假如按下时间等于40ms
			{ 
				keyBack = key_value ;	                              //键值返回等于按键值
				key_scan_func.double_click_flag=3;                    //双击计时标志等于3
			}
		}
		else
		{                                                   
			if(key_scan_func.key_press_time == KEY_PRESS_SHORT_TIME)  //KEY_PRESS_SHORT_TIME      //假如按下时间等于40ms
			{ 
			    key_code = key_value | KEY_SHORT_DOWN;                //按键值等于 按键值 短按
			   
				key_scan_func.double_click_flag = 1;                  //按键单击
				keyBack = key_value;                                  //按键返回值为按键值	
			}
		    else if(key_scan_func.key_press_time == KEY_PRESS_LONG_TIME)//假如按键按下时间等于1秒
			{   
				key_code = key_value | KEY_LONG_DOWN;                   //按键码等于按键值 长按
				keyBack = key_value;                                    //按键返回 等于 按键值
			}
			else if(key_scan_func.key_press_time == KEY_CONTINUE_TIME)//假如按键按下时间等于1.1秒
			{      
				key_scan_func.key_press_time = KEY_PRESS_LONG_TIME;     //按键下下时间等于1秒
				key_code = key_value | KEY_HOLD;                        //按键码等于 按键值 保持
				keyBack = key_value;                                    //键值返回 等于 按键值
			}
	  	}
	}
	
	if(value != key_scan_func.keyPreValue)//假如最新按键值不等于上次按键的值
	{        
		if(key_scan_func.double_click_flag==0)//假如双击计时标志等于0
		{      
     		 key_scan_func.keyPreValue = value;      //上次的值跟新为此次的值
		
	 		 key_scan_func.key_press_time = 0;         //按键按压功能等于0
	 		 key_scan_func.key_up_time = 0;            //按键向上时间等于0
		}
	} 
	
	if(key_code != 0)//按键码不等于0
	{                
		Key.KeyUserVlaue = key_code;
	}
}

