#define LPS25_LOCAL

#include "LPS25.c"

bool UartQueue_Serial_Is_Empty(void);
uint16_t UartQueue_Serial_DeQueue(void);

extern uint8_t Buffer_Rx1[];
extern uint8_t Buffer_Tx1[];

LPS25_DEF uint8_t SENSOR_LPS_Read_Bytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);
LPS25_DEF int8_t SENSPR_LPS_Write_Bytes(uint8_t devAddr, uint8_t regAddr, uint8_t lenght, uint8_t *data);
LPS25_DEF void LPS25H_Init(void);
LPS25_DEF uint8_t LPS25H_ReadID(void);
LPS25_DEF void LPS25H_RebootCmd(void);
LPS25_DEF void LPS25H_GetPressure(float* pfData);
LPS25_DEF void LPS25H_GetTemperature(float* pfData);
LPS25_DEF void LPS25H_PowerOff(void);
LPS25_DEF void LPS25H_SlaveAddrRemap(uint8_t);
LPS25_DEF void Test_Sensor_LPS25H(void);
/* Interrupt Configuration Functions */
LPS25_DEF void LPS25H_INT1InterruptConfig(uint16_t Int1Config);
LPS25_DEF void LPS25H_EnableIT(void);
LPS25_DEF void LPS25H_DisableIT(void);
 
/* Pressure sensor driver structure */
//extern PRESSURE_DrvTypeDef LPS25HDrv;
 
/* Pressure sensor IO functions */
LPS25_DEF void PRESSURE_IO_Init(void);
LPS25_DEF void PRESSURE_IO_DeInit(void);
LPS25_DEF void PRESSURE_IO_Write(uint8_t* pBuffer, uint8_t DeviceAddr, uint8_t WriteAddr,
                       uint16_t NumByteToWrite);
LPS25_DEF void PRESSURE_IO_Read(uint8_t* pBuffer, uint8_t DeviceAddr,
                      uint8_t RegisterAddr, uint16_t NumByteToRead);
