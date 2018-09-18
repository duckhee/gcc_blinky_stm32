/*
 * (C) COPYRIGHT 2009 CRZ
 *
 * File Name : main.c
 * Author    : POOH
 * Version   : V1.0
 * Date      : 08/12/2009
 */



/* includes */

#include "hw_config.h"



/* global variables */

RCC_ClocksTypeDef  rcc_clocks;

bool g_TestProcessState = FALSE;

__IO uint16_t ADCConvertedValue;

/* functions */

void System_Information()
{
    printf("SYSCLK_Frequency = %d\r\n",rcc_clocks.SYSCLK_Frequency );
    printf("HCLK_Frequency = %d\r\n",rcc_clocks.HCLK_Frequency );
    printf("PCLK1_Frequency = %d\r\n",rcc_clocks.PCLK1_Frequency );
    printf("PCLK2_Frequency = %d\r\n",rcc_clocks.PCLK2_Frequency );
    printf("ADCCLK_Frequency = %d\r\n",rcc_clocks.ADCCLK_Frequency );
}
/*
 * Name   : main
 * Input  : None
 * Output : None
 * Return : None
 */
int main(void)
{
    //debug();
    uint8_t ch;

    /* System Clocks Configuration */
    RCC_Configuration();

    RCC_GetClocksFreq(&rcc_clocks);

    /* NVIC configuration */
    NVIC_Configuration();

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* EXTI configuration */
    EXTI_Configuration();

    /* UART initialization */
    USART1_Init();
    //i2c1 setting
    i2c1_driver_Initialize();    

    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(rcc_clocks.SYSCLK_Frequency / 1000))
    { 
        /* Capture error */ 
        while (1);
    }

    Delay(500);
    
    LED_Off_All();

    ADC_TempSensorVrefintCmd(ENABLE);

    DMA_Configuration();
    ADC_Configuration();
    board_detect_initialize();
    float volt = 0.0;
    float temp = 0.0;

    const float v25 = 1.43;
    const float avg_slope = 4.3;
    
    while(1)
    {
        printf("\r\n---------------------\r\n");
#ifdef BOARD_DEF_MANGO_M32
        printf("Mango M32 test start...\r\n");
#elif  BOARD_DEF_MANGO_Z1
        printf("Mango Z1 test start...\r\n");
#endif
        printf("Press menu key\r\n");
        printf("---------------------\r\n");
        printf("0> System Information\r\n");
        printf("---------------------\r\n");
        printf("1> LED Test\r\n");
        printf("2> KEY Test\r\n");
#ifdef BOARD_DEF_MANGO_M32
        printf("3> 7-Segment Test\r\n");
#elif  BOARD_DEF_MANGO_Z1
        printf("3> ZigBee Test\r\n");
#endif
        printf("4> USB HID Test\r\n");
        printf("5> BMA280 Sensor Test\r\n");
        printf("6> ADC inner Sensor Test\r\n");
        printf("7> Sensor Board Detect\r\n");
        printf("---------------------\r\n");
        printf("x> quit\r\n\r\n");

        ch = USART_GetCharacter(USART1);
        printf(" is selected\r\n\r\n");

        switch((char)ch)
        {
        case '0':
            System_Information();
            break;

        case '1':
            LED_Test();
            break;

        case '2':
            KEY_Test();
            break;

        case '3':
#ifdef BOARD_DEF_MANGO_M32
            Seven_Segment_Test();
#elif  BOARD_DEF_MANGO_Z1
            ZigBee_Test();
#endif
            break;

        case '4':

            break;

        case '5':
            Test_3AXIS_BMA280();
            break;
        case '6':
            Delay(2000);
            volt = (float)ADCConvertedValue * 3.3 /(float)4095;
            temp = (((v25-volt)*1000)/avg_slope) + 25.0;
            printf("ADC Value : 0x%0x, volt : %f V, Temp : %f `C\r\n", ADCConvertedValue, volt, temp);
            break;
        case '7':
            board_detect();
            break;


        }//switch end

        if('x' == (char)ch)
        {
            break;
        }
    }
    Delay(1000);
    LED_Off_All();
    Delay(1000);

    return 0;
}
