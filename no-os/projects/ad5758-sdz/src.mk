# See No-OS/tool/scripts/src_model.mk for variable description
SRC_DIRS += $(PROJECT)/src
SRCS += $(DRIVERS)/api/no_os_gpio.c \
        $(DRIVERS)/api/no_os_spi.c \
        $(PLATFORM_DRIVERS)/$(PLATFORM)_spi.c \
        $(PLATFORM_DRIVERS)/$(PLATFORM)_gpio.c \
	$(PLATFORM_DRIVERS)/delay.c \
	$(DRIVERS)/dac/ad5758/ad5758.c

INCS += $(INCLUDE)/no_os_gpio.h \
	$(INCLUDE)/no_os_spi.h \
        $(INCLUDE)/no_os_error.h \
        $(INCLUDE)/no_os_delay.h \
        $(INCLUDE)/no_os_print_log.h \
        $(PLATFORM_DRIVERS)/gpio_extra.h \
	$(PLATFORM_DRIVERS)/spi_extra.h	\
	$(DRIVERS)/dac/ad5758/ad5758.h
