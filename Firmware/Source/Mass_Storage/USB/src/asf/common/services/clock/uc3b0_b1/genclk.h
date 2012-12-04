/**
 * \file
 *
 * \brief Chip-specific generic clock management
 *
 * Copyright (c) 2010-2011 Atmel Corporation. All rights reserved.
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
#ifndef CHIP_GENCLK_H_INCLUDED
#define CHIP_GENCLK_H_INCLUDED

#include <osc.h>
#include <pll.h>

/**
 * \weakgroup genclk_group
 * @{
 */

//! \name Chip-specific generic clock definitions
//@{

//! The max division factor applicable to the source clock of the generic clock
#define GENCLK_DIV_MAX    ((1 << AVR32_PM_GCCTRL_DIV_SIZE) * 2)

#ifndef __ASSEMBLY__

#include <stdint.h>
#include <avr32/io.h>

enum genclk_source {
	GENCLK_SRC_OSC0   = 0,    //!< Oscillator 0
	GENCLK_SRC_OSC1   = 1,    //!< Oscillator 1
	GENCLK_SRC_PLL0   = 2,    //!< PLL 0
	GENCLK_SRC_PLL1   = 3,    //!< PLL 1
};

//@}

struct genclk_config {
	uint32_t ctrl;
};

static inline void genclk_config_defaults(struct genclk_config *cfg,
		unsigned int id)
{
	cfg->ctrl = 0;
}

static inline void genclk_config_read(struct genclk_config *cfg,
		unsigned int id)
{
	cfg->ctrl = AVR32_PM.gcctrl[id];
}

static inline void genclk_config_write(const struct genclk_config *cfg,
		unsigned int id)
{
	AVR32_PM.gcctrl[id] = cfg->ctrl;
}

static inline void genclk_config_set_source(struct genclk_config *cfg,
		enum genclk_source src)
{
	uint32_t mask;

	mask = AVR32_PM_GCCTRL_OSCSEL_MASK | AVR32_PM_GCCTRL_PLLSEL_MASK;
	Assert(!(src & ~mask));

	cfg->ctrl = (cfg->ctrl & ~mask) | (src << AVR32_PM_GCCTRL_OSCSEL);
}

static inline void genclk_config_set_divider(struct genclk_config *cfg,
		unsigned int divider)
{
	Assert((divider > 0) && (divider <= GENCLK_DIV_MAX));

	/* Clear all the bits we're about to modify */
	cfg->ctrl &= ~(AVR32_PM_GCCTRL_DIVEN_MASK | AVR32_PM_GCCTRL_DIV_MASK);

	if (divider > 1) {
		cfg->ctrl |= 1U << AVR32_PM_GCCTRL_DIVEN;
		cfg->ctrl |= ((divider >> 1) - 1) << AVR32_PM_GCCTRL_DIV;
	}
}

static inline void genclk_enable(const struct genclk_config *cfg,
		unsigned int id)
{
	AVR32_PM.gcctrl[id] = cfg->ctrl | (1U << AVR32_PM_GCCTRL_CEN);
}

static inline void genclk_disable(unsigned int id)
{
	AVR32_PM.gcctrl[id] = 0;
}

static inline void genclk_enable_source(enum genclk_source src)
{
	switch (src) {
#ifdef BOARD_OSC0_HZ
	case GENCLK_SRC_OSC0:
		if (!osc_is_ready(OSC_ID_OSC0)) {
			osc_enable(OSC_ID_OSC0);
			osc_wait_ready(OSC_ID_OSC0);
		}
		break;
#endif

#ifdef BOARD_OSC1_HZ
	case GENCLK_SRC_OSC1:
		if (!osc_is_ready(OSC_ID_OSC1)) {
			osc_enable(OSC_ID_OSC1);
			osc_wait_ready(OSC_ID_OSC1);
		}
		break;
#endif

#ifdef CONFIG_PLL0_SOURCE
	case GENCLK_SRC_PLL0: {
		pll_enable_config_defaults(0);
		break;
	}
#endif

#ifdef CONFIG_PLL1_SOURCE
	case GENCLK_SRC_PLL1: {
		pll_enable_config_defaults(1);
		break;
	}
#endif

	default:
		Assert(false);
		break;
	}
}

#endif /* __ASSEMBLY__ */

//! @}

#endif /* CHIP_GENCLK_H_INCLUDED */
