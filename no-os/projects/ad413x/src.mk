################################################################################
#									       #
#     Shared variables:							       #
#	- PROJECT							       #
#	- DRIVERS							       #
#	- INCLUDE							       #
#	- PLATFORM_DRIVERS						       #
#	- NO-OS								       #
#									       #
################################################################################

SRC_DIRS += $(PROJECT)/src
SRCS += $(DRIVERS)/api/no_os_spi.c \
	$(DRIVERS)/api/no_os_irq.c \
	$(DRIVERS)/api/no_os_gpio.c \
	$(DRIVERS)/afe/ad413x/ad413x.c

SRCS += $(PLATFORM_DRIVERS)/xilinx_spi.c \
	$(PLATFORM_DRIVERS)/xilinx_irq.c \
	$(PLATFORM_DRIVERS)/xilinx_gpio.c \
	$(PLATFORM_DRIVERS)/xilinx_gpio_irq.c \
	$(PLATFORM_DRIVERS)/delay.c \
	$(NO-OS)/util/no_os_list.c \
	$(NO-OS)/util/no_os_crc8.c

INCS += $(DRIVERS)/afe/ad413x/ad413x.h

INCS +=	$(PLATFORM_DRIVERS)/spi_extra.h \
	$(PLATFORM_DRIVERS)/irq_extra.h \
	$(PLATFORM_DRIVERS)/gpio_extra.h \
	$(PLATFORM_DRIVERS)/gpio_irq_extra.h

INCS += $(INCLUDE)/no_os_spi.h \
	$(INCLUDE)/no_os_gpio.h \
	$(INCLUDE)/no_os_error.h \
	$(INCLUDE)/no_os_delay.h \
	$(INCLUDE)/no_os_irq.h \
	$(INCLUDE)/no_os_util.h \
	$(INCLUDE)/no_os_print_log.h \
	$(INCLUDE)/no_os_list.h \
	$(INCLUDE)/no_os_crc8.h

ifeq (y,$(strip $(TINYIIOD)))
LIBRARIES += iio
SRCS += $(DRIVERS)/afe/ad413x/iio_ad413x.c \
	$(PLATFORM_DRIVERS)/no_os_uart.c \
	$(NO-OS)/iio/iio_app/iio_app.c \
	$(NO-OS)/util/no_os_fifo.c \
	$(NO-OS)/util/no_os_util.c
INCS += $(DRIVERS)/afe/ad413x/iio_ad413x.h \
	$(PLATFORM_DRIVERS)/uart_extra.h \
	$(NO-OS)/iio/iio_app/iio_app.h \
	$(INCLUDE)/no_os_fifo.h \
	$(INCLUDE)/no_os_uart.h
endif
