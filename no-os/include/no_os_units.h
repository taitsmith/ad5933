/***************************************************************************//**
 *   @file   no_os_fifo.h
 *   @brief  Header file of Units
 *   @author Antoniu Miclaus (antoniu.miclaus@analog.com)
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
#ifndef _NO_OS_UNITS_H_
#define _NO_OS_UNITS_H_

/******************************************************************************/
/********************** Macros and Constants Definitions **********************/
/******************************************************************************/
#define PETA	1000000000000000ULL
#define TERA	1000000000000ULL
#define GIGA	1000000000UL
#define MEGA	1000000UL
#define KILO	1000UL
#define HECTO	100UL
#define DECA	10UL
#define DECI	10UL
#define CENTI	100UL
#define MILLI	1000UL
#define MICRO	1000000UL
#define NANO	1000000000UL
#define PICO	1000000000000ULL
#define FEMTO	1000000000000000ULL

#define HZ_PER_KHZ		1000UL
#define KHZ_PER_MHZ		1000UL
#define HZ_PER_MHZ		1000000UL

#define MILLIWATT_PER_WATT	1000UL
#define MICROWATT_PER_MILLIWATT	1000UL
#define MICROWATT_PER_WATT	1000000UL

#endif // _NO_OS_UNITS_H_
