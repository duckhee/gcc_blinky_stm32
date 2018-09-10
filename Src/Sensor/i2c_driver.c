/*
 * (C) COPYRIGHT 2009 CRZ
 *
 * File Name : i2c_driver.c
 * 
 * History 
 *
 * when         who       what, where, why
 *--------------------------------------------------------------
 * 09/29/2011   sikim     Initial release
 */

/* Includes */

#include "hw_config.h"

/*
 * Description : none.
 * Argument(s) : none.
 * Return(s)   : none.
 * Note(s)     : none.
 */
void i2c1_driver_Initialize (void)
{
    GPIO_InitTypeDef GPIO_InitStructure;  
    I2C_InitTypeDef  I2C_InitStructure;    
    /******************** Clock Enable ********************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
        
    /******************** GPIO configure ********************/
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);          

    /******************** Fuction configure ********************/
    I2C_DeInit(I2C1);
    /* I2C1 Init */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    //I2C_InitStructure.I2C_OwnAddress1 = 0x70;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 400000;
    I2C_Cmd(I2C1, ENABLE);    
    I2C_Init(I2C1, &I2C_InitStructure);
}

/*
 * Description : none.
 * Argument(s) : none.
 * Return(s)   : none.
 * Note(s)     : none.
 */
void i2c1_1byte_addr7_write(uint8_t Device_Addr, uint16_t WriteAddr, uint8_t* pBuffer)
{
  /* Send STRAT condition */
  I2C_GenerateSTART(I2C1, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));  

  /* Send slave address for write */
  I2C_Send7bitAddress(I2C1, Device_Addr, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Send the device internal address to write to : only one byte Address */
  I2C_SendData(I2C1, WriteAddr);
  
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send the byte to be written */
  I2C_SendData(I2C1, *pBuffer); 
   
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send STOP condition */
  I2C_GenerateSTOP(I2C1, ENABLE);
}

/*
 * Description : none.
 * Argument(s) : none.
 * Return(s)   : none.
 * Note(s)     : none.
 */
void i2c1_addr7_read(uint8_t Device_Addr, uint16_t ReadAddr, uint8_t* pBuffer, uint16_t NumByteToRead)
{
    /* While the bus is busy */
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

    /* Send START condition */
    I2C_GenerateSTART(I2C1, ENABLE);

    /* Test on EV5 and clear it */
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    /* Send slave address for write */
    I2C_Send7bitAddress(I2C1, Device_Addr, I2C_Direction_Transmitter);

    /* Test on EV6 and clear it */
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    /* Send the device internal address to read from: Only one byte address */
    I2C_SendData(I2C1, ReadAddr);  

    /* Test on EV8 and clear it */
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    /* Send STOP condition */
    I2C_GenerateSTOP(I2C1, ENABLE);  

    /********************************/
  
    /* Send STRAT condition a second time */  
    I2C_GenerateSTART(I2C1, ENABLE);

    /* Test on EV5 and clear it */
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    /* Send device address for read */
    I2C_Send7bitAddress(I2C1, Device_Addr, I2C_Direction_Receiver);
  
    /* Test on EV6 and clear it */
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  
    /* While there is data to be read */
    while(NumByteToRead)  
    {
        if(NumByteToRead == 1)
        {
            /* Disable Acknowledgement */
            I2C_AcknowledgeConfig(I2C1, DISABLE);

            /* Send STOP Condition */
            I2C_GenerateSTOP(I2C1, ENABLE);
        }
        while ((I2C_GetLastEvent(I2C1) & 0x0040) != 0x000040); /* Poll on RxNE */            

        /* Read a byte from the EEPROM */
        *pBuffer = I2C_ReceiveData(I2C1);

        /* Point to the next location where the byte read will be saved */
        pBuffer++; 

        /* Decrement the read bytes counter */
        NumByteToRead--;        
        
    }

    /* Enable Acknowledgement to be ready for another reception */
    I2C_AcknowledgeConfig(I2C1, ENABLE);
}

