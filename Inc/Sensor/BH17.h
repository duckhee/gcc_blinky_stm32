#ifndef __BH17_H__
#define __BH17_H__

#ifdef __cplusplus
extern "C"{
#endif

    #include "hw_config.h"
    #include "stdio.h"
    #include "hw_type.h"

    #ifdef BH17_LOCAL
    #define BH17_DEF 
    #else
    #define BH17_DEF         extern
    #endif

    BH17_DEF void Test_Sensor_AL_BH17(void);
    BH17_DEF uint8_t SENSOR_AL_BH17_Read_Bytes(uint8_t devAddr, uint8_t length, uint8_t *data);
    BH17_DEF int8_t SENSOR_AL_BH17_Write_Bytes(uint8_t devAddr, uint8_t length, uint8_t *data);

    

#ifdef __cplusplus
}
#endif

#endif