/**
 * \file
 *
 * \brief Sleep mode access
 *
 * Copyright (C) 2010 Atmel Corporation. All rights reserved.
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 * Atmel AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
#ifndef SLEEP_H
#define SLEEP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>

#ifndef AVR32_PM_SMODE_GMCLEAR_MASK
#define AVR32_PM_SMODE_GMCLEAR_MASK      0x80
#else
#warning Define already present in the system toolchain header files!
#endif

/**
 * \defgroup sleep_group Power Manager (PM)
 *
 * This is a stub on the AVR UC3 Power Manager(PM) for the sleepmgr service.
 *
 * \note To minimize the code overhead, these functions do not feature
 * interrupt-protected access since they are likely to be called inside
 * interrupt handlers or in applications where such protection is not
 * necessary. If such protection is needed, it must be ensured by the calling
 * code.
 *
 * @{
 */

#if defined(__DOXYGEN__)
/**
 * \brief Sets the MCU in the specified sleep mode
 * \param sleep_mode Sleep mode to set.
 */
#endif

#if (UC3A || UC3B)  // For AVR UC3 A0/A1, UC3 B, UC3 A3 series

# ifndef AVR32_PM_SMODE_DEEPSTOP
#  define AVR32_PM_SMODE_DEEPSTOP          0x00000004
# endif
# include "pm.h"
#elif UC3C          // For AVR UC3 C series
# include "pm_uc3c.h"
#elif UC3D          // For AVR UC3 D series
# include "pm_uc3d.h"
#elif UC3L          // For AVR UC3 L series
# include "pm_uc3l.h"
#else		
# error Unsupported AVR UC3 series.
#endif

static inline void pm_sleep(int sleep_mode)
{
	switch (sleep_mode) {
	case AVR32_PM_SMODE_IDLE:
		SLEEP(AVR32_PM_SMODE_IDLE);
		break;
	case AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_IDLE:
		SLEEP(AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_IDLE);
		break;
	case AVR32_PM_SMODE_FROZEN:
		SLEEP(AVR32_PM_SMODE_FROZEN);
		break;
	case AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_FROZEN:
		SLEEP(AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_FROZEN);
		break;
	case AVR32_PM_SMODE_STANDBY:
		SLEEP(AVR32_PM_SMODE_STANDBY);
		break;
	case AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_STANDBY:
		SLEEP(AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_STANDBY);
		break;
	case AVR32_PM_SMODE_STOP:
		SLEEP(AVR32_PM_SMODE_STOP);
		break;
	case AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_STOP:
		SLEEP(AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_STOP);
		break;
	case AVR32_PM_SMODE_DEEPSTOP:
		SLEEP(AVR32_PM_SMODE_DEEPSTOP);
		break;
	case AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_DEEPSTOP:
		SLEEP(AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_DEEPSTOP);
		break;
	case AVR32_PM_SMODE_STATIC:
		SLEEP(AVR32_PM_SMODE_STATIC);
		break;
	case AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_STATIC:
		SLEEP(AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_STATIC);
		break;
#if UC3L
	case AVR32_PM_SMODE_SHUTDOWN:
		SLEEP(AVR32_PM_SMODE_SHUTDOWN);
		break;
	case AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_SHUTDOWN:
		SLEEP(AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_SHUTDOWN);
		break;
#endif
	default:
		break;
	}
}


//! @}

#ifdef __cplusplus
}
#endif

#endif /* SLEEP_H */
