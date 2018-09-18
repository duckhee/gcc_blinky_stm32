#define BOARD_DETECT_LOCAL


#include "Board_Detect.h"


/* Local Defines */
#define ADC1_DR_Address         ((uint32_t)0x4001244C)
#define BOARD_TYPE_MAX          31

/* Local Variables */

/*
    12 bit adc resolution is 4096
    3.3V / 4096 = 0.0008056640625 V

    J Class resistance 9000 ohm -> 9450 ~ 8550
    J Class resistance 1000 ohm -> 950  ~ 1050 

    3.3V X ( 1050 / 10500 ) = 0.33V
    3.3V X ( 950  / 10400 ) = 0.301V
    3.3V X ( 1050 / 9600  ) = 0.3609V
    3.3V X ( 950  / 9500  ) = 0.33V

    Max Error -0.03V ~ + 0.03V

    Max Sensor Board is 30 Class

    0   V	device 1    0     ~ 0.03V
    0.11V	device 2    0.08V ~ 0.14V
    0.22V	device 3    0.19V ~ 0.25V
     .	 .
     .	 .
     .	 .
     
*/

static float BoardClass[BOARD_TYPE_MAX][3]; 

/* Local Global Variables */
__IO uint16_t BoardDetectValue;
char *BoardType[BOARD_TYPE_MAX] = {
                                        "TEST1 0V",
                                        "TEST2 0.11V",
                                        "TEST3 0.22V",
                                        "TEST4 0.33V (3-Axis ACC Sensor Board with Temp)",
                                        "TEST5 0.44V",
                                        "TEST6 0.55V",
                                        "TEST7 0.66V (Pressure Board with Temp)",
                                        "TEST8 0.77V",
                                        "TEST9 0.88V (Light Sensor Board)",
                                        "TEST10 0.99V",
                                        "TEST11 1.1V",
                                        "TEST12 1.21V"
                                        "TEST13 1.32V",
                                        "TEST14 1.43V (Remocon Sensor Board)",
                                        "TEST15 1.54V",
                                        "TEST16 1.65V",
                                        "TEST17 1.76V",
                                        "TEST18 1.87V",
                                        "TEST19 1.98V (Gyro Sensor Board)",
                                        "TEST20 2.01V",
                                        "TEST21 2.12V (MPU 9150 9 Axis Sensor Board)",
                                        "TEST22 2.23V",
                                        "TEST23 2.34V",
                                        "TEST24 2.45V",
                                        "TEST25 2.56V",
                                        "TEST26 2.67V",
                                        "TEST27 2.78V",
                                        "TEST28 2.89V",
                                        "TEST29 3.0V (Humidity Sensor board)",
                                        "TEST30 3.11V",
                                        "TEST31 3.22V"
};

BOARD_DETECT_DEF void board_detect(void)
{
    uint32_t nLoop;
    float volt = 0.0;

    /* Initialize Board Class */
    for(nLoop = 0; nLoop < BOARD_TYPE_MAX; nLoop++)
    {
        BoardClass[nLoop][0] = 0 + (0.11 * nLoop);
        BoardClass[nLoop][1] = BoardClass[nLoop][0] - 0.03;
        BoardClass[nLoop][2] = BoardClass[nLoop][0] + 0.03;
    }
    BoardClass[0][1] = 0.0;
    BoardClass[BOARD_TYPE_MAX - 1][2] = (float)3.3;

    /* Convert AD value to Volt */
    volt = (float)(BoardDetectValue * 3.3)/(float)4095; //12bit 4096
    #if 0
        printf("volt [%f]\r\n", volt);
    #endif

    for(nLoop = 0; nLoop < BOARD_TYPE_MAX; nLoop++)
    {
        if(BoardClass[nLoop][1] < volt)
        {
            if(volt < BoardClass[nLoop][2])
            {
                printf("Board Type : %s\r\n", BoardType[nLoop]);
                printf("volt [%f]\r\n", volt);
                printf("BoardDetectValue : %x\r\n", BoardDetectValue);
                break;
            }
        }
    }
}

BOARD_DETECT_DEF void board_detect_initialize(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    /******************** Clock Enable ********************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    /******************** GPIO configure ********************/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /******************** DMA configure ********************/ 
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&BoardDetectValue;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel1, ENABLE);
    /******************** Fuction configure ********************/
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
    /* ADC1 regular channel14 configuration */ 
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_55Cycles5);
    /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);
    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);
    /* Enable ADC1 reset calibaration register */   
    ADC_ResetCalibration(ADC1);
    /* Check the end of ADC1 reset calibration register */
    while(ADC_GetResetCalibrationStatus(ADC1));
    /* Start ADC1 calibaration */
    ADC_StartCalibration(ADC1);
    /* Check the end of ADC1 calibration */
    while(ADC_GetCalibrationStatus(ADC1));
    /* Start ADC1 Software Conversion */ 
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
