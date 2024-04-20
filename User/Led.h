#ifndef __LED_H__
#define __LED_H__



typedef struct _DRIVER
{
  unsigned short 
    wEndLum[3],
	  wNowLum[3],
	  wLumCount[3],
	  wDmxValue[3],
		wNowSpeed[3];



} DRIVER, *P_DRIVER;


extern DRIVER Driver;

//Çý¶¯---------------------------------------------------------
void LedDriver(void);

#endif // __LED_H__

