#include "EEPROM.h"
#include "KeyFunc.h"
#include "LEDFunc.h"

#define FLASH_USER_START_ADDR      0x08004000                   /*0x08002000*/
#define c_Set_EEPROM_Size  11  


uint32_t EEPROM_UserSet_Data[c_Set_EEPROM_Size];                    

const uint32_t EEPROM_UserSetInit_Data[c_Set_EEPROM_Size] = {
  0x01,        //DMX512��ַ
  0x00,        //��ɫ��������
  0x00,        //��ɫ��������
  0x00,        //��ɫ��������
  0x01,        //Ƶ���ٶ�
  0x01,        //��ɫģʽ��ɫ
  0x01,        //�߲������ٶ�
  0x01,        //�߲ʽ����ٶ�
  0x01,        //�߲������ٶ�
  0x01,        //��������ģʽ
	0x01,        //LED����ģʽ
};

/**
  * @brief  ����FLASH
  * @param  ��
  * @retval ��
  */
static void APP_FlashErase(void)
{
  uint32_t SECTORError = 0;
  FLASH_EraseInitTypeDef EraseInitStruct;

  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_SECTORERASE;                                       /*��д����FLASH_TYPEERASE_PAGEERASE=Page��, FLASH_TYPEERASE_SECTORERASE=Sector��*/
  EraseInitStruct.SectorAddress = FLASH_USER_START_ADDR;                                           /*��д��ʼ��ַ*/
  EraseInitStruct.NbSectors  = 1;                                                                  /*��Ҫ��д����������*/
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)                                 /*ִ��sector����,SECTORError���ز�д�����sector,����0xFFFFFFFF,��ʾ��д�ɹ�*/
  {
    Error_Handler();
  }
}

/**
  * @brief  дFLASH
  * @param  ��
  * @retval ��
  */
static void APP_FlashProgram(uint32_t* Databuf)
{
  uint32_t flash_program_start = FLASH_USER_START_ADDR ;                                            /*flashд��ʼ��ַ*/
  uint32_t flash_program_end = (FLASH_USER_START_ADDR + sizeof(Databuf));                              /*flashд������ַ*/
  uint32_t *src = (uint32_t *)Databuf;                                                                 /*����ָ��*/

  while (flash_program_start < flash_program_end)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_PAGE, flash_program_start, src) == HAL_OK)              /*ִ��Program*/
    {                                                                                               
      flash_program_start += FLASH_PAGE_SIZE;                                                       /*flash��ʼָ��ָ���һ��page*/
      src += FLASH_PAGE_SIZE / 4;                                                                   /*��������ָ��*/
    }                                                                                               
  }
}

/**
  * @brief  ����д��EEPROM
  * @param  ��
  * @retval ��
  */
void WriteEEPROM(uint32_t* Databuf)
{
  /*����FLASH*/
  HAL_FLASH_Unlock();
  /*����FLASH*/
  APP_FlashErase();
  /*дFLASH*/
  APP_FlashProgram(Databuf);
  /*����FLASH*/
  HAL_FLASH_Lock();
}

/**
  * @brief  ��EEPROM��������
  * @param  ��
  * @retval ��
  */
void ReadUserSetData(void)
{
	uint32_t addr = 0;

	while (addr < sizeof(EEPROM_UserSet_Data))
	{
		EEPROM_UserSet_Data[addr/4] = HW32_REG(FLASH_USER_START_ADDR + addr);
		addr += 4; 
	}
//  Databuf[0] = HW32_REG(FLASH_USER_START_ADDR);
//  Databuf[1] = HW32_REG(FLASH_USER_START_ADDR+4);
//  Databuf[2] = HW32_REG(FLASH_USER_START_ADDR+8);
//  Databuf[3] = HW32_REG(FLASH_USER_START_ADDR+12);
//  Databuf[4] = HW32_REG(FLASH_USER_START_ADDR+16);
//  Databuf[5] = HW32_REG(FLASH_USER_START_ADDR+20);
//  Databuf[6] = HW32_REG(FLASH_USER_START_ADDR+24);
//  Databuf[7] = HW32_REG(FLASH_USER_START_ADDR+28);
//  Databuf[8] = HW32_REG(FLASH_USER_START_ADDR+32);
//  Databuf[9] = HW32_REG(FLASH_USER_START_ADDR+36);
//  Databuf[10] = HW32_REG(FLASH_USER_START_ADDR+40); 
//  Databuf[11] = HW32_REG(FLASH_USER_START_ADDR+44); 
}

 /**
  * @brief  �û����ݳ�ʼ��(��EEPROM)
  * @param  ��
  * @retval ��
  */
