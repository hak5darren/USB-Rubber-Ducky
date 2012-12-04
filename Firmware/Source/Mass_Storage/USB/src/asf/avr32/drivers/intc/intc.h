/**
 * \file
 *
 * \brief INTC software driver API for AVR UC3 devices.
 *
 * Copyright (c) 2009-2011 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 *    AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#ifndef _INTC_H_
#define _INTC_H_

#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup intc_group INTC Software Driver API for AVR UC3
 *
 * This is a software module to register interrupt handlers at any specified
 * interrupt level to any interrupt line managed by the INTC module in AVR UC3
 * devices.
 * @{
 */

//! Maximal number of interrupt request lines per group.
#define AVR32_INTC_MAX_NUM_IRQS_PER_GRP      32

//! Number of interrupt priority levels.
#define AVR32_INTC_NUM_INT_LEVELS            (1 << AVR32_INTC_IPR_INTLEVEL_SIZE)


#ifdef __AVR32_ABI_COMPILER__
// (Automatically defined when compiling for AVR UC3, not when assembling).

extern void INTC_init_interrupts(void);
extern void INTC_register_interrupt(__int_handler handler, uint32_t irq,
		uint32_t int_level);

#endif  // __AVR32_ABI_COMPILER__

//! @}

#ifdef __cplusplus
}
#endif

#endif  // _INTC_H_
