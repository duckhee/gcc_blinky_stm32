#ifndef __UART_COMM_H
#define __UART_COMM_H

/* Includes ------------------------------------------------------------------*/

#include "stm32l10x.h"
#include "stdio.h"


/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

void UartComm_SendData_OneChar(uint8_t ch);
void UartComm_SendData_Chars(uint8_t * ch_p, uint32_t data_size);
uint8_t UartComm_GetChar_Wait(void);
int8_t UartComm_GetChar_Timeout(uint8_t * data_p);

/* External variables --------------------------------------------------------*/

#endif  /* __UART_COMM_H */
