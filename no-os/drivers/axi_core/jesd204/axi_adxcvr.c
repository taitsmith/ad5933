/***************************************************************************//**
 *   @file   axi_adxcvr.c
 *   @brief  Driver for the ADI AXI-ADXCVR Module.
 *   @author DBogdan (dragos.bogdan@analog.com)
********************************************************************************
 * Copyright 2018(c) Analog Devices, Inc.
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
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "no_os_axi_io.h"
#include "no_os_util.h"
#include "no_os_error.h"
#include "no_os_delay.h"
#include "xilinx_transceiver.h"
#include "axi_adxcvr.h"
#include "no_os_print_log.h"

/******************************************************************************/
/********************** Macros and Constants Definitions **********************/
/******************************************************************************/
#define ADXCVR_REG_RESETN		0x0010
#define ADXCVR_RESETN			(1 << 0)

#define ADXCVR_REG_STATUS		0x0014
#define ADXCVR_STATUS			(1 << 0)

#define ADXCVR_REG_CONTROL		0x0020
#define ADXCVR_LPM_DFE_N		(1 << 12)
#define ADXCVR_RATE(x)			(((x) & 0x7) << 8)
#define ADXCVR_SYSCLK_SEL(x)	(((x) & 0x3) << 4)
#define ADXCVR_OUTCLK_SEL(x)	(((x) & 0x7) << 0)

#define ADXCVR_REG_SYNTH		0x24

#define ADXCVR_REG_DRP_SEL(x)		(0x0040 + (x))

#define ADXCVR_REG_DRP_CTRL(x)		(0x0044 + (x))
#define ADXCVR_DRP_CTRL_WR			(1 << 28)
#define ADXCVR_DRP_CTRL_ADDR(x)		(((x) & 0xFFF) << 16)
#define ADXCVR_DRP_CTRL_WDATA(x)	(((x) & 0xFFFF) << 0)

#define ADXCVR_REG_DRP_STATUS(x)	(0x0048 + (x))
#define ADXCVR_DRP_STATUS_BUSY		(1 << 16)
#define ADXCVR_DRP_STATUS_RDATA(x)	(((x) & 0xFFFF) << 0)

#define ADXCVR_DRP_PORT_ADDR_COMMON		0x00
#define ADXCVR_DRP_PORT_ADDR_CHANNEL	0x20

#define ADXCVR_DRP_PORT_COMMON(x)		(x)
#define ADXCVR_DRP_PORT_CHANNEL(x)		(0x100 + (x))

#define ADXCVR_BROADCAST				0xff

/**
 * @brief AXI ADXCVR Write
 * @param xcvr - Device Structure.
 * @param reg_addr - The register address.
 * @param reg_val - Data value to write.
 * @return Returns 0 in case of success or negative error code otherwise.
 */
int32_t adxcvr_write(struct adxcvr *xcvr,
		     uint32_t reg_addr,
		     uint32_t reg_val)
{
	no_os_axi_io_write(xcvr->base, reg_addr, reg_val);

	return 0;
}

/**
 * @brief AXI ADXCVR Read
 * @param xcvr - Device Structure.
 * @param reg_addr - The register address.
 * @param reg_val - Data read from the device.
 * @return Returns 0 in case of success or negative error code otherwise.
 */
int32_t adxcvr_read(struct adxcvr *xcvr,
		    uint32_t reg_addr,
		    uint32_t *reg_val)
{
	no_os_axi_io_read(xcvr->base, reg_addr, reg_val);

	return 0;
}

/**
 * @brief Read AXI ADXCVR DRP status
 * @param xcvr - Device Structure.
 * @param drp_addr - DRP Port address.
 * @return Returns status in case of success or negative error code otherwise.
 */
