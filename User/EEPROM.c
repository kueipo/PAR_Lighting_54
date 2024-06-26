#include "EEPROM.h"
#include "KeyFunc.h"
#include "LEDFunc.h"

#define FLASH_USER_START_ADDR      0x08004000                   /*0x08002000*/
#define c_Set_EEPROM_Size  11  


uint32_t EEPROM_UserSet_Data[c_Set_EEPROM_Size];                    

const uint32_t EEPROM_UserSetInit_Data[c_Set_EEPROM_Size] = {
  0x01,        //DMX512地址
  0x00,        //红色调光亮度
  0x00,        //绿色调光亮度
  0x00,        //蓝色调光亮度
  0x01,        //频闪速度
  0x01,        //单色模式颜色
  0x01,        //七彩跳变速度
  0x01,        //七彩渐变速度
  0x01,        //七彩脉变速度
  0x01,        //声音控制模式
	0x01,        //LED控制模式
};

/**
  * @brief  擦除FLASH
  * @param  无
  * @retval 无
  */
static void APP_FlashErase(void)
{
  uint32_t SECTORError = 0;
  FLASH_EraseInitTypeDef EraseInitStruct;

  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_SECTORERASE;                                       /*擦写类型FLASH_TYPEERASE_PAGEERASE=Page擦, FLASH_TYPEERASE_SECTORERASE=Sector擦*/
  EraseInitStruct.SectorAddress = FLASH_USER_START_ADDR;                                           /*擦写起始地址*/
  EraseInitStruct.NbSectors  = 1;                                                                  /*需要擦写的扇区数量*/
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)                                 /*执行sector擦除,SECTORError返回擦写错误的sector,返回0xFFFFFFFF,表示擦写成功*/
  {
    Error_Handler();
  }
}

/**
  * @brief  写FLASH
  * @param  无
  * @retval 无
  */
static void APP_FlashProgram(uint32_t* Databuf)
{
  uint32_t flash_program_start = FLASH_USER_START_ADDR ;                                            /*flash写起始地址*/
  uint32_t flash_program_end = (FLASH_USER_START_ADDR + sizeof(Databuf));                              /*flash写结束地址*/
  uint32_t *src = (uint32_t *)Databuf;                                                                 /*数组指针*/

  while (flash_program_start < flash_program_end)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_PAGE, flash_program_start, src) == HAL_OK)              /*执行Program*/
    {                                                                                               
      flash_program_start += FLASH_PAGE_SIZE;                                                       /*flash起始指针指向第一个page*/
      src += FLASH_PAGE_SIZE / 4;                                                                   /*更新数据指针*/
    }                                                                                               
  }
}

/**
  * @brief  数据写入EEPROM
  * @param  无
  * @retval 无
  */
void WriteEEPROM(uint32_t* Databuf)
{
  /*解锁FLASH*/
  HAL_FLASH_Unlock();
  /*擦除FLASH*/
  APP_FlashErase();
  /*写FLASH*/
  APP_FlashProgram(Databuf);
  /*锁定FLASH*/
  HAL_FLASH_Lock();
}

/**
  * @brief  从EEPROM读出数据
  * @param  无
  * @retval 无
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
  * @brief  用户数据初始化(读EEPROM)
  * @param  无
  * @retval 无
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
  * @brief  将用户数据写入EEPROM
  * @param  无
  * @retval 无
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

