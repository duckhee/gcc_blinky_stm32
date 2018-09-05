#define I2C_SW_LOCAL

#include "I2c_Sw.h"


#define SW_I2C_WAIT_TIME       1
#define I2C_READ               0x01
#define READ_CMD               1
#define WRITE_CMD              0

#define SW_I2C_SDA_GPIO        GPIO_SW_I2C
#define SW_I2C_SCL_GPIO        GPIO_SW_I2C
#define SW_I2C_SDA_PIN         GPIO_SW_I2C_SDA_PIN
#define SW_I2C_SCL_PIN         GPIO_SW_I2C_SCL_PIN

I2C_DEF uint8_t SW_I2C_ReadVal_SDA(void);
I2C_DEF void SW_I2C_Write_Data(uint8_t data);
I2C_DEF uint8_t SW_I2C_Read_Data(void);
I2C_DEF uint8_t SW_I2C_WriteControl_8Bit(uint8_t IICID, uint8_t regaddr, uint8_t data);
I2C_DEF uint8_t SW_I2C_WriteControl_16Bit(uint8_t IICID, uint8_t regaddr, uint16_t data);
I2C_DEF uint8_t SW_I2C_ReadControl_8Bit(uint8_t IICID, uint8_t regaddr);
I2C_DEF uint16_t SW_I2C_ReadControl_16Bit(uint8_t IICID, uint8_t regaddr);



#ifdef BOARD_DEF_MANGO_M32
I2C_DEF void I2C_Send_Test(void)
{
    uint8_t ch;

    while(1)
    {
        ch = USART_GetCharacter(USART1);
        printf(" is selected, Send Data = 0x%0X\n", ch);
        SW_I2C_Write_Data(ch);
    }
}
#elif  BOARD_DEF_MANGO_Z1
uint8_t g_i2c_rx_data = 0;
bool g_flag_i2c_rx_done = FALSE;
uint8_t g_i2c_rx_count = 0;

I2C_DEF void I2C_Receive_Test(void)
{
    while(1)
    {
        if(TRUE == g_flag_i2c_rx_done)
        {
            printf("Read Data = 0x%0X (%c)\n", g_i2c_rx_data, g_i2c_rx_data);
            g_flag_i2c_rx_done = FALSE;
            g_i2c_rx_data = 0;
            g_i2c_rx_count = 0;
        }
    }
}
#endif


void TIMER_Wait_us(__IO uint32_t nCount)
{
    for(; nCount != 0; nCount--);
}

// SDA High
static inline void sda_high(void)
{
    GPIO_SetBits(SW_I2C_SDA_GPIO, SW_I2C_SDA_PIN);
}

//SDA Low
static inline void sda_low(void)
{
    GPIO_ResetBits(SW_I2C_SDA_GPIO, SW_I2C_SDA_PIN);
}

//SCL High
static inline void scl_high(void)
{
    GPIO_SetBits(SW_I2C_SCL_GPIO, SW_I2C_SCL_PIN);
}

//SCL Low
static inline void scl_low(void)
{
    GPIO_ResetBits(SW_I2C_SCL_GPIO, SW_I2C_SCL_PIN);
}

//sda out
static inline void sda_out(uint8_t out)
{
    if(out)
    {
        sda_high();
    }
    else
    {
        sda_low();
    }
}

//sda in is gpio setting 
static inline void sda_in_mode(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = SW_I2C_SDA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SW_I2C_SDA_GPIO, &GPIO_InitStructure);
}

//sda out mode gpio setting
static inline void sda_out_mode(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = SW_I2C_SDA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
}

//clk data out get
static inline void i2c_clk_data_out(void)
{
    scl_high();
    TIMER_Wait_us(SW_I2C_WAIT_TIME);
    scl_low();
}

//port inital
static inline void i2c_port_initial(void)
{
    sda_high();
    scl_low();
}

static inline void i2c_start_condition(void)
{
    sda_high();
    scl_high();

    TIMER_Wait_us(SW_I2C_WAIT_TIME);
    sda_low();
    TIMER_Wait_us(SW_I2C_WAIT_TIME);
    scl_low();
    TIMER_Wait_us(SW_I2C_WAIT_TIME);
}

static inline void i2c_stop_condition(void)
{
    sda_low();
    scl_high();
    TIMER_Wait_us(SW_I2C_WAIT_TIME);
    sda_high();
    TIMER_Wait_us(SW_I2C_WAIT_TIME);
}

static inline uint8_t i2c_check_ack(void)
{
    uint8_t ack;
    int i;
    unsigned int temp;

    sda_in_mode();
    scl_high();

    ack = FALSE;
    TIMER_Wait_us(SW_I2C_WAIT_TIME);

    for(i = 10; i > 0; i--)
    {
        temp = ~(SW_I2C_ReadVal_SDA());
        if(temp)
        {
            ack = TRUE;
            break;
        }
    }
    scl_low();
    sda_out_mode();
    TIMER_Wait_us(SW_I2C_WAIT_TIME);
    return ack;
}

//ack not checking
static inline void i2c_check_not_ack(void)
{
    sda_in_mode();
    i2c_clk_data_out();
    sda_out_mode();
    TIMER_Wait_us(SW_I2C_WAIT_TIME);
}

static inline void i2c_slave_address(uint8_t IICID, uint8_t readwrite)
{
    int x;
    if(readwrite)
    {
        IICID |= I2C_READ;
    }
    else
    {
        IICID &= ~I2C_READ;
    }

    scl_low();

    for(x = 7; x >= 0; x--)
    {
        sda_out(IICID & (1 << x));
        i2c_clk_data_out();
        TIMER_Wait_us(SW_I2C_WAIT_TIME);
    }
}

