
/* Includes */

#include "hw_config.h"
#include "global_types.h"

/* Defines */

#define  UART_QUEUE_BUFFER_SIZE  3000

/* Variables */

// UART Queue for Comm
uint16_t  uart_queue_comm_buffer[UART_QUEUE_BUFFER_SIZE];
uint32_t  uart_queue_comm_point_head = 0;
uint32_t  uart_queue_comm_point_tail = 0;

// UART Queue for Serial
uint16_t  uart_queue_serial_buffer[UART_QUEUE_BUFFER_SIZE];
uint32_t  uart_queue_serial_point_head = 0;
uint32_t  uart_queue_serial_point_tail = 0;

/* Static Functions */

static void uart_queue_increase_point_value(uint32_t * data_p)
{
    (* data_p) ++;
    if(UART_QUEUE_BUFFER_SIZE == (* data_p))
    {
        (* data_p) = 0;
    }
}

/* Global Functions */

// UART Queue for Comm

void UartQueue_Comm_Initialize(void)
{
    uart_queue_comm_point_head = uart_queue_comm_point_tail = 0;
}

bool UartQueue_Comm_Is_Empty(void)
{
    if(uart_queue_comm_point_head == uart_queue_comm_point_tail)
    {
        return TRUE;
    }
    return FALSE;
}

void UartQueue_Comm_EnQueue(uint16_t data)
{
    uart_queue_comm_buffer[uart_queue_comm_point_head] = data;
    uart_queue_increase_point_value(&uart_queue_comm_point_head);
}

uint16_t UartQueue_Comm_DeQueue(void)
{
    uint16_t retVal = uart_queue_comm_buffer[uart_queue_comm_point_tail];
    uart_queue_increase_point_value(&uart_queue_comm_point_tail);
    return retVal;
}

// UART Queue for Serial

bool UartQueue_Serial_Is_Empty(void)
{
    if(uart_queue_serial_point_head == uart_queue_serial_point_tail)
    {
        return TRUE;
    }
    return FALSE;
}

void UartQueue_Serial_EnQueue(uint16_t data)
{
    uart_queue_serial_buffer[uart_queue_serial_point_head] = data;
    uart_queue_increase_point_value(&uart_queue_serial_point_head);
}

uint16_t UartQueue_Serial_DeQueue(void)
{
    uint16_t retVal = uart_queue_serial_buffer[uart_queue_serial_point_tail];
    uart_queue_increase_point_value(&uart_queue_serial_point_tail);
    return retVal;
}

