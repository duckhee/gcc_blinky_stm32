#ifndef __GPIO_JTAG_H__
#define __GPIO_JTAG_H__

#include "hw_config.h"

#define GPIO_JTAG            GPIOA

#define GPIO_JTAG_TMS_PIN               GPIO_Pin_13
#define GPIO_JTAG_TCK_PIN               GPIO_Pin_14
#define GPIO_PORTSOURCE_JTAG_TCK  GPIO_PortSourceGPIOA
#define GPIO_PINSOURCE_JTAG_TCK   

#ifdef GPIO_JTAG_LOCAL
#define JTAG_DEF 
#else
#define JTAG_DEF            extern
#endif

JTAG_DEF void JTAG_Init(void);
JTAG_DEF void JTAG_TMS_Toggle_Red(void);
JTAG_DEF void Process_UseGPIO_JtagPort(void);



#endif
