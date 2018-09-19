#define SHT20_LOCAL

#include "SHT20.h"

//---------- Defines -----------------------------------------------------------
//  CRC
const uint16_t POLYNOMIAL = 0x131;  //P(x)=x^8+x^5+x^4+1 = 100110001

// measurement signal selection
#define   HUMIDITY 0
#define   TEMP     1

// Error codes
typedef enum{
  ACK_ERROR                = 0x01,
  TIME_OUT_ERROR           = 0x02,
  CHECKSUM_ERROR           = 0x04,
  UNIT_ERROR               = 0x08
}etError;

// sensor command
typedef enum{
  TRIG_T_MEASUREMENT_HM    = 0xE3, // command trig. temp meas. hold master
  TRIG_RH_MEASUREMENT_HM   = 0xE5, // command trig. humidity meas. hold master
  TRIG_T_MEASUREMENT_POLL  = 0xF3, // command trig. temp meas. no hold master
  TRIG_RH_MEASUREMENT_POLL = 0xF5, // command trig. humidity meas. no hold master
  USER_REG_W               = 0xE6, // command writing user register
  USER_REG_R               = 0xE7, // command reading user register
  SOFT_RESET               = 0xFE  // command soft reset
}etSHT2xCommand;

typedef enum {
  SHT2x_RES_12_14BIT       = 0x00, // RH=12bit, T=14bit
  SHT2x_RES_8_12BIT        = 0x01, // RH= 8bit, T=12bit
  SHT2x_RES_10_13BIT       = 0x80, // RH=10bit, T=13bit
  SHT2x_RES_11_11BIT       = 0x81, // RH=11bit, T=11bit
  SHT2x_RES_MASK           = 0x81  // Mask for res. bits (7,0) in user reg.
} etSHT2xResolution;

typedef enum {
  SHT2x_EOB_ON             = 0x40, // end of battery
  SHT2x_EOB_MASK           = 0x40, // Mask for EOB bit(6) in user reg.
} etSHT2xEob;

typedef enum {
  SHT2x_HEATER_ON          = 0x04, // heater on
  SHT2x_HEATER_OFF         = 0x00, // heater off
  SHT2x_HEATER_MASK        = 0x04, // Mask for Heater bit(2) in user reg.
} etSHT2xHeater;

typedef enum{
  I2C_ADR_W                = 0x80,   // sensor I2C address + write bit
  I2C_ADR_R                = 0x81    // sensor I2C address + read bit
}etI2cHeader;


/*
 * Description : none.
 * Argument(s) : none.
 * Return(s)   : none.
 * Note(s)     : none.
 */
SHT20_DEF void SHT2x_test(void)
{
    uint8_t SerialNumber_SHT2x[8];  //64bit serial number    
    uint8_t userRegister;           //variable for user register
    uint8_t sRH[2];                   //variable for raw humidity ticks
    uint8_t sT[2];                    //variable for raw temperature ticks
    float   humidityRH;             //variable for relative humidity[%RH] as float    
    float   temperatureC;           //variable for temperature[�C] as float
        
    SHT2x_SoftReset();
    SHT2x_GetSerialNumber(SerialNumber_SHT2x);
    printf("SerialNumber_SHT2x : [%x][%x][%x][%x][%x][%x][%x][%x]\r\n", SerialNumber_SHT2x[0], SerialNumber_SHT2x[1],
    SerialNumber_SHT2x[2], SerialNumber_SHT2x[3], SerialNumber_SHT2x[4], SerialNumber_SHT2x[5], SerialNumber_SHT2x[6],
    SerialNumber_SHT2x[7]);
    printf("SerialNumber_SHT2x : %x%x%x%x%x%x%x%x\r\n", SerialNumber_SHT2x[0], SerialNumber_SHT2x[1],
    SerialNumber_SHT2x[2], SerialNumber_SHT2x[3], SerialNumber_SHT2x[4], SerialNumber_SHT2x[5], SerialNumber_SHT2x[6],
    SerialNumber_SHT2x[7]);
    // --- Set Resolution e.g. RH 10bit, Temp 13bit ---            
    SHT2x_ReadUserRegister(&userRegister);
    printf("userRegister : [%x]\r\n", userRegister);
    userRegister = (userRegister & ~0x81) | 0x80;
    SHT2x_WriteUserRegister(&userRegister); //write changed user reg

    // --- measure humidity with "Hold Master Mode (HM)"  ---
    SHT2x_MeasureHM(HUMIDITY, sRH);
    // --- measure temperature with "Polling Mode" (no hold master) ---
    SHT2x_MeasurePoll(TEMP, sT);            

    //-- calculate humidity and temperature --
    temperatureC = SHT2x_CalcTemperatureC( sT);
    humidityRH   = SHT2x_CalcRH( sRH);    
    // --- check end of battery status (eob)---
    // note: a RH / Temp. measurement must be executed to update the status of eob
    SHT2x_ReadUserRegister(&userRegister);  //get actual user reg

    //-- write humidity and temperature values on LCD --
    printf("Humidity RH:%6.2f %% ",humidityRH);
    printf("\r\n");
    printf("Temperature:%6.2f C",temperatureC);
    
    delay_100_milli_second();
    delay_100_milli_second();    
    delay_100_milli_second();
    delay_100_milli_second();
}

