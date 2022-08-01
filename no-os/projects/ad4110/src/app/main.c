/***************************************************************************//**
 *   @file   ad4110/src/app/main.c
 *   @brief  Implementation of Main Function.
 *   @author Porumb Andrei (andrei.porumb@analog.com)
********************************************************************************
 * Copyright 2021(c) Analog Devices, Inc.
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
#include "no_os_irq.h"
#include "irq_extra.h"
#include "gpio_irq_extra.h"
#include "no_os_spi.h"
#include "spi_extra.h"
#include "ad4110.h"
#include "no_os_error.h"
#include "xparameters.h"
#include "parameters.h"
#include "no_os_print_log.h"
#include <stdint.h>
#include <inttypes.h>
#include <xil_cache.h>

static uint32_t data_buf[BUF_LENGTH];

/***************************************************************************//**
 * @brief main
*******************************************************************************/
int main()
{
	uint32_t ret;
	int32_t i;

	struct xil_spi_init_param spi_extra = {
		.type = SPI_PS,
		.flags = 0U
	};
	struct no_os_spi_init_param spi_ip = {
		.device_id = SPI_DEVICE_ID,
		.max_speed_hz = 100000,
		.mode = NO_OS_SPI_MODE_0,
		.chip_select = 0U,
		.bit_order = NO_OS_SPI_BIT_ORDER_MSB_FIRST,
		.platform_ops = &xil_spi_ops,
		.extra = &spi_extra
	};

	/* Enable the instruction cache. */
	Xil_ICacheEnable();
	/* Enable the data cache. */
	Xil_DCacheEnable();

	/* IRQ instance. */
	struct no_os_irq_ctrl_desc *irq_desc;
	struct xil_irq_init_param irq_extra = {
		.type = IRQ_PS
	};
	struct no_os_irq_init_param irq_ip = {
		.irq_ctrl_id = 0U,
		.platform_ops = &xil_irq_ops,
		.extra = &irq_extra
	};

	ret = no_os_irq_ctrl_init(&irq_desc, &irq_ip);
	if(ret)
		return -1;
	ret = no_os_irq_global_enable(irq_desc);
	if(ret)
		return -1;

	/* GPIO IRQ instance. */
	struct no_os_irq_ctrl_desc *gpio_irq_desc;
	struct xil_gpio_irq_init_param gpio_irq_extra = {
		.parent_desc = irq_desc,
		.gpio_device_id = XPAR_PS7_GPIO_0_DEVICE_ID
	};
	struct no_os_irq_init_param gpio_irq_ip = {
		.irq_ctrl_id = GPIO_IRQ_ID,
		.platform_ops = &xil_gpio_irq_ops,
		.extra = &gpio_irq_extra
	};

	ret = no_os_irq_ctrl_init(&gpio_irq_desc, &gpio_irq_ip);
	if(ret)
		return -1;

	/* Device AD4110 instance. */
	struct ad4110_dev *ad4110_dev;
	struct ad4110_init_param ad4110_dev_ip = {
		.spi_init = spi_ip,
		.volt_ref = AD4110_INT_2_5V_REF,
		.data_stat = AD4110_ENABLE,
		.data_length = AD4110_DATA_WL24,
		.afe_crc_en = AD4110_AFE_CRC,
		.adc_crc_en = AD4110_ADC_CRC_CRC,
		.op_mode = AD4110_VOLTAGE_MODE,
		.gain = AD4110_GAIN_0_5,
		.sync = AD4110_SYNC_DIS,
		.afe_clk = AD4110_AFE_ADC_CLOCKED,
		.adc_clk = AD4110_ADC_INT_CLK_CLKIO,
		.addr = 0U,
		.irq_desc = gpio_irq_desc,
		.nready_pin = NREADY_PIN
	};

	ret = ad4110_setup(&ad4110_dev, ad4110_dev_ip);
	if(ret)
		return -1;

	ret = ad4110_continuous_read(ad4110_dev, data_buf, BUF_LENGTH);
	if(ret)
		return -1;

	for(i=0; i<BUF_LENGTH; i++)
		printf("DATA[%"PRIi32"] = %"PRIi32" \n", i, data_buf[i]);

	/* Disable the instruction cache. */
	Xil_DCacheDisable();
	/* Disable the data cache. */
	Xil_ICacheDisable();

	return 0;
}
