#include "NixiteTube_Driver.h"
#include "BspDriver_GPIO.h"
#include "py32f0xx_ll_gpio.h"
#include "KeyFunc.h"


static void SEG_GPIO_CofigFloat(void);
static void SEG1_GPIO_CofigOutput(uint8_t state);
static void SEG2_GPIO_CofigOutput(uint8_t state);
static void SEG3_GPIO_CofigOutput(uint8_t state);
static void SEG4_GPIO_CofigOutput(uint8_t state);
static void SEG5_GPIO_CofigOutput(uint8_t state);
static void SEG6_GPIO_CofigOutput(uint8_t state);
static uint8_t KEY1_GPIO_StateGet(void);
static uint8_t KEY2_GPIO_StateGet(void);
static uint8_t KEY3_GPIO_StateGet(void);
static uint8_t KEY4_GPIO_StateGet(void);
static void KEY_GPIO_IntputPullUp(void);

/**
 * @brief  LED����ɨ��
 * @param  *buf 8λ��ʾ����
 * @retval ��
 */
void LED_Scan(uint8_t *buf)
{
  static uint8_t ScanNum=0;

  switch(ScanNum)
  {
    case 0:
    {
      SEG_GPIO_CofigFloat();
      if(buf[0] == 0)break;
      if(buf[0]&LED_BIT_2)SEG2_LOW();
      if(buf[0]&LED_BIT_3)SEG3_LOW();
      if(buf[0]&LED_BIT_4)SEG4_LOW();
      if(buf[0]&LED_BIT_5)SEG5_LOW();
      if(buf[0]&LED_BIT_6)SEG6_LOW();
      if(buf[0])SEG1_HIGHT();
    }
    break;

    case 1:
    {
      SEG_GPIO_CofigFloat();
      if(buf[1] == 0)break;
      if(buf[1]&LED_BIT_1)SEG1_LOW();
      if(buf[1]&LED_BIT_3)SEG3_LOW();
      if(buf[1]&LED_BIT_4)SEG4_LOW();
      if(buf[1]&LED_BIT_5)SEG5_LOW();
      if(buf[1]&LED_BIT_6)SEG6_LOW();
	  if(buf[1])SEG2_HIGHT();
    }
    break;

    case 2:
    {
      SEG_GPIO_CofigFloat();
      if(buf[2] == 0)break;
      if(buf[2]&LED_BIT_1)SEG1_LOW();
      if(buf[2]&LED_BIT_2)SEG2_LOW();
      if(buf[2]&LED_BIT_4)SEG4_LOW();
      if(buf[2]&LED_BIT_5)SEG5_LOW();
      if(buf[2]&LED_BIT_6)SEG6_LOW();
      if(buf[2])SEG3_HIGHT();
    }
    break;

    case 3:
    {
      SEG_GPIO_CofigFloat();
      if(buf[3] == 0)break;
      if(buf[3]&LED_BIT_1)SEG1_LOW();
      if(buf[3]&LED_BIT_2)SEG2_LOW();
      if(buf[3]&LED_BIT_3)SEG3_LOW();
      if(buf[3]&LED_BIT_5)SEG5_LOW();
      if(buf[3]&LED_BIT_6)SEG6_LOW();
      if(buf[3])SEG4_HIGHT();
    }
    break;

    case 4:
    {
      SEG_GPIO_CofigFloat();
      if(buf[4] == 0)break;
      if(buf[4]&LED_BIT_1)SEG1_LOW();
      if(buf[4]&LED_BIT_2)SEG2_LOW();
      if(buf[4]&LED_BIT_3)SEG3_LOW();
      if(buf[4]&LED_BIT_4)SEG4_LOW();
      if(buf[4]&LED_BIT_6)SEG6_LOW();
      if(buf[4])SEG5_HIGHT();
    }
    break;

    case 5:
    {
      SEG_GPIO_CofigFloat();
      if(buf[5] == 0)break;
      if(buf[5]&LED_BIT_1)SEG1_LOW();
      if(buf[5]&LED_BIT_2)SEG2_LOW();
      if(buf[5]&LED_BIT_3)SEG3_LOW();
      if(buf[5]&LED_BIT_4)SEG4_LOW();
      if(buf[5]&LED_BIT_5)SEG5_LOW();
      if(buf[5])SEG6_HIGHT();
    }
    break;

    case 6:
		KEY_GPIO_IntputPullUp();
		break;

    case 7:
    {
      if(!KEY1_GPIO_StateGet())
        Key.State |= KEY1;
      else
        Key.State &= ~KEY1;

      if(!KEY2_GPIO_StateGet())
        Key.State |= KEY2;
      else
        Key.State &= ~KEY2;

      if(!KEY3_GPIO_StateGet())
        Key.State = KEY3;
      else
        Key.State &= ~KEY3;

      if(!KEY4_GPIO_StateGet())
        Key.State = KEY4;
      else
        Key.State &= ~KEY4;
    }
    break;

    default:break;
  }

  ScanNum++;
	if(ScanNum > 7)
		ScanNum = 0;
}