//===========================================================================
SHT20_DEF uint8_t SHT2x_SoftReset()
//===========================================================================
{
  uint8_t  error=0;           //error variable

  i2c1_1byte_addr7_write_cmd( I2C_ADR_W, SOFT_RESET );
  delay_100_milli_second();
  return error;
}


//==============================================================================
SHT20_DEF uint8_t SHT2x_CheckCrc(uint8_t data[], uint8_t nbrOfBytes, uint8_t checksum)
//==============================================================================
{
  uint8_t crc = 0;	
  uint8_t byteCtr;
  //calculates 8-Bit checksum with given polynomial
  for (byteCtr = 0; byteCtr < nbrOfBytes; ++byteCtr)
  { crc ^= (data[byteCtr]);
    for (uint8_t bit = 8; bit > 0; --bit)
    { if (crc & 0x80) crc = (crc << 1) ^ POLYNOMIAL;
      else crc = (crc << 1);
    }
  }
  if (crc != checksum) return CHECKSUM_ERROR;
  else return 0;
}

//===========================================================================
SHT20_DEF uint8_t SHT2x_ReadUserRegister(uint8_t *pRegisterValue)
//===========================================================================
{
  uint8_t checksum;   //variable for checksum byte
  uint8_t error=0;    //variable for error code
  uint8_t i2c_data[3];

  i2c1_addr7_read(I2C_ADR_W, USER_REG_R, i2c_data, 2);

  *pRegisterValue = i2c_data[0];
  checksum = i2c_data[1];

  error |= SHT2x_CheckCrc (pRegisterValue,1,checksum);

#if 0  
  printf("error : [%x]\r\n", error);
#endif

  return error;
}

//==============================================================================
SHT20_DEF uint8_t SHT2x_GetSerialNumber(uint8_t u8SerialNumber[])
//==============================================================================
{
  uint8_t  error=0;                          //error variable
  uint8_t i2c_data[0xf];

  //Read from memory location 1  
  i2c1_addr7_cmd_read(I2C_ADR_W, 0xFA, 0x0F, i2c_data, 4);
  u8SerialNumber[5] = i2c_data[0]; //Read SNB_3
  u8SerialNumber[4] = i2c_data[2]; //Read SNB_2
  u8SerialNumber[3] = i2c_data[4]; //Read SNB_1
  u8SerialNumber[2] = i2c_data[6]; //Read SNB_0

  //Read from memory location 2
  i2c1_addr7_cmd_read(I2C_ADR_W, 0xFC, 0xC9, i2c_data, 4);
  u8SerialNumber[1] = i2c_data[0]; //Read SNC_1
  u8SerialNumber[0] = i2c_data[1]; //Read SNC_0
  u8SerialNumber[7] = i2c_data[3]; //Read SNA_1
  u8SerialNumber[6] = i2c_data[4]; //Read SNA_0

  return error;
}

