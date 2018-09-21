#ifndef __UART_QUEUE_H
#define __UART_QUEUE_H

/* Includes */

#include "hw_config.h"
#include "global_types.h"
/* Exported constants */

/* Exported functions */

// UART Queue for Comm

void UartQueue_Comm_Initialize(void);
bool UartQueue_Comm_Is_Empty(void);
void UartQueue_Comm_EnQueue(uint16_t data);
uint16_t UartQueue_Comm_DeQueue(void);

// UART Queue for Serial

bool UartQueue_Serial_Is_Empty(void);
void UartQueue_Serial_EnQueue(uint16_t data);
uint16_t UartQueue_Serial_DeQueue(void);

#endif /* __UART_QUEUE_H */

