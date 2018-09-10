/*
 * (C) COPYRIGHT 2014 CRZ
 */

/* Includes */

#include "hw_config.h"
#include "BMA280.h"

#define BMA280_I2C_ADDR (0x18<<1)//x30
//#define BMA280_SLAVE_ADDRESS (0x18<<1)//x30

#define BMA280_RA_CHIP_ID           0x00
#define BMA280_RA_VERSION           0x01
#define BMA280_RA_X_AXIS_LSB        0x02
#define BMA280_RA_X_AXIS_MSB        0x03
#define BMA280_RA_Y_AXIS_LSB        0x04
#define BMA280_RA_Y_AXIS_MSB        0x05
#define BMA280_RA_Z_AXIS_LSB        0x06
#define BMA280_RA_Z_AXIS_MSB        0x07
#define BMA280_RA_TEMP_RD           0x08
#define BMA280_RA_SMB150_STATUS     0x09
#define BMA280_RA_SMB150_CTRL       0x0a
#define BMA280_RA_SMB150_CONF1      0x0b
#define BMA280_RA_LG_THRESHOLD      0x0c
#define BMA280_RA_LG_DURATION       0x0d
#define BMA280_RA_HG_THRESHOLD      0x0e
//#define BMA280_RA_HG_DURATION       0x0f
#define BMA280_RA_BANDWIDTH       0x10
#define BMA280_RA_HYSTERESIS        0x11
#define BMA280_RA_CUSTOMER1         0x12
#define BMA280_RA_CUSTOMER2         0x13
#define BMA280_RA_RANGE_BWIDTH      0x0f
#define BMA280_RA_SMB150_CONF2      0x15
#define BMA280_RA_OFFS_GAIN_X       0x16
#define BMA280_RA_OFFS_GAIN_Y       0x17
#define BMA280_RA_OFFS_GAIN_Z       0x18
#define BMA280_RA_OFFS_GAIN_T       0x19
#define BMA280_RA_OFFSET_X          0x1a
#define BMA280_RA_OFFSET_Y          0x1b
#define BMA280_RA_OFFSET_Z          0x1c
#define BMA280_RA_OFFSET_T          0x1d

#define BMA280_CHIP_ID_BIT             2
#define BMA280_CHIP_ID_LENGTH          3

#define BMA280_X_AXIS_LSB_BIT          7
#define BMA280_X_AXIS_LSB_LENGTH       2
#define BMA280_X_NEW_DATA_BIT          0

#define BMA280_Y_AXIS_LSB_BIT          7
#define BMA280_Y_AXIS_LSB_LENGTH       2
#define BMA280_Y_NEW_DATA_BIT          0

#define BMA280_Z_AXIS_LSB_BIT          7
#define BMA280_Z_AXIS_LSB_LENGTH       2
#define BMA280_Z_NEW_DATA_BIT          0

#define BMA280_STATUS_HG_BIT           0
#define BMA280_STATUS_LG_BIT           1
#define BMA280_HG_LATCHED_BIT          2
#define BMA280_LG_LATCHED_BIT          3
#define BMA280_ALERT_PHASE_BIT         4
#define BMA280_ST_RESULT_BIT           7

#define BMA280_SLEEP_BIT               0
#define BMA280_SOFT_RESET_BIT          1
#define BMA280_ST0_BIT                 2
#define BMA280_ST1_BIT                 3
#define BMA280_EEW_BIT                 4
#define BMA280_UPDATE_IMAGE_BIT        5
#define BMA280_RESET_INT_BIT           6

#define BMA280_ENABLE_LG_BIT           0
#define BMA280_ENABLE_HG_BIT           1
#define BMA280_COUNTER_LG_BIT          3
#define BMA280_COUNTER_LG_LENGTH       2
#define BMA280_COUNTER_HG_BIT          5
#define BMA280_COUNTER_HG_LENGTH       2
#define BMA280_ANY_MOTION_BIT          6
#define BMA280_ALERT_BIT               7

#define BMA280_LG_HYST_BIT             2
#define BMA280_LG_HYST_LENGTH          3
#define BMA280_HG_HYST_BIT             5
#define BMA280_HG_HYST_LENGTH          3
#define BMA280_ANY_MOTION_DUR_BIT      7
#define BMA280_ANY_MOTION_DUR_LENGTH   2

