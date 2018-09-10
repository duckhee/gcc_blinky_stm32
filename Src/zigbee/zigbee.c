#include "zigbee.h"

#ifdef  BOARD_DEF_MANGO_Z1

ZIGBEE_DEF void Zigbee_Test(void)
{
    DEBUG_MSG_FUNC_START;
    SPIx_Init();

    halRfInit();

    printf("chip ID : 0x%x\r\n", halRfChipId());
    printf("version : 0x%x\r\n", halRfGetChipVer());
}

#endif