int32_t adxcvr_drp_wait_idle(struct adxcvr *xcvr,
			     uint32_t drp_addr)
{
	uint32_t val;
	int32_t timeout = 20;

	do {
		adxcvr_read(xcvr, ADXCVR_REG_DRP_STATUS(drp_addr), &val);
		if (!(val & ADXCVR_DRP_STATUS_BUSY))
			return ADXCVR_DRP_STATUS_RDATA(val);

		no_os_mdelay(1);
	} while (timeout--);

	printf("%s: %s: Timeout!", xcvr->name, __func__);

	return -1;
}

/**
 * @brief AXI ADXCVR DPR Port Read
 * @param xcvr - The device structure.
 * @param drp_port - The DRP Port.
 * @param reg - DRP Register address.
 * @param val - Data read.
 * @return Returns 0 in case of success or negative error code otherwise.
 */
int32_t adxcvr_drp_read(struct adxcvr *xcvr,
			uint32_t drp_port,
			uint32_t reg,
			uint32_t *val)
{
	uint32_t drp_sel, drp_addr;
	int32_t ret;

	if (drp_port < ADXCVR_DRP_PORT_CHANNEL(0))
		drp_addr = ADXCVR_DRP_PORT_ADDR_COMMON;
	else
		drp_addr = ADXCVR_DRP_PORT_ADDR_CHANNEL;

	drp_sel = drp_port & 0xFF;

	adxcvr_write(xcvr, ADXCVR_REG_DRP_SEL(drp_addr), drp_sel);
	adxcvr_write(xcvr, ADXCVR_REG_DRP_CTRL(drp_addr), ADXCVR_DRP_CTRL_ADDR(reg));

	ret = adxcvr_drp_wait_idle(xcvr, drp_addr);
	if (ret < 0)
		return ret;

	*val = ret & 0xffff;

	return 0;
}

/**
 * @brief AXI ADXCVR DPR Port Write
 * @param xcvr - The device structure.
 * @param drp_port - The DRP Port.
 * @param reg - DRP Register address.
 * @param val - Data to be written.
 * @return Returns 0 in case of success or negative error code otherwise.
 */
int32_t adxcvr_drp_write(struct adxcvr *xcvr,
			 uint32_t drp_port,
			 uint32_t reg,
			 uint32_t val)
{
	uint32_t drp_sel, drp_addr;
	int32_t ret;

	if (drp_port < ADXCVR_DRP_PORT_CHANNEL(0))
		drp_addr = ADXCVR_DRP_PORT_ADDR_COMMON;
	else
		drp_addr = ADXCVR_DRP_PORT_ADDR_CHANNEL;

	drp_sel = drp_port & 0xFF;

	adxcvr_write(xcvr, ADXCVR_REG_DRP_SEL(drp_addr), drp_sel);
	adxcvr_write(xcvr, ADXCVR_REG_DRP_CTRL(drp_addr), (ADXCVR_DRP_CTRL_WR |
			ADXCVR_DRP_CTRL_ADDR(reg) | ADXCVR_DRP_CTRL_WDATA(val)));

	ret = adxcvr_drp_wait_idle(xcvr, drp_addr);
	if (ret < 0)
		return ret;

	return 0;
}

/**
 * @brief AXI ADXCVR Clock Set Rate
 * @param xcvr - The device structure.
 * @param rate - The output rate (kHz).
 * @param parent_rate - The parent rate (kHz).
 * @return Returns 0 in case of success or negative error code otherwise.
 */