/*�����1��������*/
const uint8_t Number1[10][6] = {
  {0x20,0x01,0x21,0x01,0x01,0x00},    //0
  {0x00,0x01,0x01,0x00,0x00,0x00},    //1
  {0x20,0x01,0x00,0x01,0x01,0x01},    //2
  {0x20,0x01,0x01,0x01,0x00,0x01},    //3
  {0x00,0x01,0x21,0x00,0x00,0x01},    //4
  {0x20,0x00,0x21,0x01,0x00,0x01},    //5
  {0x20,0x00,0x21,0x01,0x01,0x01},    //6
  {0x20,0x01,0x01,0x00,0x00,0x00},    //7
  {0x20,0x01,0x21,0x01,0x01,0x01},    //8
  {0x20,0x01,0x21,0x01,0x00,0x01},    //9
};

/*�����2��������*/
const uint8_t Number2[10][6] = {
  {0x08,0x08,0x0A,0x00,0x08,0x08},    //0
  {0x00,0x08,0x08,0x00,0x00,0x00},    //1
  {0x0A,0x08,0x00,0x00,0x08,0x08},    //2
  {0x0A,0x08,0x08,0x00,0x08,0x00},    //3
  {0x02,0x08,0x0A,0x00,0x00,0x00},    //4
  {0x0A,0x00,0x0A,0x00,0x08,0x00},    //5
  {0x0A,0x00,0x0A,0x00,0x08,0x08},    //6
  {0x08,0x08,0x08,0x00,0x00,0x00},    //7
  {0x0A,0x08,0x0A,0x00,0x08,0x08},    //8
  {0x0A,0x08,0x0A,0x00,0x08,0x00},    //9
};

/*�����3��������*/
const uint8_t Number3[10][6] = {
  {0x10,0x10,0x10,0x02,0x02,0x02},    //0
  {0x00,0x00,0x00,0x00,0x02,0x02},    //1
  {0x00,0x10,0x10,0x12,0x02,0x00},    //2
  {0x00,0x10,0x00,0x12,0x02,0x02},    //3
  {0x10,0x00,0x00,0x10,0x02,0x02},    //4
  {0x10,0x10,0x00,0x12,0x00,0x02},    //5
  {0x10,0x10,0x10,0x12,0x00,0x02},    //6
  {0x00,0x00,0x00,0x02,0x02,0x02},    //7
  {0x10,0x10,0x10,0x12,0x02,0x02},    //8
  {0x10,0x10,0x00,0x12,0x02,0x02},    //9
};

/*�����4��������*/
const uint8_t Number4[10][6] = {
  {0x04,0x04,0x00,0x04,0x04,0x14},    //0
  {0x00,0x04,0x00,0x04,0x00,0x00},    //1
  {0x04,0x24,0x00,0x00,0x04,0x10},    //2
  {0x00,0x24,0x00,0x04,0x04,0x10},    //3
  {0x00,0x24,0x00,0x04,0x00,0x04},    //4
  {0x00,0x20,0x00,0x04,0x04,0x14},    //5
  {0x04,0x20,0x00,0x04,0x04,0x14},    //6
  {0x00,0x04,0x00,0x04,0x00,0x10},    //7
  {0x04,0x24,0x00,0x04,0x04,0x14},    //8
  {0x00,0x24,0x00,0x04,0x04,0x14},    //9
};


/**
	* @brief  SEG����Ϊ��������
  * @param  ��
  * @retval ��
  */
