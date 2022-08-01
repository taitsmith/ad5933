#See No-OS/tool/scripts/src_model.mk for variable description
PLATFORM = aducm3029

# TINYIIOD=y

SRC_DIRS += $(PROJECT)/src \
		$(PLATFORM_DRIVERS) \
		$(NO-OS)/util \
		$(NO-OS)/include
SRCS += $(NO-OS)/drivers/api/no_os_irq.c

ifeq '$(TINYIIOD)' 'y'
SRC_DIRS += $(NO-OS)/iio/iio_app
SRCS += $(NO-OS)/drivers/api/no_os_gpio.c \
        $(NO-OS)/drivers/api/no_os_i2c.c  \
        $(NO-OS)/drivers/api/no_os_irq.c  \
        $(NO-OS)/drivers/api/no_os_spi.c  \
		$(NO-OS)/drivers/api/no_os_timer.c
endif
