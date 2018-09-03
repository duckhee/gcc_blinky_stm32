MAIN_SOURCES = \
Src/main.c


CORE_SOURCES = \
CMSIS/Core/CM3/system_stm32f10x.c \
#CMSIS/Core/CM3/core_cm3.c\


CMSIS_SOURCES = \
STM32F10x_StdPeriph_Driver/src/misc.c \
STM32F10x_StdPeriph_Driver/src/bkp.c \
STM32F10x_StdPeriph_Driver/src/can.c \
STM32F10x_StdPeriph_Driver/src/crc.c \
STM32F10x_StdPeriph_Driver/src/dac.c \
STM32F10x_StdPeriph_Driver/src/dbgmcu.c \
STM32F10x_StdPeriph_Driver/src/dma.c \
STM32F10x_StdPeriph_Driver/src/exti.c \
STM32F10x_StdPeriph_Driver/src/flash.c \
STM32F10x_StdPeriph_Driver/src/fsmc.c \
STM32F10x_StdPeriph_Driver/src/gpio.c \
STM32F10x_StdPeriph_Driver/src/i2c.c \
STM32F10x_StdPeriph_Driver/src/iwdg.c \
STM32F10x_StdPeriph_Driver/src/pwr.c \
STM32F10x_StdPeriph_Driver/src/rcc.c \
STM32F10x_StdPeriph_Driver/src/rtc.c \
STM32F10x_StdPeriph_Driver/src/sdio.c \
STM32F10x_StdPeriph_Driver/src/spi.c \
STM32F10x_StdPeriph_Driver/src/tim.c \
STM32F10x_StdPeriph_Driver/src/usart.c \
STM32F10x_StdPeriph_Driver/src/wwdg.c \

C_SOURCES =  $(MAIN_SOURCES) $(CORE_SOURCES) $(CMSIS_SOURCES)

MAIN_INCLUDES = \
-I inc \
-I STM32F10x_StdPeriph_Driver/inc \
-I CMSIS/Core/CM3



C_INCLUDES = $(MAIN_INCLUDES)
