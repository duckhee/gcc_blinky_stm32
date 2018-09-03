######################################
# source
######################################
# C sources
SRC_SOURCES = \
src/main.c \
src/stm32f10x_it.c \
src/hw_config.c \
src/debug.c \
src/key.c \
src/led.c \
src/seven_segment.c \
src/usb_desc.c \
src/usb_endp.c \
src/usb_istr.c \
src/usb_prop.c \
src/usb_pwr.c \
src/zigbee_test.c \

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

C_SOURCES =  $(SRC_SOURCES) $(CMSIS_SOURCES) $(USB_SOURCES) $(CORE_SOURCES)

# ASM sources
ASM_SOURCES =  \
CMSIS/Core/CM3/startup/gcc/startup_stm32f10x_md.s