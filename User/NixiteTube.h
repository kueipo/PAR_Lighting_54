#ifndef __NIXITE_TUBE__H
#define __NIXITE_TUBE__H
#include "py32f0xx_hal.h"

/*自定义结构体*/
typedef struct
{
  uint8_t DisplayBuf[6];
	
}NixieTubeTypeDef;

extern NixieTubeTypeDef NixieTube;


    

extern uint8_t RxDisplayBuf[9];
extern uint8_t LedDisplayBuf[7];
extern void LED_Scan(uint8_t *buf);
extern void NixieTubeDisplay(void);

#endif /*__NIXITE_TUBE__H*/
