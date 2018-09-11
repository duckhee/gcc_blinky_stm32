#include "TIM_1_Second.h"


void System_Information()
{
    printf("SYSCLK_Frequency = %d\r\n",rcc_clocks.SYSCLK_Frequency );
    printf("HCLK_Frequency = %d\r\n",rcc_clocks.HCLK_Frequency );
    printf("PCLK1_Frequency = %d\r\n",rcc_clocks.PCLK1_Frequency );
    printf("PCLK2_Frequency = %d\r\n",rcc_clocks.PCLK2_Frequency );
    printf("ADCCLK_Frequency = %d\r\n",rcc_clocks.ADCCLK_Frequency );
}

void TIM_Configuration(void)
{
    //clock init
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    //tim2 setting 
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 0x4AF; //period setting 1200
    TIM_TimeBaseStructure.TIM_Prescaler = 0xEA5F; //prescaler setting 60000
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_Cmd(TIM2, ENABLE);
}

int main(void)
{
    RCC_Configuration();
    RCC_GetClocksFreq(&rcc_clocks);
    NVIC_Configuration();
    GPIO_Configuration();
    EXTI_Configuration();
    USART1_Init();
    LED_Off_All();
    TIM_Configuration();

    if(SysTick_Config(rcc_clocks.SYSCLK_Frequency / 1000)) //?
    {
        while(1);
    }
}