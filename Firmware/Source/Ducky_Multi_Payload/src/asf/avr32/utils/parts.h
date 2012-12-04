/*This file is prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief Arch file for AVR32.
 *
 * This file defines common AVR32 UC3 series.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices can be used.
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 ******************************************************************************/

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
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
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 *
 */

#ifndef _ARCH_H_
#define _ARCH_H_

// UC3 A Series
#define UC3A0    (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3A0128__)   || \
                     defined (__AVR32_UC3A0256__)   || \
                     defined (__AVR32_UC3A0512__)   || \
                     defined (__AVR32_UC3A0512ES__)))  \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3A0128__)     || \
                     defined (__AT32UC3A0256__)     || \
                     defined (__AT32UC3A0512__)     || \
                     defined (__AT32UC3A0512ES__))))

#define UC3A1    (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3A1128__)   || \
                     defined (__AVR32_UC3A1256__)   || \
                     defined (__AVR32_UC3A1512__)   || \
                     defined (__AVR32_UC3A1512ES__)))  \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3A1128__)     || \
                     defined (__AT32UC3A1256__)     || \
                     defined (__AT32UC3A1512__)     || \
                     defined (__AT32UC3A1512ES__))))

#define UC3A3  (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3A364__)    || \
                     defined (__AVR32_UC3A364S__)   || \
                     defined (__AVR32_UC3A3128__)   || \
                     defined (__AVR32_UC3A3128S__)  || \
                     defined (__AVR32_UC3A3256__)   || \
                     defined (__AVR32_UC3A3256S__)))  \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3A364__)      || \
                     defined (__AT32UC3A364S__)     || \
                     defined (__AT32UC3A3128__)     || \
                     defined (__AT32UC3A3128S__)    || \
                     defined (__AT32UC3A3256__)     || \
                     defined (__AT32UC3A3256S__))))

#define UC3A4  (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3A464__)    || \
                     defined (__AVR32_UC3A464S__)   || \
                     defined (__AVR32_UC3A4128__)   || \
                     defined (__AVR32_UC3A4128S__)  || \
                     defined (__AVR32_UC3A4256__)   || \
                     defined (__AVR32_UC3A4256S__)))  \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3A464__)      || \
                     defined (__AT32UC3A464S__)     || \
                     defined (__AT32UC3A4128__)     || \
                     defined (__AT32UC3A4128S__)    || \
                     defined (__AT32UC3A4256__)     || \
                     defined (__AT32UC3A4256S__))))

#define UC3A (UC3A0 || UC3A1 || UC3A3 || UC3A4)

// UC3 B Series
#define UC3B0  (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3B064__)     || \
                     defined (__AVR32_UC3B0128__)    || \
                     defined (__AVR32_UC3B0256__)    || \
                     defined (__AVR32_UC3B0256ES__)  || \
                     defined (__AVR32_UC3B0512__)    || \
                     defined (__AVR32_UC3B0512REVC_))) \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3B064__)       || \
                     defined (__AT32UC3B0128__)      || \
                     defined (__AT32UC3B0256__)      || \
                     defined (__AT32UC3B0256ES__)    || \
                     defined (__AT32UC3B0512__)      || \
                     defined (__AT32UC3B0512REVC__))))

#define UC3B1  (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3B164__)     || \
                     defined (__AVR32_UC3B1128__)    || \
                     defined (__AVR32_UC3B1256__)    || \
                     defined (__AVR32_UC3B1256ES__)  || \
                     defined (__AVR32_UC3B1512__)    || \
                     defined (__AVR32_UC3B1512ES__))) \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3B164__)       || \
                     defined (__AT32UC3B1128__)      || \
                     defined (__AT32UC3B1256__)      || \
                     defined (__AT32UC3B1256ES__)    || \
                     defined (__AT32UC3B1512__)      || \
                     defined (__AT32UC3B1512REVC__))))

#define UC3B (UC3B0 || UC3B1 )

