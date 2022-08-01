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
# app
SRCS +=	$(DRIVERS)/rf-transceiver/navassa/adrv9002_conv.c \
	$(DRIVERS)/rf-transceiver/navassa/adrv9002.c \
	$(PROJECT)/src/app/headless.c
INCS += $(DRIVERS)/rf-transceiver/navassa/adrv9002.h \
	$(PROJECT)/src/app/ORxGainTable.h \
	$(PROJECT)/src/app/RxGainTable.h \
	$(PROJECT)/src/app/TxAttenTable.h \
	$(PROJECT)/src/app/Navassa_CMOS_profile.h \
	$(PROJECT)/src/app/Navassa_LVDS_profile.h
# hal
SRCS += $(PROJECT)/src/hal/no_os_platform.c
INCS += $(PROJECT)/src/hal/parameters.h \
	$(PROJECT)/src/hal/no_os_platform.h \
	$(PROJECT)/src/hal/adi_platform.h \
	$(PROJECT)/src/hal/adi_platform_types.h \
	$(PROJECT)/src/firmware/Navassa_EvaluationFw.h \
	$(PROJECT)/src/firmware/Navassa_Stream.h
# no-OS drivers
SRCS += $(PLATFORM_DRIVERS)/xilinx_gpio.c \
	$(DRIVERS)/api/no_os_gpio.c \
	$(DRIVERS)/api/no_os_spi.c \
	$(PLATFORM_DRIVERS)/xilinx_spi.c \
	$(PLATFORM_DRIVERS)/delay.c \
	$(NO-OS)/util/no_os_util.c \
	$(DRIVERS)/axi_core/axi_adc_core/axi_adc_core.c \
	$(DRIVERS)/axi_core/axi_dac_core/axi_dac_core.c \
	$(DRIVERS)/axi_core/axi_dmac/axi_dmac.c \
	$(PLATFORM_DRIVERS)/axi_io.c
INCS +=	$(INCLUDE)/no_os_spi.h \
	$(PLATFORM_DRIVERS)/spi_extra.h \
	$(INCLUDE)/no_os_gpio.h \
	$(PLATFORM_DRIVERS)/gpio_extra.h \
	$(INCLUDE)/no_os_error.h \
	$(INCLUDE)/no_os_delay.h \
	$(INCLUDE)/no_os_util.h \
	$(INCLUDE)/no_os_print_log.h \
	$(DRIVERS)/axi_core/axi_adc_core/axi_adc_core.h \
	$(DRIVERS)/axi_core/axi_dac_core/axi_dac_core.h \
	$(DRIVERS)/axi_core/axi_dmac/axi_dmac.h \
	$(INCLUDE)/no_os_axi_io.h

# Navassa API sources
SRC_DIRS += $(DRIVERS)/rf-transceiver/navassa

# IIO
ifeq (y,$(strip $(TINYIIOD)))
LIBRARIES += iio
SRC_DIRS += $(NO-OS)/iio/iio_app
SRCS += $(PLATFORM_DRIVERS)/no_os_uart.c \
	$(NO-OS)/util/no_os_lf256fifo.c \
	$(PLATFORM_DRIVERS)/$(PLATFORM)_irq.c \
	$(NO-OS)/util/no_os_list.c \
	$(NO-OS)/util/no_os_fifo.c \
	$(DRIVERS)/axi_core/iio_axi_adc/iio_axi_adc.c \
	$(DRIVERS)/axi_core/iio_axi_dac/iio_axi_dac.c \
	$(DRIVERS)/api/no_os_irq.c
INCS += $(INCLUDE)/no_os_uart.h \
	$(INCLUDE)/no_os_lf256fifo.h \
	$(INCLUDE)/no_os_irq.h \
	$(PLATFORM_DRIVERS)/irq_extra.h \
	$(PLATFORM_DRIVERS)/uart_extra.h \
	$(INCLUDE)/no_os_fifo.h \
	$(INCLUDE)/no_os_list.h \
	$(DRIVERS)/axi_core/iio_axi_adc/iio_axi_adc.h \
	$(DRIVERS)/axi_core/iio_axi_dac/iio_axi_dac.h
endif