int adxcvr_clk_set_rate(struct adxcvr *xcvr,
			uint32_t rate,
			uint32_t parent_rate
		       )
{
	struct xilinx_xcvr_cpll_config cpll_conf;
	struct xilinx_xcvr_qpll_config qpll_conf;
	uint32_t out_div, clk25_div, prog_div;
	uint32_t i;
	int ret;

	pr_debug("%s: Rate %lu Hz Parent Rate %lu Hz\n",
		 __func__, rate, parent_rate);

	clk25_div = NO_OS_DIV_ROUND_CLOSEST(parent_rate, 25000);

	if (xcvr->cpll_enable)
		ret = xilinx_xcvr_calc_cpll_config(&xcvr->xlx_xcvr, parent_rate, rate,
						   &cpll_conf, &out_div);
	else
		ret = xilinx_xcvr_calc_qpll_config(&xcvr->xlx_xcvr, xcvr->sys_clk_sel,
						   parent_rate, rate, &qpll_conf, &out_div);
	if (ret < 0)
		return ret;

	for (i = 0; i < xcvr->num_lanes; i++) {

		if (xcvr->cpll_enable)
			ret = xilinx_xcvr_cpll_write_config(&xcvr->xlx_xcvr,
							    ADXCVR_DRP_PORT_CHANNEL(i), &cpll_conf);
		else if ((i % 4 == 0) && xcvr->qpll_enable)
			ret = xilinx_xcvr_qpll_write_config(&xcvr->xlx_xcvr,
							    xcvr->sys_clk_sel,
							    ADXCVR_DRP_PORT_COMMON(i), &qpll_conf);
		if (ret < 0)
			return ret;

		ret = xilinx_xcvr_write_out_div(&xcvr->xlx_xcvr,
						ADXCVR_DRP_PORT_CHANNEL(i),
						xcvr->tx_enable ? -1 : (int32_t)out_div,
						xcvr->tx_enable ? (int32_t)out_div : -1);
		if (ret < 0)
			return ret;

		if (xcvr->out_clk_sel == ADXCVR_PROGDIV_CLK) {
			unsigned int max_progdiv, div = 1, ratio;

			if (xcvr->xlx_xcvr.encoding == ENC_66B64B)
				ratio = 66;
			else
				ratio = 40;

			/* Set RX|TX_PROGDIV_RATE = 2 on GTY4 */
			ret = xilinx_xcvr_write_prog_div_rate(&xcvr->xlx_xcvr,
							      ADXCVR_DRP_PORT_CHANNEL(i),
							      xcvr->tx_enable ? -1 : 2,
							      xcvr->tx_enable ? 2 : -1);
			if (!ret)
				div = 2;

			switch (xcvr->xlx_xcvr.type) {
			case XILINX_XCVR_TYPE_US_GTH3:
				max_progdiv = 100;
				/* This is done in the FPGA fabric */
				if (xcvr->xlx_xcvr.encoding == ENC_66B64B)
					div = 2;
				break;
			case XILINX_XCVR_TYPE_US_GTH4:
				max_progdiv = 132;
				/* This is done in the FPGA fabric */
				if (xcvr->xlx_xcvr.encoding == ENC_66B64B)
					div = 2;
				break;
			case XILINX_XCVR_TYPE_US_GTY4:
				max_progdiv = 100;
				break;
			default:
				return -EINVAL;
			}

			prog_div = NO_OS_DIV_ROUND_CLOSEST(ratio * out_div, 2 * div);

			if (prog_div > max_progdiv) {
				prog_div = 0; /* disabled */
				pr_info("%s: No PROGDIV divider found for OUTDIV=%lu, disabling output!\n",
					__func__, out_div);
			}

			ret = xilinx_xcvr_write_prog_div(&xcvr->xlx_xcvr,
							 ADXCVR_DRP_PORT_CHANNEL(i),
							 xcvr->tx_enable ? -1 : (int32_t)prog_div,
							 xcvr->tx_enable ? (int32_t)prog_div : -1);
			if (ret < 0)
				return ret;
		}

		if (!xcvr->tx_enable) {
			ret = xilinx_xcvr_configure_cdr(&xcvr->xlx_xcvr,
							ADXCVR_DRP_PORT_CHANNEL(i), rate, out_div,
							xcvr->lpm_enable);
			if (ret < 0)
				return ret;

			ret = xilinx_xcvr_write_rx_clk25_div(&xcvr->xlx_xcvr,
							     ADXCVR_DRP_PORT_CHANNEL(i), clk25_div);
		} else {
			ret = xilinx_xcvr_write_tx_clk25_div(&xcvr->xlx_xcvr,
							     ADXCVR_DRP_PORT_CHANNEL(i), clk25_div);
		}

		if (ret < 0)
			return ret;
	}


	xcvr->lane_rate_khz = rate;

	return 0;
}

