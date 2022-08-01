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
SRC_DIRS += $(DRIVERS)/adc/ad713x

SRCS += $(DRIVERS)/api/no_os_spi.c \
	$(DRIVERS)/api/no_os_gpio.c \
	$(DRIVERS)/axi_core/axi_dmac/axi_dmac.c \
	$(DRIVERS)/axi_core/spi_engine/spi_engine.c \
	$(DRIVERS)/axi_core/axi_pwmgen/axi_pwm.c \
	$(DRIVERS)/axi_core/clk_axi_clkgen/clk_axi_clkgen.c \
	$(NO-OS)/util/no_os_util.c \
	$(NO-OS)/util/no_os_lf256fifo.c
SRCS +=	$(PLATFORM_DRIVERS)/axi_io.c \
	$(PLATFORM_DRIVERS)/$(PLATFORM)_gpio.c \
	$(PLATFORM_DRIVERS)/$(PLATFORM)_spi.c \
	$(PLATFORM_DRIVERS)/delay.c
ifeq (y,$(strip $(TINYIIOD)))
LIBRARIES += iio
SRC_DIRS += $(NO-OS)/iio/iio_app
SRCS += $(PLATFORM_DRIVERS)/no_os_uart.c \
	$(PLATFORM_DRIVERS)/$(PLATFORM)_irq.c \
	$(DRIVERS)/api/no_os_irq.c \
	$(NO-OS)/util/no_os_fifo.c \
	$(NO-OS)/util/no_os_list.c	
endif
INCS += $(DRIVERS)/axi_core/axi_dmac/axi_dmac.h \
	$(DRIVERS)/axi_core/axi_pwmgen/axi_pwm_extra.h \
	$(DRIVERS)/axi_core/spi_engine/spi_engine.h \
	$(DRIVERS)/axi_core/spi_engine/spi_engine_private.h \
	$(DRIVERS)/axi_core/clk_axi_clkgen/clk_axi_clkgen.h
INCS +=	$(PLATFORM_DRIVERS)/spi_extra.h \
	$(PLATFORM_DRIVERS)/irq_extra.h \
	$(PLATFORM_DRIVERS)/uart_extra.h \
	$(PLATFORM_DRIVERS)/gpio_extra.h
INCS +=	$(INCLUDE)/no_os_axi_io.h \
	$(INCLUDE)/no_os_spi.h \
	$(INCLUDE)/no_os_gpio.h \
	$(INCLUDE)/no_os_error.h \
	$(INCLUDE)/no_os_delay.h \
	$(INCLUDE)/no_os_irq.h \
	$(INCLUDE)/no_os_uart.h \
	$(INCLUDE)/no_os_pwm.h \
	$(INCLUDE)/no_os_util.h \
	$(INCLUDE)/no_os_lf256fifo.h
ifeq (y,$(strip $(TINYIIOD)))
INCS += $(INCLUDE)/no_os_fifo.h \
	$(INCLUDE)/no_os_list.h
endif