void UserSetInit(void)
{
	unsigned char i;
	ReadUserSetData();
	if(EEPROM_UserSet_Data[0] == 0x0000 || EEPROM_UserSet_Data[0] == 0xFFFF)
	{
		for(i=0;i<c_Set_EEPROM_Size;i++)
		{
		  EEPROM_UserSet_Data[i] = EEPROM_UserSetInit_Data[i];
		}
		WriteEEPROM(EEPROM_UserSet_Data);
	}
	Key.Dmx512Address     =  (uint8_t)EEPROM_UserSet_Data[0];
	LED.KeyRedLight       =  (uint8_t)EEPROM_UserSet_Data[1];
	LED.KeyGreenLight     =  (uint8_t)EEPROM_UserSet_Data[2];
	LED.KeyBlueLight      =  (uint8_t)EEPROM_UserSet_Data[3];
	LED.GlitterSpeed      =  (uint8_t)EEPROM_UserSet_Data[4];
	LED.OneColorMode      =  (uint8_t)EEPROM_UserSet_Data[5];
	LED.ColorJumpSpeed    =  (uint8_t)EEPROM_UserSet_Data[6];
	LED.ColorGradualSpeed =  (uint8_t)EEPROM_UserSet_Data[7];
	LED.ColorPulseSpeed   =  (uint8_t)EEPROM_UserSet_Data[8];
	LED.VioceCtrlMode     =  (uint8_t)EEPROM_UserSet_Data[9];
  
	LED.Mode              =  (uint8_t)EEPROM_UserSet_Data[10];//c_Mode_DMX512_4Chan;
	if((LED.Mode>=c_Mode_RedLight)
		&&(LED.Mode<=c_Mode_Glitter))
	{
		LED.RGB_ARR[LED_R] = LED.KeyRedLight;
		LED.RGB_ARR[LED_G] = LED.KeyGreenLight;
		LED.RGB_ARR[LED_B] = LED.KeyBlueLight;
	}
}
  
 /**
  * @brief  ���û�����д��EEPROM
  * @param  ��
  * @retval ��
  */
void WriteUserSetDataIntoEEPROM(void)
{
	EEPROM_UserSet_Data[0] = (uint32_t)Key.Dmx512Address;
	EEPROM_UserSet_Data[1] = (uint32_t)LED.KeyRedLight;
	EEPROM_UserSet_Data[2] = (uint32_t)LED.KeyGreenLight;
	EEPROM_UserSet_Data[3] = (uint32_t)LED.KeyBlueLight;
	EEPROM_UserSet_Data[4] = (uint32_t)LED.GlitterSpeed;
	EEPROM_UserSet_Data[5] = (uint32_t)LED.OneColorMode;
	EEPROM_UserSet_Data[6] = (uint32_t)LED.ColorJumpSpeed;
	EEPROM_UserSet_Data[7] = (uint32_t)LED.ColorGradualSpeed;
	EEPROM_UserSet_Data[8] = (uint32_t)LED.ColorPulseSpeed;
	EEPROM_UserSet_Data[9] = (uint32_t)LED.VioceCtrlMode;
	EEPROM_UserSet_Data[10] = LED.Mode;
	WriteEEPROM(EEPROM_UserSet_Data);
}
