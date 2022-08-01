/***************************************************************************//**
 *   @file   common_data.c
 *   @brief  Defines common data to be used by eval-adxrs290-pmdz examples.
 *   @author RBolboac (ramona.bolboaca@analog.com)
********************************************************************************
 * Copyright 2022(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include "common_data.h"

/******************************************************************************/
/********************** Macros and Constants Definitions **********************/
/******************************************************************************/
struct no_os_spi_init_param adxrs290_spi_ip = {
	.device_id = SPI_DEVICE_ID,
	.max_speed_hz = SPI_BAUDRATE,
	.bit_order = NO_OS_SPI_BIT_ORDER_MSB_FIRST,
	.mode = NO_OS_SPI_MODE_3,
	.platform_ops = SPI_OPS,
	.chip_select = SPI_CS,
	.extra = SPI_EXTRA,
};

/* Initialization for Sync pin */
struct no_os_gpio_init_param adxrs290_gpio_sync_ip = {
	.port = GPIO_SYNC_PORT_NUM,
	.number = GPIO_SYNC_PIN_NUM,
	.pull = NO_OS_PULL_NONE,
	.platform_ops = GPIO_OPS,
	.extra = GPIO_EXTRA
};

struct adxrs290_init_param adxrs290_ip = {
	.mode = ADXRS290_MODE_MEASUREMENT,
	.gpio_sync = &adxrs290_gpio_sync_ip,
	.lpf = ADXRS290_LPF_480HZ,
	.hpf = ADXRS290_HPF_ALL_PASS
};

#ifdef IIO_TRIGGER_EXAMPLE
struct no_os_irq_init_param adxrs290_gpio_irq_ip = {
	.irq_ctrl_id = GPIO_IRQ_ID,
	.platform_ops = GPIO_IRQ_OPS,
	.extra = GPIO_IRQ_EXTRA,
};

const struct iio_hw_trig_cb_info gpio_cb_info = {
	.event = NO_OS_EVT_GPIO,
	.peripheral = NO_OS_GPIO_IRQ,
	.handle = ADXRS290_GPIO_CB_HANDLE,
};

struct iio_hw_trig_init_param adxrs290_gpio_trig_ip = {
	.irq_id = ADXRS290_GPIO_TRIG_IRQ_ID,
	.irq_trig_lvl = NO_OS_IRQ_LEVEL_HIGH,
	.cb_info = gpio_cb_info,
	.name = ADXRS290_GPIO_TRIG_NAME,
};
#endif

#ifdef IIO_TIMER_TRIGGER_EXAMPLE
/* ADXRS290 timer init parameter */
struct no_os_timer_init_param adxrs290_tip = {
	.id = ADXRS290_TIMER_DEVICE_ID,
	.freq_hz = ADXRS290_TIMER_FREQ_HZ,
	.ticks_count = ADXRS290_TIMER_TICKS_COUNT,
	.platform_ops = TIMER_OPS,
	.extra = ADXRS290_TIMER_EXTRA,
};

/* ADXRS290 timer irq init parameter */
struct no_os_irq_init_param adxrs290_timer_irq_ip = {
	.irq_ctrl_id = ADXRS290_TIMER_IRQ_ID,
	.platform_ops = TIMER_IRQ_OPS,
	.extra = ADADXRS290_TIMER_IRQ_EXTRA,
};

/* ADXRS290 timer trigger init parameter */
struct iio_hw_trig_init_param adxrs290_timer_trig_ip = {
	.irq_id = ADXRS290_TIMER_TRIG_IRQ_ID,
	.cb_info = {
		.event = NO_OS_EVT_TIM_ELAPSED,
		.peripheral = NO_OS_TIM_IRQ,
		.handle = ADXRS290_TIMER_CB_HANDLE,
	},
	.name = ADXRS290_TIMER_TRIG_NAME,
};

#endif
