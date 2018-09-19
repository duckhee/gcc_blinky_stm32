#ifndef __SHT20_H__
#define __SHT20_H__

#include "hw_config.h"


#ifdef SHT20_LOCAL
#define SHT20_DEF
#else
#define SHT20_DEF              extern
#endif


SHT20_DEF void SHT2x_test(void);
SHT20_DEF uint8_t SHT2x_SoftReset(void);
SHT20_DEF uint8_t SHT2x_CheckCrc(uint8_t data[], uint8_t nbrOfBytes, uint8_t checksum);
SHT20_DEF uint8_t SHT2x_ReadUserRegister(uint8_t *pRegisterValue);
SHT20_DEF uint8_t SHT2x_GetSerialNumber(uint8_t u8SerialNumber[]);
SHT20_DEF uint8_t SHT2x_WriteUserRegister(uint8_t *pRegisterValue);
SHT20_DEF uint8_t SHT2x_MeasureHM(uint8_t eSHT2xMeasureType, uint8_t *pMeasurand);
SHT20_DEF uint8_t SHT2x_MeasurePoll(uint8_t eSHT2xMeasureType, uint8_t *pMeasurand);
SHT20_DEF float SHT2x_CalcRH(uint8_t *psRH);
SHT20_DEF float SHT2x_CalcTemperatureC(uint8_t *psT);


#endif