/**
 * @brief AXI ADXCVR Status Read
 * @param xcvr - The device structure.
 * @return Returns 0 in case of success or negative error code otherwise.
 */
int32_t adxcvr_status_error(struct adxcvr *xcvr)
{
	int32_t timeout = 100;
	uint32_t status;

	do {
		no_os_mdelay(1);
		adxcvr_read(xcvr, ADXCVR_REG_STATUS, &status);
	} while ((timeout--) && (status == 0));

	if (!status)
		return -1;

	printf("%s: OK (%"PRId32" kHz)\n", xcvr->name, xcvr->lane_rate_khz);

	return 0;
}

/**
 * @brief AXI ADXCVR Clock Enable
 * @param xcvr - The device structure.
 * @return Returns 0 in case of success or negative error code otherwise.
 */
int32_t adxcvr_clk_enable(struct adxcvr *xcvr)
{
	adxcvr_write(xcvr, ADXCVR_REG_RESETN, ADXCVR_RESETN);
	no_os_mdelay(100);

	return adxcvr_status_error(xcvr);
}

/**
 * @brief AXI ADXCVR Clock Disable
 * @param xcvr - The device structure.
 * @return Returns 0 in case of success or negative error code otherwise.
 */
int32_t adxcvr_clk_disable(struct adxcvr *xcvr)
{
	adxcvr_write(xcvr, ADXCVR_REG_RESETN, 0);

	return 0;
}

/**
 * @brief AXI ADXCVR Get Information
 * @param xcvr - The device structure.
 */
static void adxcvr_get_info(struct adxcvr *xcvr)
{
	uint32_t reg_value;

	adxcvr_read(xcvr, AXI_REG_FPGA_INFO, &reg_value);
	xcvr->xlx_xcvr.tech = AXI_INFO_FPGA_TECH(reg_value);
	xcvr->xlx_xcvr.family = AXI_INFO_FPGA_FAMILY(reg_value);
	xcvr->xlx_xcvr.speed_grade = AXI_INFO_FPGA_SPEED_GRADE(reg_value);
	xcvr->xlx_xcvr.dev_package = AXI_INFO_FPGA_DEV_PACKAGE(reg_value);

	adxcvr_read(xcvr, AXI_REG_FPGA_VOLTAGE, &reg_value);
	xcvr->xlx_xcvr.voltage = AXI_INFO_FPGA_VOLTAGE(reg_value);
}

/**
 * @brief AXI ADXCVR Device Initialization
 * @param ad_xcvr - The device structure.
 * @param init - The structure containing the device initial parameters.
 * @return Returns 0 in case of success or negative error code otherwise.
 */
