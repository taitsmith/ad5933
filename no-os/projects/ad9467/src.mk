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

# Uncomment to select the profile

SRCS += $(PROJECT)/src/app/ad9467_fmc.c
ifeq (y,$(strip $(TINYIIOD)))
LIBRARIES += iio
SRC_DIRS += $(NO-OS)/iio/iio_app
endif
SRCS += $(DRIVERS)/axi_core/axi_adc_core/axi_adc_core.c \
	$(DRIVERS)/axi_core/axi_dmac/axi_dmac.c \
	$(DRIVERS)/adc/ad9467/ad9467.c \
	$(DRIVERS)/frequency/ad9517/ad9517.c \
	$(DRIVERS)/api/no_os_spi.c \
	$(NO-OS)/util/no_os_util.c
SRCS +=	$(PLATFORM_DRIVERS)/axi_io.c \
	$(PLATFORM_DRIVERS)/xilinx_spi.c \
	$(PLATFORM_DRIVERS)/delay.c
ifeq (y,$(strip $(TINYIIOD)))
SRCS += $(NO-OS)/util/no_os_fifo.c \
	$(DRIVERS)/axi_core/iio_axi_adc/iio_axi_adc.c \
	$(DRIVERS)/api/no_os_irq.c \
	$(NO-OS)/util/no_os_list.c \
	$(PLATFORM_DRIVERS)/no_os_uart.c \
	$(NO-OS)/util/no_os_lf256fifo.c \
	$(PLATFORM_DRIVERS)/$(PLATFORM)_irq.c
endif
INCS +=	$(PROJECT)/src/app/app_config.h \
	$(PROJECT)/src/devices/adi_hal/parameters.h
INCS += $(DRIVERS)/axi_core/axi_adc_core/axi_adc_core.h \
	$(DRIVERS)/axi_core/axi_dmac/axi_dmac.h \
	$(DRIVERS)/adc/ad9467/ad9467.h \
	$(DRIVERS)/frequency/ad9517/ad9517.h
INCS +=	$(PLATFORM_DRIVERS)/spi_extra.h
INCS +=	$(INCLUDE)/no_os_axi_io.h \
	$(INCLUDE)/no_os_spi.h \
	$(INCLUDE)/no_os_error.h \
	$(INCLUDE)/no_os_delay.h \
	$(INCLUDE)/no_os_util.h
ifeq (y,$(strip $(TINYIIOD)))
INCS +=	$(INCLUDE)/no_os_fifo.h \
	$(INCLUDE)/no_os_irq.h \
	$(INCLUDE)/no_os_uart.h \
	$(INCLUDE)/no_os_lf256fifo.h \
	$(INCLUDE)/no_os_list.h \
	$(PLATFORM_DRIVERS)/irq_extra.h \
	$(PLATFORM_DRIVERS)/uart_extra.h \
	$(DRIVERS)/axi_core/iio_axi_adc/iio_axi_adc.h
endif
