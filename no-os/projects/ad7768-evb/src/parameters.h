/***************************************************************************//**
 *   @file   parameters.h
 *   @brief  Platform dependent parameters.
 *   @author Antoniu Miclaus (antoniu.miclaus@analog.com)
********************************************************************************
 * Copyright 2020(c) Analog Devices, Inc.
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

#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#include <xparameters.h>

#define UART_BAUDRATE                           115200
#define SPI_DEVICE_ID				XPAR_PS7_SPI_0_DEVICE_ID
#define SPI_AD7768_CS				0
#define GPIO_DEVICE_ID				XPAR_PS7_GPIO_0_DEVICE_ID
#define GPIO_OFFSET					32 + 54
#define AD7768_DMA_BASEADDR			XPAR_AD7768_DMA_BASEADDR
#define ADC_DDR_BASEADDR			XPAR_DDR_MEM_BASEADDR + 0x800000
#define AD7768_ADC_BASEADDR			XPAR_AXI_AD7768_ADC_BASEADDR
#define UART_DEVICE_ID				XPAR_XUARTPS_0_DEVICE_ID
#define UART_IRQ_ID				XPAR_XUARTPS_1_INTR
#define INTC_DEVICE_ID				XPAR_SCUGIC_SINGLE_DEVICE_ID
#define GPIO_RESET_N				GPIO_OFFSET + 8
#define GPIO_START_N				GPIO_OFFSET + 9
#define GPIO_SYNC_IN_N				GPIO_OFFSET + 10
#define GPIO_SYNC_OUT_N				GPIO_OFFSET + 11
#define GPIO_MODE_0_GPIO_0			GPIO_OFFSET + 16
#define GPIO_MODE_1_GPIO_1			GPIO_OFFSET + 17
#define GPIO_MODE_2_GPIO_2			GPIO_OFFSET + 18
#define GPIO_MODE_3_GPIO_3			GPIO_OFFSET + 19
#define GPIO_FILTER_GPIO_4			GPIO_OFFSET + 20
#define AD7768_HEADER_SIZE			8
#define BITS_IN_BYTE				8
#define AD7768_EVB_REFERENCE_VOLT		4.096f

/* HDL Control Interface */

#define GPIO_UP_SSHOT				GPIO_OFFSET + 4
#define GPIO_UP_FORMAT_1			GPIO_OFFSET + 3
#define GPIO_UP_FORMAT_0			GPIO_OFFSET + 2
#define GPIO_UP_CRC_ENABLE			GPIO_OFFSET + 1
#define GPIO_UP_CRC_4_OR_16_N		GPIO_OFFSET + 0
#define GPIO_STATUS_DEVICE_ID		XPAR_AD7768_GPIO_DEVICE_ID
#define GPIO_STATUS_OFFSET			0
#define UP_STATUS_CLR_OFFSET		GPIO_STATUS_OFFSET + 0
#define UP_STATUS_OFFSET			GPIO_STATUS_OFFSET + 0

#endif /* _PARAMETERS_H_ */
