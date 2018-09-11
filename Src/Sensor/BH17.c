#define BH17_LOCAL

#include "BH17.h"


bool UartQueue_Serial_Is_Empty(void);
uint16_t UartQueue_Serial_DeQueue(void);

extern uint8_t Buffer_Rx1[];
extern uint8_t Buffer_Tx1[];


#define AL_BH17_SLAVE_ADDRESS     0x23 /* Slave Address : "010 0011" */




