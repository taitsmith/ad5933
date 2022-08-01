/***************************************************************************//**
 *   @file   parameters.h
 *   @brief  Definitions specific to STM32 platform used by ad74413r
 *           project.
 *   @author Ciprian Regus (ciprian.regus@analog.com)
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
#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include "stm32_hal.h"
#include "stm32_irq.h"
#include "stm32_spi.h"
#include "stm32_gpio.h"
#include "stm32_uart.h"
#include "stm32_uart_stdio.h"
#include "stm32_gpio_irq.h"

/******************************************************************************/
/********************** Macros and Constants Definitions **********************/
/******************************************************************************/
extern UART_HandleTypeDef huart3;

#ifdef IIO_SUPPORT
#define INTC_DEVICE_ID  0
#define IIO_APP_HUART   (&huart3)
#define UART_IRQ_ID     USART3_IRQn
#endif

#define UART_DEVICE_ID  3
#define UART_BAUDRATE   115200
#define UART_EXTRA      &ad74413r_uart_extra_ip

#define SPI_DEVICE_ID   1
#define SPI_BAUDRATE    1000000
#define SPI_CS          14
#define SPI_CS_PORT     GPIOD
#define SPI_OPS         &stm32_spi_ops
#define SPI_EXTRA       &ad74413r_spi_extra_ip

extern struct stm32_uart_init_param ad74413r_uart_extra_ip;
extern struct stm32_spi_init_param ad74413r_spi_extra_ip;

#ifdef IIO_TRIGGER_EXAMPLE
extern struct stm32_gpio_irq_init_param ad74413r_gpio_irq_extra_ip;
/* Setting for PortG Pin0 used for DATA_READY.
   Has to be adapted accordingly if another pin is used.
 */
#define AD74413R_GPIO_TRIG_IRQ_ID     0    /* Not used in stm32 platform */
#define AD74413R_GPIO_CB_HANDLE       NULL /* Not used in stm32 platform */

#define GPIO_IRQ_ID             0 /* Pin 0 */
#define GPIO_IRQ_OPS            &stm32_gpio_irq_ops
#define GPIO_IRQ_EXTRA          &ad74413r_gpio_irq_extra_ip
#endif

#endif /* __PARAMETERS_H__ */