int32_t adxcvr_init(struct adxcvr **ad_xcvr,
		    const struct adxcvr_init *init)
{
	struct adxcvr *xcvr;
	uint32_t synth_conf, xcvr_type;
	uint32_t i;
	int32_t ret;

	xcvr = (struct adxcvr *)calloc(1, sizeof(*xcvr));
	if (!xcvr)
		return -1;

	xcvr->base = init->base;
	xcvr->name = init->name;
	xcvr->sys_clk_sel = init->sys_clk_sel;
	xcvr->out_clk_sel = init->out_clk_sel;
	if (init->sys_clk_sel == ADXCVR_SYS_CLK_CPLL)
		xcvr->cpll_enable = 1;
	else
		xcvr->cpll_enable = 0;
	xcvr->lpm_enable = init->lpm_enable;

	xcvr->lane_rate_khz = init->lane_rate_khz;
	xcvr->ref_rate_khz = init->ref_rate_khz;

	adxcvr_read(xcvr, ADXCVR_REG_SYNTH, &synth_conf);
	xcvr->tx_enable = (synth_conf >> 8) & 1;
	xcvr->num_lanes = synth_conf & 0xff;
	xcvr->qpll_enable = (synth_conf >> 20) & 1;

	if ((!xcvr->qpll_enable) && (init->sys_clk_sel != ADXCVR_SYS_CLK_CPLL))
		pr_info("%s: Using QPLL with previously defined settings.\n", xcvr->name);

	xcvr_type = (synth_conf >> 16) & 0xf;

	adxcvr_read(xcvr, AXI_REG_VERSION, &xcvr->xlx_xcvr.version);
	if (AXI_PCORE_VER_MAJOR(xcvr->xlx_xcvr.version) > 0x10)
		adxcvr_get_info(xcvr);

	/* Ensure compliance with legacy xcvr type */
	if (AXI_PCORE_VER_MAJOR(xcvr->xlx_xcvr.version) <= 0x10) {
		switch (xcvr_type) {
		case XILINX_XCVR_LEGACY_TYPE_S7_GTX2:
			xcvr->xlx_xcvr.type = XILINX_XCVR_TYPE_S7_GTX2;
			break;
		case XILINX_XCVR_LEGACY_TYPE_US_GTH3:
			xcvr->xlx_xcvr.type = XILINX_XCVR_TYPE_US_GTH3;
			break;
		case XILINX_XCVR_LEGACY_TYPE_US_GTH4:
			xcvr->xlx_xcvr.type = XILINX_XCVR_TYPE_US_GTH4;
			break;
		case XILINX_XCVR_LEGACY_TYPE_US_GTY4:
			xcvr->xlx_xcvr.type = XILINX_XCVR_TYPE_US_GTY4;
			break;
		default:
			goto err;
		}
	} else
		xcvr->xlx_xcvr.type = xcvr_type;

	switch (xcvr->xlx_xcvr.type) {
	case XILINX_XCVR_TYPE_S7_GTX2:
	case XILINX_XCVR_TYPE_US_GTH3:
	case XILINX_XCVR_TYPE_US_GTH4:
	case XILINX_XCVR_TYPE_US_GTY4:
		break;
	default:
		printf("Unknown transceiver type: %d\n", xcvr->xlx_xcvr.type);
		goto err;
	}

	xcvr->xlx_xcvr.encoding = ENC_8B10B;
	xcvr->xlx_xcvr.refclk_ppm = PM_200; /* TODO use clock accuracy */

	adxcvr_write(xcvr, ADXCVR_REG_RESETN, 0);

	adxcvr_write(xcvr, ADXCVR_REG_CONTROL,
		     ((xcvr->lpm_enable ? ADXCVR_LPM_DFE_N : 0) |
		      ADXCVR_SYSCLK_SEL(xcvr->sys_clk_sel) |
		      ADXCVR_OUTCLK_SEL(xcvr->out_clk_sel)));

	xcvr->xlx_xcvr.ad_xcvr = xcvr;

	if (!xcvr->tx_enable) {
		for (i = 0; i < xcvr->num_lanes; i++) {
			xilinx_xcvr_configure_lpm_dfe_mode(&xcvr->xlx_xcvr,
							   ADXCVR_DRP_PORT_CHANNEL(i),
							   xcvr->lpm_enable);
		}
	}

	if (xcvr->lane_rate_khz && xcvr->ref_rate_khz) {
		ret = adxcvr_clk_set_rate(xcvr, xcvr->lane_rate_khz, xcvr->ref_rate_khz);
		if (ret)
			goto err;
	}

	*ad_xcvr = xcvr;

	return 0;

err:
	free(xcvr);

	return -1;
}

/**
 * @brief Free resoulces allocated for AXI_ADXCVR
 * @param xcvr - The device structure.
 * @return Returns 0 in case of success or negative error code.
 */
int32_t adxcvr_remove(struct adxcvr *xcvr)
{
	free(xcvr);

	return 0;
}
