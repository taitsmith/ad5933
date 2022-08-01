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

#PROFILE =  tx_bw100_orx_bw100_rx_bw100
#PROFILE = tx_bw100_orx_bw100_rx_bw40
PROFILE = tx_bw200_orx_bw200_rx_bw100
SRCS += $(PROJECT)/src/app/headless.c \
	$(PROJECT)/profiles/$(PROFILE)/myk_ad9528init.c \
	$(PROJECT)/profiles/$(PROFILE)/myk.c \
	$(PROJECT)/src/devices/ad9528/ad9528.c \
	$(PROJECT)/src/devices/adi_hal/common.c \
	$(PROJECT)/src/devices/mykonos/mykonos.c \
	$(PROJECT)/src/devices/mykonos/mykonos_debug/mykonos_dbgjesd.c \
	$(PROJECT)/src/devices/mykonos/mykonos_gpio.c \
	$(PROJECT)/src/devices/mykonos/mykonosMmap.c \
	$(PROJECT)/src/devices/mykonos/mykonos_user.c
SRCS += $(DRIVERS)/axi_core/axi_adc_core/axi_adc_core.c \
	$(DRIVERS)/axi_core/axi_dac_core/axi_dac_core.c \
	$(DRIVERS)/axi_core/axi_dmac/axi_dmac.c \
	$(DRIVERS)/axi_core/jesd204/axi_jesd204_rx.c \
	$(DRIVERS)/axi_core/jesd204/axi_jesd204_tx.c \
	$(NO-OS)/util/no_os_util.c \
	$(DRIVERS)/api/no_os_spi.c \
	$(DRIVERS)/api/no_os_gpio.c
ifeq (xilinx,$(strip $(PLATFORM)))
SRCS += $(DRIVERS)/axi_core/jesd204/xilinx_transceiver.c \
	$(DRIVERS)/axi_core/jesd204/axi_adxcvr.c \
	$(DRIVERS)/axi_core/clk_axi_clkgen/clk_axi_clkgen.c \
	$(PLATFORM_DRIVERS)/xilinx_spi.c \
	$(PLATFORM_DRIVERS)/xilinx_gpio.c
else
SRCS += $(DRIVERS)/axi_core/clk_altera_a10_fpll/clk_altera_a10_fpll.c \
	$(DRIVERS)/axi_core/jesd204/altera_a10_atx_pll.c \
	$(DRIVERS)/axi_core/jesd204/altera_a10_cdr_pll.c \
	$(DRIVERS)/axi_core/jesd204/altera_adxcvr.c \
	$(PLATFORM_DRIVERS)/altera_spi.c \
	$(PLATFORM_DRIVERS)/altera_gpio.c
endif
SRCS +=	$(PLATFORM_DRIVERS)/axi_io.c \
	$(PLATFORM_DRIVERS)/delay.c
ifeq (y,$(strip $(TINYIIOD)))
LIBRARIES += iio
SRCS += $(PLATFORM_DRIVERS)/no_os_uart.c \
	$(NO-OS)/util/no_os_lf256fifo.c \
	$(PLATFORM_DRIVERS)/$(PLATFORM)_irq.c \
	$(NO-OS)/util/no_os_fifo.c \
	$(NO-OS)/util/no_os_list.c \
	$(DRIVERS)/axi_core/iio_axi_adc/iio_axi_adc.c \
	$(DRIVERS)/axi_core/iio_axi_dac/iio_axi_dac.c \
	$(NO-OS)/iio/iio_app/iio_app.c \
	$(DRIVERS)/api/no_os_irq.c
endif
INCS +=	$(PROJECT)/src/app/app_config.h \
	$(PROJECT)/src/devices/ad9528/ad9528.h \
	$(PROJECT)/src/devices/ad9528/t_ad9528.h \
	$(PROJECT)/src/devices/adi_hal/common.h \
	$(PROJECT)/src/devices/adi_hal/parameters.h \
	$(PROJECT)/profiles/$(PROFILE)/myk.h \
	$(PROJECT)/src/devices/mykonos/mykonos_debug/mykonos_dbgjesd.h \
	$(PROJECT)/src/devices/mykonos/mykonos_debug/t_mykonos_dbgjesd.h \
	$(PROJECT)/src/devices/mykonos/mykonos_gpio.h \
	$(PROJECT)/src/devices/mykonos/mykonos.h \
	$(PROJECT)/src/devices/mykonos/mykonos_macros.h \
	$(PROJECT)/src/devices/mykonos/mykonos_user.h \
	$(PROJECT)/src/devices/mykonos/mykonos_version.h \
	$(PROJECT)/src/devices/mykonos/t_mykonos_gpio.h \
	$(PROJECT)/src/devices/mykonos/t_mykonos.h \
	$(PROJECT)/src/firmware/Mykonos_M3.h
INCS += $(DRIVERS)/axi_core/axi_adc_core/axi_adc_core.h \
	$(DRIVERS)/axi_core/axi_dac_core/axi_dac_core.h \
	$(DRIVERS)/axi_core/axi_dmac/axi_dmac.h \
	$(DRIVERS)/axi_core/jesd204/axi_jesd204_rx.h \
	$(DRIVERS)/axi_core/jesd204/axi_jesd204_tx.h
ifeq (xilinx,$(strip $(PLATFORM)))
INCS += $(DRIVERS)/axi_core/jesd204/xilinx_transceiver.h \
	$(DRIVERS)/axi_core/jesd204/axi_adxcvr.h \
	$(DRIVERS)/axi_core/clk_axi_clkgen/clk_axi_clkgen.h
else
INCS += $(DRIVERS)/axi_core/clk_altera_a10_fpll/clk_altera_a10_fpll.h \
	$(DRIVERS)/axi_core/jesd204/altera_a10_atx_pll.h \
	$(DRIVERS)/axi_core/jesd204/altera_a10_cdr_pll.h \
	$(DRIVERS)/axi_core/jesd204/altera_adxcvr.h
endif
INCS +=	$(PLATFORM_DRIVERS)/spi_extra.h \
	$(PLATFORM_DRIVERS)/gpio_extra.h
INCS +=	$(INCLUDE)/no_os_axi_io.h \
	$(INCLUDE)/no_os_spi.h \
	$(INCLUDE)/no_os_gpio.h \
	$(INCLUDE)/no_os_error.h \
	$(INCLUDE)/no_os_delay.h \
	$(INCLUDE)/no_os_util.h \
	$(INCLUDE)/no_os_print_log.h
ifeq (y,$(strip $(TINYIIOD)))
INCS += $(INCLUDE)/no_os_fifo.h \
	$(INCLUDE)/no_os_irq.h \
	$(INCLUDE)/no_os_uart.h \
	$(INCLUDE)/no_os_lf256fifo.h \
	$(INCLUDE)/no_os_list.h \
	$(PLATFORM_DRIVERS)/irq_extra.h \
	$(PLATFORM_DRIVERS)/uart_extra.h \
	$(DRIVERS)/axi_core/iio_axi_adc/iio_axi_adc.h \
	$(NO-OS)/iio/iio_app/iio_app.h \
	$(DRIVERS)/axi_core/iio_axi_dac/iio_axi_dac.h
endif