#define BMA280_BANDWIDTH_BIT           2
#define BMA280_BANDWIDTH_LENGTH        3
#define BMA280_RANGE_BIT               4
#define BMA280_RANGE_LENGTH            2

#define BMA280_WAKE_UP_BIT             0
#define BMA280_WAKE_UP_PAUSE_BIT       2
#define BMA280_WAKE_UP_PAUSE_LENGTH    2
#define BMA280_SHADOW_DIS_BIT          3
#define BMA280_LATCH_INT_BIT           4
#define BMA280_NEW_DATA_INT_BIT        5
#define BMA280_ENABLE_ADV_INT_BIT      6
#define BMA280_SPI4_BIT                7

/* range and bandwidth */
#define BMA280_RANGE_2G                0x3
#define BMA280_RANGE_4G                0x5
#define BMA280_RANGE_8G                0x8

#define BMA280_BW_7HZ                 0
#define BMA280_BW_7_81HZ                 0x8
#define BMA280_BW_15_13HZ                0x9
#define BMA280_BW_125HZ                12
#define BMA280_BW_250HZ                13
#define BMA280_BW_500HZ                14
#define BMA280_BW_MAX              0xF

static uint8_t Read_1_Byte(uint8_t address)
{
    uint8_t Buffer_Tx;
    uint8_t Buffer_Rx;

    Buffer_Tx = address;

    I2C_Master_BufferWrite(I2C1, &Buffer_Tx, 1, Polling, BMA280_I2C_ADDR);
    I2C_Master_BufferRead(I2C1, &Buffer_Rx, 1, Polling, BMA280_I2C_ADDR);

    return Buffer_Rx;
}

static uint8_t Get_ChipID(void)
{
    return Read_1_Byte(BMA280_RA_CHIP_ID);
}

/*
 * Description : none.
 * Argument(s) : none.
 * Return(s)   : none.
 * Note(s)     : none.
 */
void Read_3_Axis_BMA280_Data(int16_t * xData_p, int16_t * yData_p, int16_t * zData_p)
{
    uint8_t Buffer_Tx;
    uint8_t Buffer_Rx[6];

    Buffer_Tx = BMA280_RA_X_AXIS_LSB; //0x2

    I2C_Master_BufferWrite(I2C1, &Buffer_Tx, 1, Polling, BMA280_I2C_ADDR);
    I2C_Master_BufferRead(I2C1, Buffer_Rx, 6, Polling, BMA280_I2C_ADDR);

    * xData_p = ((((int16_t)(int8_t)Buffer_Rx[1]) << 8) | Buffer_Rx[0]) >> 6;
    * yData_p = ((((int16_t)(int8_t)Buffer_Rx[3]) << 8) | Buffer_Rx[2]) >> 6;
    * zData_p = ((((int16_t)(int8_t)Buffer_Rx[5]) << 8) | Buffer_Rx[4]) >> 6;
    
    for(int i = 0; i < sizeof(Buffer_Rx); i++)
    {
        printf("Buffer_Rx[%d] : %x\r\n", i, Buffer_Rx[i]);
    }
}

void Test_3AXIS_BMA280(void)
{
    uint8_t  Buffer_Tx[2];
    int16_t  xData, yData, zData;

    printf("Get_ChipID: %X\r\n", Get_ChipID());

    Buffer_Tx[0] = BMA280_RA_RANGE_BWIDTH; //0xf
    Buffer_Tx[1] = BMA280_RANGE_8G << 3; //0x40 0x8 << 3
    printf("Buffer_Tx : %x\r\n", Buffer_Tx);
    I2C_Master_BufferWrite(I2C1, Buffer_Tx, 2, Polling, BMA280_I2C_ADDR);
    Buffer_Tx[0] = BMA280_RA_BANDWIDTH; //0x10
    Buffer_Tx[1] = BMA280_BW_500HZ; //14
    printf("Buffer_Tx : %x\r\n", Buffer_Tx);
    I2C_Master_BufferWrite(I2C1, Buffer_Tx, 2, Polling, BMA280_I2C_ADDR);	
    printf("Set Param BMA280_RANGE_8G, BMA280_BW_500HZ\r\n");

    while(1)
    {
        Read_3_Axis_BMA280_Data(&xData, &yData, &zData);
        printf("x: %d, y: %d, z: %d\r\n", xData, yData, zData);
        Delay(300);
    }
}


