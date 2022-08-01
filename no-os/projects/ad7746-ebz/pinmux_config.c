/*
 **
 ** Source file generated on April 5, 2021 at 10:17:10.
 **
 ** Copyright (C) 2011-2021 Analog Devices Inc., All Rights Reserved.
 **
 ** This file is generated automatically based upon the options selected in
 ** the Pin Multiplexing configuration editor. Changes to the Pin Multiplexing
 ** configuration should be made by changing the appropriate options rather
 ** than editing this file.
 **
 ** Selected Peripherals
 ** --------------------
 ** I2C0 (SCL0, SDA0)
 ** UART0 (Tx, Rx, UART_SOUT_EN)
 **
 ** GPIO (unavailable)
 ** ------------------
 ** P0_04, P0_05, P0_10, P0_11, P0_12
 */

#include <sys/platform.h>
#include <stdint.h>

#define I2C0_SCL0_PORTP0_MUX  ((uint16_t) ((uint16_t) 1<<8))
#define I2C0_SDA0_PORTP0_MUX  ((uint16_t) ((uint16_t) 1<<10))
#define UART0_TX_PORTP0_MUX  ((uint32_t) ((uint32_t) 1<<20))
#define UART0_RX_PORTP0_MUX  ((uint32_t) ((uint32_t) 1<<22))
#define UART0_UART_SOUT_EN_PORTP0_MUX  ((uint32_t) ((uint32_t) 3<<24))

int32_t adi_initpinmux(void);

/*
 * Initialize the Port Control MUX Registers
 */
int32_t adi_initpinmux(void)
{
	/* PORTx_MUX registers */
	*((volatile uint32_t *)REG_GPIO0_CFG) = I2C0_SCL0_PORTP0_MUX |
						I2C0_SDA0_PORTP0_MUX
						| UART0_TX_PORTP0_MUX | UART0_RX_PORTP0_MUX | UART0_UART_SOUT_EN_PORTP0_MUX;

	return 0;
}