//===========================================================================
SHT20_DEF uint8_t SHT2x_WriteUserRegister(uint8_t *pRegisterValue)
//===========================================================================
{
  uint8_t error=0;   //variable for error code

  i2c1_1byte_addr7_write( I2C_ADR_W, USER_REG_W, pRegisterValue);

  return error;
}

//===========================================================================
SHT20_DEF uint8_t SHT2x_MeasureHM(uint8_t eSHT2xMeasureType, uint8_t* pMeasurand)
//===========================================================================
{
  uint8_t  checksum;   //checksum
  uint8_t  data[2];    //data array for checksum verification
  uint8_t  error=0;    //error variable
  uint8_t i2c_data[3];

  if( eSHT2xMeasureType == HUMIDITY )
  {
    i2c1_addr7_read( I2C_ADR_W, TRIG_RH_MEASUREMENT_HM, i2c_data, 3);

     //-- read two data bytes and one checksum byte --
     pMeasurand[0] = i2c_data[0];
     pMeasurand[1] = i2c_data[1];
     checksum   =   i2c_data[2];
     
     error |= SHT2x_CheckCrc (data,2,checksum);     
  }
  if( eSHT2xMeasureType == TEMP )
  {
    i2c1_addr7_read( I2C_ADR_W, TRIG_T_MEASUREMENT_HM, i2c_data, 3);

     //-- read two data bytes and one checksum byte --
     pMeasurand[0] = i2c_data[0];
     pMeasurand[1] = i2c_data[1];
     checksum   =   i2c_data[2];
     
     error |= SHT2x_CheckCrc (data,2,checksum);     
  }

  return error;
}


//===========================================================================
SHT20_DEF uint8_t SHT2x_MeasurePoll(uint8_t eSHT2xMeasureType, uint8_t* pMeasurand)
//===========================================================================
{
  uint8_t  checksum;   //checksum
  uint8_t  data[2];    //data array for checksum verification
  uint8_t  error=0;    //error variable
  uint8_t i2c_data[3];
  
  //-- write I2C sensor address and command --
  if( eSHT2xMeasureType == HUMIDITY )
  {
    i2c1_addr7_read( I2C_ADR_W, TRIG_RH_MEASUREMENT_HM, i2c_data, 3);

     //-- read two data bytes and one checksum byte --
     pMeasurand[0] = i2c_data[0];
     pMeasurand[1] = i2c_data[1];
     checksum   =   i2c_data[2];
     
     error |= SHT2x_CheckCrc (data,2,checksum);     
  }
  if( eSHT2xMeasureType == TEMP )
  {
    i2c1_addr7_read( I2C_ADR_W, TRIG_T_MEASUREMENT_HM, i2c_data, 3);

     //-- read two data bytes and one checksum byte --
     pMeasurand[0] = i2c_data[0];
     pMeasurand[1] = i2c_data[1];
     checksum   =   i2c_data[2];
     
     error |= SHT2x_CheckCrc (data,2,checksum);     
  }  

  return error;
}

//==============================================================================
SHT20_DEF float SHT2x_CalcRH(uint8_t* psRH)
//==============================================================================
{
  float humidityRH;              // variable for result
  uint16_t u16_sRH;
  u16_sRH = (psRH[0]<<8) | psRH[1];

  u16_sRH &= ~0x0003;          // clear bits [1..0] (status bits)
  //-- calculate relative humidity [%RH] --

  humidityRH = -6.0 + 125.0/65536 * (float)u16_sRH; // RH= -6 + 125 * SRH/2^16
  return humidityRH;
}

//==============================================================================
SHT20_DEF float SHT2x_CalcTemperatureC(uint8_t* psT)
//==============================================================================
{
  float temperatureC;            // variable for result
  uint16_t u16_sT;
  u16_sT = (psT[0]<<8) | psT[1];

  u16_sT &= ~0x0003;           // clear bits [1..0] (status bits)

  //-- calculate temperature [�C] --
  temperatureC= -46.85 + 175.72/65536 *(float)u16_sT; //T= -46.85 + 175.72 * ST/2^16
  return temperatureC;
}



