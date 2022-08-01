ifeq (y,$(strip $(IIO_EXAMPLE)))
TINYIIOD=y
CFLAGS += -DIIO_EXAMPLE=1
SRCS += $(PROJECT)/src/examples/iio_example/iio_example.c
INCS += $(PROJECT)/src/examples/iio_example/iio_example.h
endif

ifeq (y,$(strip $(DUMMY_EXAMPLE)))
CFLAGS += -DDUMMY_EXAMPLE=1
SRCS += $(PROJECT)/src/examples/dummy/dummy_example.c
INCS += $(PROJECT)/src/examples/dummy/dummy_example.h
endif

ifeq (y,$(strip $(TINYIIOD)))
SRC_DIRS += $(NO-OS)/iio/iio_app

SRCS += $(DRIVERS)/accel/adxl367/iio_adxl367.c \
	$(DRIVERS)/api/no_os_irq.c \
	$(PLATFORM_DRIVERS)/no_os_uart.c \
	$(NO-OS)/util/no_os_fifo.c

INCS +=	$(DRIVERS)/accel/adxl367/iio_adxl367.h \
	$(INCLUDE)/no_os_uart.h \
	$(INCLUDE)/no_os_irq.h \
	$(INCLUDE)/no_os_fifo.h \
	$(INCLUDE)/no_os_lf256fifo.h
endif
