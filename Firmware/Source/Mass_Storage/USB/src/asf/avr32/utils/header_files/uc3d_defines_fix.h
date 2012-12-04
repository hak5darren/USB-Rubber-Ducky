/**
 * \file
 *
 * \brief Missing Toolchain Definition for UC3 D header files
 *
 * Copyright (c) 2011 Atmel Corporation. All rights reserved.
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

#ifndef _UC3D_DEFINES_FIX_
#define _UC3D_DEFINES_FIX_

#if (UC3D)

//  These defines are missing from or wrong in the toolchain header file ip_xxx.h or part.h
#ifndef AVR32_SCIF_GC_NO_DIV_CLOCK
#define AVR32_SCIF_GC_NO_DIV_CLOCK           0
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // end AVR32_SCIF_GC_NO_DIV_CLOCK

#ifndef AVR32_SCIF_GCLK_ADCIFD
#define AVR32_SCIF_GCLK_ADCIFD               8
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // end AVR32_SCIF_GCLK_ADCIFD

#ifndef AVR32_SCIF_GCLK_AST
#define AVR32_SCIF_GCLK_AST                  6
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // end AVR32_SCIF_GCLK_AST

#ifndef AVR32_SCIF_GCLK_GLOC
#define AVR32_SCIF_GCLK_GLOC                 0
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // end AVR32_SCIF_GCLK_GLOC

#ifndef AVR32_SCIF_GCLK_IISC
#define AVR32_SCIF_GCLK_IISC                 5
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // end AVR32_SCIF_GCLK_IISC

#ifndef AVR32_SCIF_GCLK_PWMA
#define AVR32_SCIF_GCLK_PWMA                 4
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // end AVR32_SCIF_GCLK_PWMA

#ifndef AVR32_SCIF_GCLK_USBC
#define AVR32_SCIF_GCLK_USBC                 3
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // end AVR32_SCIF_GCLK_USBC

#ifndef AVR32_PM_CPU_MAX_FREQ
#define AVR32_PM_CPU_MAX_FREQ              48000000
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // AVR32_PM_CPU_MAX_FREQ

#ifndef AVR32_PM_HSB_MAX_FREQ
#define AVR32_PM_HSB_MAX_FREQ              48000000
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // AVR32_PM_HSB_MAX_FREQ

#ifndef AVR32_PM_PBA_MAX_FREQ
#define AVR32_PM_PBA_MAX_FREQ              48000000
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif // AVR32_PM_PBA_MAX_FREQ

#ifndef AVR32_PM_PBB_MAX_FREQ
#define AVR32_PM_PBB_MAX_FREQ              48000000
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif  // AVR32_PM_PBB_MAX_FREQ

#endif // end UC3D

#endif  // _UC3D_DEFINES_FIX
