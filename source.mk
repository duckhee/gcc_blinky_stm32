######################################
# source
######################################
# C sources
SRC_SOURCES = \
Src/main.c \
Src/stm32f10x_it.c \
Src/hw_config.c \
Src/debug.c \
Src/key.c \
Src/led.c \
Src/seven_segment.c \
Src/usb_desc.c \
Src/usb_endp.c \
Src/usb_istr.c \
Src/usb_prop.c \
Src/usb_pwr.c \
Src/zigbee_test.c \
Src/syscalls.c \
Src/Sensor/i2c_driver.c \
Src/Sensor/I2CRoutines.c \
Src/Sensor/BMA280.c \
#src/support.c \

CMSIS_SOURCES = \
STM32F10x_StdPeriph_Driver/src/misc.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c \

USB_SOURCES = \
STM32_USB-FS-Device_Driver/src/usb_core.c \
STM32_USB-FS-Device_Driver/src/usb_init.c \
STM32_USB-FS-Device_Driver/src/usb_int.c \
STM32_USB-FS-Device_Driver/src/usb_mem.c \
STM32_USB-FS-Device_Driver/src/usb_regs.c \

CORE_SOURCES = \
CMSIS/Core/CM3/system_stm32f10x.c \
#CMSIS/Core/CM3/core_cm3.c \

ZIGBEE_SOURCE = \
Src/zigbee/basic_rf_security.c \
Src/zigbee/basic_rf.c \
Src/zigbee/cc2520_mango_porting.c \
Src/zigbee/hal_cc2520.c \
Src/zigbee/hal_int.c \
Src/zigbee/hal_rf_security.c \
Src/zigbee/hal_rf.c \
Src/zigbee/util.c \
Src/zigbee/zigbee.c \

SENSOR_SORUCE = \
Src/Sensor/I2c_Sw.c \
Src/Sensor/Board_Detect.c \
Src/Sensor/SHT20.c \

C_SOURCES =  $(SRC_SOURCES) $(CMSIS_SOURCES) $(USB_SOURCES) $(CORE_SOURCES) $(SENSOR_SORUCE) $(ZIGBEE_SOURCE)

# ASM sources
ASM_SOURCES =  \
CMSIS/Core/CM3/startup/gcc/startup_stm32f10x_md.s