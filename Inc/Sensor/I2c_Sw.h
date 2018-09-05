#ifndef __I2C_SW_H__
#define __I2C_SW_H__


#include "stm32f10x.h"
#include "stdio.h"


//include i2c_sw_c file header 
#include "hw_config.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "debug.h"


#ifdef I2C_SW_LOCAL
#define I2C_DEF
#else
#define I2C_DEF              extern
#endif

I2C_DEF void I2C_Send_Test(void);
I2C_DEF void I2C_Receive_Test(void);
I2C_DEF uint8_t SW_I2C_ReadVal_SDA(void);
I2C_DEF void SW_I2C_Write_Data(uint8_t data);
I2C_DEF uint8_t SW_I2C_Read_Data(void);
I2C_DEF uint8_t SW_I2C_WriteControl_8Bit(uint8_t IICID, uint8_t regaddr, uint8_t data);
I2C_DEF uint8_t SW_I2C_WriteControl_16Bit(uint8_t IICID, uint8_t regaddr, uint16_t data);
I2C_DEF uint8_t SW_I2C_ReadControl_8Bit(uint8_t IICID, uint8_t regaddr);
I2C_DEF uint16_t SW_I2C_ReadControl_16Bit(uint8_t IICID, uint8_t regaddr);

#endif