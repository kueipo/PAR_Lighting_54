#ifndef _KEY_FUNC_H
#define _KEY_FUNC_H
#include "py32f0xx_hal.h"

/*�Զ���ṹ��*/
typedef struct
{
  uint16_t State;  
  uint16_t KeyUserVlaue;
  uint8_t  KeyStateBit;
  uint16_t Dmx512Address;
	
}KeyTypeDef;


extern KeyTypeDef Key;


typedef struct{
  uint8_t keyScanStep;
  uint16_t key_up_time;
  uint16_t key_press_time;
  
  uint16_t key_press_time_double;
  uint16_t key_up_value;
  uint16_t scan_time;
  uint8_t double_click_flag;
  
  uint8_t keyPreValue;
}_key_func;



#define  KEY1 0x01
#define  KEY2 0x02
#define  KEY3 0x04
#define  KEY4 0x08

#define  KEY_SHORT_DOWN        0x000       //�̰���
#define  KEY_SHORT_UP          0x800       //�̰���
#define  KEY_HOLD              0xE00       //����
#define  KEY_LONG_DOWN         0xA00       //������
#define  KEY_LONG_UP           0xC00       //������
#define  KEY_DOUBLE            0x1800      //˫��

#define  c_KeyValue_Nothing       0                         //�ް���
#define  c_KeyValue_Menu         (KEY1 | KEY_SHORT_DOWN)    //�˵�����ֵ  
#define  c_KeyValue_Plus         (KEY2 | KEY_SHORT_DOWN)    //�Ӷ̰���ֵ
#define  c_KeyValue_Plus_Hold    (KEY2 | KEY_HOLD)          //�ӳ�����ֵ
#define  c_KeyValue_Down         (KEY3 | KEY_SHORT_DOWN)    //���̰���ֵ 
#define  c_KeyValue_Down_Hold    (KEY3 | KEY_HOLD)          //��������ֵ
#define  c_KeyValue_Enter        (KEY4 | KEY_SHORT_DOWN)    //ȷ������ֵ

extern void KeyScan(uint8_t value);
extern void KeyFunc(uint16_t KeyCode);
extern void Bottom_KeyFunc(void);

#endif /*_KEY_FUNC_H*/
