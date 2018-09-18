#define BH17_LOCAL

#include "BH17.h"


bool UartQueue_Serial_Is_Empty(void);
uint16_t UartQueue_Serial_DeQueue(void);

extern uint8_t Buffer_Rx1[];
extern uint8_t Buffer_Tx1[];


#define AL_BH17_SLAVE_ADDRESS     0x23 /* Slave Address : "010 0011" */


BH17_DEF uint8_t SENSOR_AL_BH17_Read_Bytes(uint8_t devAddr, uint8_t length, uint8_t *data)
{
    /*
     * devAddr should be shifted 1 bit to left ...
     */
    Status i2cRW_status;

    /* Disable FSMC */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, DISABLE);

    i2cRW_status = I2C_Master_BufferRead(I2C1, data, length, Polling, devAddr << 1);

    if(Error == i2cRW_status)
    {
        DEBUG_MSG_FUNC_ERROR;
        return 0;
    }

    /* Enable FSMC */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

    return length;

}

BH17_DEF int8_t SENSOR_AL_BH17_Write_Bytes(uint8_t devAddr, uint8_t length, uint8_t *data)
{
    Status i2cRW_status;

    /* Disable FSMC */
    RCC_AHBPeriph_FSMC(RCC_AHBPeriph_FSMC, DISABLE);

    memcpy(&Buffer_Tx1[0], data, length); //memory copy function

    i2cRW_status = I2C_Master_BufferWrite(I2C1, Buffer_Tx1, length, Interrupt, devAddr << 1);

    if(Error == i2cRW_status)
    {
        DEBUG_MSG_FUNC_ERROR;
        return -1;
    }

    /* Enable FSMC */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

    return 0;
}

static bool g_print_menu_control_flag = FALSE;

static void print_menu_command(void)
{
    if(TRUE == g_print_menu_control_flag)
    {
        printf("\r\n----------------------\r\n");
        printf("Press menu key \r\n");
        printf("-------------------------\r\n");
        printf("1> Get Data \r\n");
        printf("--------------------------\r\n");
        printf("x> quit\r\n");
    }

    g_print_menu_control_flag = FALSE;
}

void Test_Sensor_AL_BH17(void)
{
    uint8_t ch;
    uint8_t dataVal[2];

    uint16_t data16Val;

    float alData;

    GPIO_InitTypeDef GPIO_InitStructure;

    //DEBUG_MSG_FUNC_START;

    /* DVI setup */
    RCC_AHBPeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    printf("TEST BH17\r\n");
    //GPIO_SetBits(GPIOB, GPIO_Pin_0);
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);

    Delay(1000);

    dataVal[0] = 0x10;
    SENSOR_AL_BH17_Write_Bytes(AL_BH17_SLAVE_ADDRESS, 1, dataVal);

    Delay(1000);
//#if 0
/*
    while(1)
    {
        SENSOR_AL_BH17_Read_Bytes(AL_BH17_SLAVE_ADDRESS, 2, dataVal);
        data16Val = (dataVAl[0] << 8) | dataVal[1];
        printf("Data Val : 0x%04x\r\n", data16Val);
        Delay(1000);

        if(data16Val < 20)
        {
            LED_On_All();
        }
        else
        {
            LED_Off_All();
        }
    }
*/

//#else
    while(1)
    {
        print_menu_command();
        if(FALSE == UartQueue_Serial_Is_Empty())
        {
            ch = UartQueue_Serial_DeQueue();
            printf("%c is selected \r\n\r\n", (char)ch);

            switch((char)ch)
            {
                case '0':
                break;
                
                case '1':
                    SENSOR_AL_BH17_Read_Bytes(AL_BH17_SLAVE_ADDRESS, 2, dataVal);
                    data16Val = (dataVal[0] << 8) | dataVal[1];
                    printf("Data Val : 0x%04x\r\n", data16Val);
                    alData = (float)data16Val / 1.2;
                    printf("Lux : 0x%f\r\n", alData);
                break;

            }
            g_print_menu_control_flag = TRUE;

            if('x' == (char)ch)
            {
                break;
            }
        }
    }

//#endif

    return ;
}