// UC3 C Series
#define UC3C0_REVC    (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3C064CREVC__)   || \
                     defined (__AVR32_UC3C0128CREVC__)  || \
                     defined (__AVR32_UC3C0256CREVC__)  || \
                     defined (__AVR32_UC3C0512CREVC__)))  \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3C064CREVC__)     || \
                     defined (__AT32UC3C0128CREVC__)    || \
                     defined (__AT32UC3C0256CREVC__)    || \
                     defined (__AT32UC3C0512CREVC__))))

#define UC3C0    (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3C064C__)       || \
                     defined (__AVR32_UC3C0128C__)      || \
                     defined (__AVR32_UC3C0256C__)      || \
                     defined (__AVR32_UC3C0512C__)))  \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3C064C__)         || \
                     defined (__AT32UC3C0128C__)        || \
                     defined (__AT32UC3C0256C__)        || \
                     defined (__AT32UC3C0512C__))))

#define UC3C1_REVC    (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3C164CREVC__)   || \
                     defined (__AVR32_UC3C1128CREVC__)  || \
                     defined (__AVR32_UC3C1256CREVC__)  || \
                     defined (__AVR32_UC3C1512CREVC__)))  \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3C164CREVC__)     || \
                     defined (__AT32UC3C1128CREVC__)    || \
                     defined (__AT32UC3C1256CREVC__)    || \
                     defined (__AT32UC3C1512CREVC__))))

#define UC3C1    (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3C164C__)       || \
                     defined (__AVR32_UC3C1128C__)      || \
                     defined (__AVR32_UC3C1256C__)      || \
                     defined (__AVR32_UC3C1512C__)))  \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3C164C__)         || \
                     defined (__AT32UC3C1128C__)        || \
                     defined (__AT32UC3C1256C__)        || \
                     defined (__AT32UC3C1512C__))))

#define UC3C2_REVC    (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3C264CREVC__)   || \
                     defined (__AVR32_UC3C2128CREVC__)  || \
                     defined (__AVR32_UC3C2256CREVC__)  || \
                     defined (__AVR32_UC3C2512CREVC__)))  \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3C264CREVC__)     || \
                     defined (__AT32UC3C2128CREVC__)    || \
                     defined (__AT32UC3C2256CREVC__)    || \
                     defined (__AT32UC3C2512CREVC__))))

#define UC3C2    (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3C264C__)       || \
                     defined (__AVR32_UC3C2128C__)      || \
                     defined (__AVR32_UC3C2256C__)      || \
                     defined (__AVR32_UC3C2512C__)))  \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3C264C__)         || \
                     defined (__AT32UC3C2128C__)        || \
                     defined (__AT32UC3C2256C__)        || \
                     defined (__AT32UC3C2512C__))))

#define UC3C_REVC (UC3C0_REVC || UC3C1_REVC || UC3C2_REVC)
#define UC3C (UC3C0 || UC3C0_REVC || UC3C1 || UC3C1_REVC || UC3C2 || UC3C2_REVC)

// UC3 L Device series
#define UC3L0 (( defined (__GNUC__) && \
                  ( defined (__AVR32_UC3L016__)     || \
                    defined (__AVR32_UC3L032__)     || \
                    defined (__AVR32_UC3L064__))) \
           ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                  ( defined (__AT32UC3L016__)     || \
                    defined (__AT32UC3L032__)     || \
                    defined (__AT32UC3L064__))))

#define UC3L (UC3L0)

// UC3 D Device series
#define UC3D3 (( defined (__GNUC__) && \
                  ( defined (__AVR32_UC128D3__)     || \
                    defined (__AVR32_UC64D3__)))      \
           ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                  ( defined (__ATUC128D3__)     || \
                    defined (__ATUC64D3__) )))

#define UC3D (UC3D3)

#if (UC3D)
#include "header_files/uc3d_defines_fix.h"
#endif

#define UC3  (UC3A || UC3B || UC3C || UC3D || UC3L)

#if ((defined __GNUC__) && (defined __AVR32__)) || (defined __ICCAVR32__ || defined __AAVR32__)
#  if (UC3)
#    include <avr32/io.h>
#  endif
#endif

#endif  // _ARCH_H_
