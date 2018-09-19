#ifndef __I2C_DRIVER_H__
#define __I2C_DRIVER_H__

#include "hw_config.h"

#ifdef I2C_DRIVER_LOCAL
#define I2C_DRIVER_DEF
#else
#define I2C_DRIVER_DEF            extern
#endif

I2C_DRIVER_DEF void i2c1_driver_Initialize (void);
I2C_DRIVER_DEF void i2c1_1byte_addr7_write_cmd(uint8_t Devcie_Addr, uint16_t cmd);
I2C_DRIVER_DEF void i2c1_1byte_addr7_write(uint8_t Device_Addr, uint16_t WriteAddr, uint8_t* pBuffer);
I2C_DRIVER_DEF void i2c1_addr_7_cmd_read(uint8_t Device_Addr, uint16_t cmd, uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumByteToRead);
I2C_DRIVER_DEF void i2c1_addr7_read(uint8_t Device_Addr, uint16_t ReadAddr, uint8_t* pBuffer, uint16_t NumByteToRead);

#endif