static void SEG_GPIO_CofigFloat(void)
{
  /*SEG1*/
  LL_GPIO_SetPinMode(SEG1_GPIO_PORT, SEG1_GPIO_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(SEG1_GPIO_PORT, SEG1_GPIO_PIN, LL_GPIO_PULL_NO);
  /*SEG2*/
  LL_GPIO_SetPinMode(SEG2_GPIO_PORT, SEG2_GPIO_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(SEG2_GPIO_PORT, SEG2_GPIO_PIN, LL_GPIO_PULL_NO);
  /*SEG3*/
  LL_GPIO_SetPinMode(SEG3_GPIO_PORT, SEG3_GPIO_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(SEG3_GPIO_PORT, SEG3_GPIO_PIN, LL_GPIO_PULL_NO);
  /*SEG4*/
	LL_GPIO_SetPinMode(SEG4_GPIO_PORT, SEG4_GPIO_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(SEG4_GPIO_PORT, SEG4_GPIO_PIN, LL_GPIO_PULL_NO);
  /*SEG5*/
	LL_GPIO_SetPinMode(SEG5_GPIO_PORT, SEG5_GPIO_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(SEG5_GPIO_PORT, SEG5_GPIO_PIN, LL_GPIO_PULL_NO);
  /*SEG6*/
	LL_GPIO_SetPinMode(SEG6_GPIO_PORT, SEG6_GPIO_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(SEG6_GPIO_PORT, SEG6_GPIO_PIN, LL_GPIO_PULL_NO);
}

/**
	* @brief  SEG1����Ϊ���
  * @param  state
  * @arg  	0 or 1
  * @retval ��
  */
static void SEG1_GPIO_CofigOutput(uint8_t state)
{
	LL_GPIO_SetPinMode(SEG1_GPIO_PORT, SEG1_GPIO_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(SEG1_GPIO_PORT, SEG1_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);

  if(state)
    LL_GPIO_SetOutputPin(SEG1_GPIO_PORT, SEG1_GPIO_PIN);                 /* SEG1����� */
  else
    LL_GPIO_ResetOutputPin(SEG1_GPIO_PORT,SEG1_GPIO_PIN);                /* SEG1����� */
}

/**
	* @brief  SEG2����Ϊ���
  * @param  state
  * @arg  	0 or 1
  * @retval ��
  */
static void SEG2_GPIO_CofigOutput(uint8_t state)
{
	LL_GPIO_SetPinMode(SEG2_GPIO_PORT, SEG2_GPIO_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(SEG2_GPIO_PORT, SEG2_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);

  if(state)
    LL_GPIO_SetOutputPin(SEG2_GPIO_PORT, SEG2_GPIO_PIN);                 /* SEG2����� */
  else
    LL_GPIO_ResetOutputPin(SEG2_GPIO_PORT,SEG2_GPIO_PIN);                /* SEG2����� */
}

/**
	* @brief  SEG3����Ϊ���
  * @param  state
  * @arg  	0 or 1
  * @retval ��
  */
static void SEG3_GPIO_CofigOutput(uint8_t state)
{
	LL_GPIO_SetPinMode(SEG3_GPIO_PORT, SEG3_GPIO_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(SEG3_GPIO_PORT, SEG3_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);

  if(state)
    LL_GPIO_SetOutputPin(SEG3_GPIO_PORT, SEG3_GPIO_PIN);                 /* SEG3����� */
  else
    LL_GPIO_ResetOutputPin(SEG3_GPIO_PORT,SEG3_GPIO_PIN);                /* SEG3����� */
}

/**
	* @brief  SEG4����Ϊ���
  * @param  state
  * @arg  	0 or 1
  * @retval ��
  */
static void SEG4_GPIO_CofigOutput(uint8_t state)
{
	LL_GPIO_SetPinMode(SEG4_GPIO_PORT, SEG4_GPIO_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(SEG4_GPIO_PORT, SEG4_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);

  if(state)
    LL_GPIO_SetOutputPin(SEG4_GPIO_PORT, SEG4_GPIO_PIN);                 /* SEG4����� */
  else
    LL_GPIO_ResetOutputPin(SEG4_GPIO_PORT,SEG4_GPIO_PIN);                /* SEG4����� */
}

/**
	* @brief  SEG5����Ϊ���
  * @param  state
  * @arg  	0 or 1
  * @retval ��
  */
static void SEG5_GPIO_CofigOutput(uint8_t state)
{
	LL_GPIO_SetPinMode(SEG5_GPIO_PORT, SEG5_GPIO_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(SEG5_GPIO_PORT, SEG5_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  if(state)
    LL_GPIO_SetOutputPin(SEG5_GPIO_PORT, SEG5_GPIO_PIN);                 /* SEG5����� */
  else
    LL_GPIO_ResetOutputPin(SEG5_GPIO_PORT,SEG5_GPIO_PIN);                /* SEG5����� */
}

/**
	* @brief  SEG6����Ϊ���
  * @param  state
  * @arg  	0 or 1��
  * @retval ��
  */
static void SEG6_GPIO_CofigOutput(uint8_t state)
{
	LL_GPIO_SetPinMode(SEG6_GPIO_PORT, SEG6_GPIO_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(SEG6_GPIO_PORT, SEG6_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);

  if(state)
    LL_GPIO_SetOutputPin(SEG6_GPIO_PORT, SEG6_GPIO_PIN);                 /* SEG6����� */
  else
    LL_GPIO_ResetOutputPin(SEG6_GPIO_PORT,SEG6_GPIO_PIN);                /* SEG6����� */
}

/**
	* @brief  ������������Ϊ��������
  * @param  ��
  * @retval ��
  */
static void KEY_GPIO_IntputPullUp(void)
{
  //ǰ4��IO����Ϊ�����������ڼ��
  LL_GPIO_SetPinMode(SEG1_GPIO_PORT, SEG1_GPIO_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(SEG1_GPIO_PORT, SEG1_GPIO_PIN, LL_GPIO_PULL_UP);

  LL_GPIO_SetPinMode(SEG2_GPIO_PORT, SEG2_GPIO_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(SEG2_GPIO_PORT, SEG2_GPIO_PIN, LL_GPIO_PULL_UP);

  LL_GPIO_SetPinMode(SEG3_GPIO_PORT, SEG3_GPIO_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(SEG3_GPIO_PORT, SEG3_GPIO_PIN, LL_GPIO_PULL_UP);

  LL_GPIO_SetPinMode(SEG4_GPIO_PORT, SEG4_GPIO_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(SEG4_GPIO_PORT, SEG4_GPIO_PIN, LL_GPIO_PULL_UP);

  //������IO�����ް�������Ϊ��������
  /*SEG5*/
	LL_GPIO_SetPinMode(SEG5_GPIO_PORT, SEG5_GPIO_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(SEG5_GPIO_PORT, SEG5_GPIO_PIN, LL_GPIO_PULL_NO);
  /*SEG6*/
	LL_GPIO_SetPinMode(SEG6_GPIO_PORT, SEG6_GPIO_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(SEG6_GPIO_PORT, SEG6_GPIO_PIN, LL_GPIO_PULL_NO);
}

/**
	* @brief  ��ⰴ��1 IO��״̬
  * @param  ��
  * @retval ��
  */
static uint8_t KEY1_GPIO_StateGet(void)
{
  return(LL_GPIO_IsInputPinSet(SEG4_GPIO_PORT,SEG4_GPIO_PIN));
}

/**
	* @brief  ��ⰴ��2 IO��״̬
  * @param  ��
  * @retval ��
  */
static uint8_t KEY2_GPIO_StateGet(void)
{
  return(LL_GPIO_IsInputPinSet(SEG3_GPIO_PORT,SEG3_GPIO_PIN));
}

/**
	* @brief  ��ⰴ��3 IO��״̬
  * @param  ��
  * @retval ��
  */
static uint8_t KEY3_GPIO_StateGet(void)
{
  return(LL_GPIO_IsInputPinSet(SEG2_GPIO_PORT,SEG2_GPIO_PIN));
}

/**
	* @brief  ��ⰴ��4 IO��״̬
  * @param  ��
  * @retval ��
  */
static uint8_t KEY4_GPIO_StateGet(void)
{
  return(LL_GPIO_IsInputPinSet(SEG1_GPIO_PORT,SEG1_GPIO_PIN));
}

