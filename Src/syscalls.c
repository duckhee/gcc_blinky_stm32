#include <stdio.h>
#include <sys/stat.h>
#include "stm32f10x.h"


__attribute__ ((used)) int _write(int fd, char *ptr, int len)
{
    size_t i;
    for(i = 0; i < len; i++)
    {
        USART_SendData(USART1, ptr[i]);
    }
    return len;
}