static inline void i2c_register_address(uint8_t addr)
{
    int x;
    scl_low();
    for(x = 7; x >= 0; x--)
    {
        sda_out(addr & (1 << x));
        i2c_clk_data_out();
        TIMER_Wait_us(SW_I2C_WAIT_TIME);
    }
}

static inline void i2c_send_ack(void)
{
    sda_out_mode();
    sda_low();

    TIMER_Wait_us(SW_I2C_WAIT_TIME);
    scl_high();

    TIMER_Wait_us(SW_I2C_WAIT_TIME);

    sda_low();
    TIMER_Wait_us(SW_I2C_WAIT_TIME);
    
    scl_low();

    sda_out_mode();

    TIMER_Wait_us(SW_I2C_WAIT_TIME);
}

I2C_DEF uint8_t SW_I2C_ReadVal_SDA(void)
{
    return GPIO_ReadOutputDataBit(SW_I2C_SDA_GPIO, SW_I2C_SDA_PIN);
}

I2C_DEF void SW_I2C_Write_Data(uint8_t data)
{
    int x;
    scl_low();
    
    for(x = 7; x > 0; x--)
    {
        sda_out(data & (1 << x));
        i2c_clk_data_out();
        TIMER_Wait_us(SW_I2C_WAIT_TIME);
    }
}

I2C_DEF uint8_t SW_I2C_Read_Data(void)
{
    int x;
    uint8_t readdata = 0;

    sda_in_mode();

    for(x = 8; x--;)
    {
        scl_high();

        readdata <<= 1;
        if(SW_I2C_ReadVal_SDA())
        {
            readdata |= 0x01;
        }

        TIMER_Wait_us(SW_I2C_WAIT_TIME);
        scl_low();

        TIMER_Wait_us(SW_I2C_WAIT_TIME);
    }
    sda_out_mode();
    return readdata;
}

I2C_DEF uint8_t SW_I2C_WriteControl_8Bit(uint8_t IICID, uint8_t regaddr, uint8_t data)
{
    uint8_t returnack = TRUE;
    i2c_start_condition();
    i2c_slave_address(IICID, WRITE_CMD);
    if(!i2c_check_ack())
    {
        returnack = FALSE;
    }

    TIMER_Wait_us(SW_I2C_WAIT_TIME);

    i2c_register_address(regaddr);
    if(!i2c_check_ack())
    {
        returnack = FALSE;
    }
    
    TIMER_Wait_us(SW_I2C_WAIT_TIME);

    SW_I2C_Write_Data(data);
    if(!i2c_check_ack())
    {
        returnack = FALSE;
    }

    TIMER_Wait_us(SW_I2C_WAIT_TIME);

    i2c_stop_condition();

    return returnack;

}
I2C_DEF uint8_t SW_I2C_WriteControl_16Bit(uint8_t IICID, uint8_t regaddr, uint16_t data)
{
    uint8_t returnack = TRUE;

    i2c_start_condition();

    i2c_slave_address(IICID, WRITE_CMD);
    if(!i2c_check_ack())
    {
        returnack = FALSE;
    }
    TIMER_Wait_us(SW_I2C_WAIT_TIME);
    i2c_register_address(regaddr);
    if(!i2c_check_ack())
    {
        returnack = FALSE;
    }
    TIMER_Wait_us(SW_I2C_WAIT_TIME);

    SW_I2C_Write_Data((data >> 8) & 0xFF);
    if(!i2c_check_ack())
    {
        returnack = FALSE;
    }

    TIMER_Wait_us(SW_I2C_WAIT_TIME);

    SW_I2C_Write_Data(data & 0xFF);
    if(!i2c_check_ack())
    {
        returnack = FALSE;
    }

    TIMER_Wait_us(SW_I2C_WAIT_TIME);

    i2c_stop_condition();

    return returnack;
}

I2C_DEF uint8_t SW_I2C_ReadControl_8Bit(uint8_t IICID, uint8_t regaddr)
{
    uint8_t  readdata = 0;

    i2c_port_initial();

    i2c_start_condition();

    i2c_slave_address(IICID, WRITE_CMD);
    i2c_check_ack();

    i2c_register_address(regaddr);
    i2c_check_ack();

    TIMER_Wait_us(SW_I2C_WAIT_TIME);

    i2c_start_condition();

    i2c_slave_address(IICID, READ_CMD);
    i2c_check_ack();

    TIMER_Wait_us(SW_I2C_WAIT_TIME);

    readdata = SW_I2C_Read_Data();

    i2c_check_not_ack();

    i2c_stop_condition();

    return readdata;
}
I2C_DEF uint16_t SW_I2C_ReadControl_16Bit(uint8_t IICID, uint8_t regaddr)
{
    uint16_t  readdata = 0;

    i2c_port_initial();

    i2c_start_condition();

    i2c_slave_address(IICID, WRITE_CMD);
    i2c_check_ack();

    i2c_register_address(regaddr);
    i2c_check_ack();

    TIMER_Wait_us(SW_I2C_WAIT_TIME);

    i2c_start_condition();

    i2c_slave_address(IICID, READ_CMD);
    i2c_check_ack();

    TIMER_Wait_us(SW_I2C_WAIT_TIME);

    readdata = SW_I2C_Read_Data();
    i2c_send_ack();
    TIMER_Wait_us(SW_I2C_WAIT_TIME);

    readdata = ((readdata << 8) | SW_I2C_Read_Data());

    i2c_check_not_ack();

    i2c_stop_condition();

    return readdata;    
}