include $(PROJECT)/src/platform/$(PLATFORM)/platform_src.mk
include $(PROJECT)/src/examples/examples_src.mk

SRCS += $(PROJECT)/src/platform/$(PLATFORM)/main.c

INCS += $(PROJECT)/src/common/app_config.h
INCS += $(PROJECT)/src/common/common_data.h
SRCS += $(PROJECT)/src/common/common_data.c

INCS += $(PROJECT)/src/platform/platform_includes.h

INCS += $(PROJECT)/src/platform/$(PLATFORM)/parameters.h
SRCS += $(PROJECT)/src/platform/$(PLATFORM)/parameters.c 

SRCS += $(NO-OS)/util/no_os_fifo.c      \
        $(NO-OS)/util/no_os_list.c      \
        $(NO-OS)/util/no_os_util.c

INCS += $(INCLUDE)/no_os_delay.h     \
        $(INCLUDE)/no_os_error.h     \
        $(INCLUDE)/no_os_fifo.h      \
        $(INCLUDE)/no_os_irq.h       \
        $(INCLUDE)/no_os_lf256fifo.h \
        $(INCLUDE)/no_os_list.h      \
        $(INCLUDE)/no_os_timer.h     \
        $(INCLUDE)/no_os_uart.h      \
        $(INCLUDE)/no_os_util.h

INCS += $(DRIVERS)/adc/adc_demo/adc_demo.h \
        $(DRIVERS)/dac/dac_demo/dac_demo.h

SRCS += $(DRIVERS)/adc/adc_demo/adc_demo.c \
        $(DRIVERS)/dac/dac_demo/dac_demo.c


