#define GPIO_JTAG_LOCAL

#include "gpio_jtag.h"

JTAG_DEF void JTAG_Init(void);
JTAG_DEF void JTAG_TMS_Toggle_Red(void);
JTAG_DEF void Process_UseGPIO_JtagPort(void);


JTAG_DEF void JTAG_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    #ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x20000000 */ 
        NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
    #else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08000000 */ 
        NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
    #endif
    /* Configure one bit for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* Enable the EXTI14 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //gpio pin setting
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIO_JTAG */

    GPIO_InitStructure.GPIO_Pin   = GPIO_JTAG_TMS_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;
    GPIO_Init(GPIO_JTAG, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_JTAG_TCK_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_JTAG, &GPIO_InitStructure);

    EXTI_InitTypeDef EXTI_InitStructure;

    /* Connect EXTI Line to gpio pin */
    GPIO_EXTILineConfig(GPIO_PORTSOURCE_JTAG_TCK, GPIO_PINSOURCE_JTAG_TCK);

    /* Configure EXTI Line to generate an interrupt */  
    EXTI_InitStructure.EXTI_Line    = GPIO_EXTI_Line_JTAG_TCK;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

JTAG_DEF void JTAG_TMS_Toggle_Red(void)
{

}
JTAG_DEF void Process_UseGPIO_JtagPort(void)
{

}

