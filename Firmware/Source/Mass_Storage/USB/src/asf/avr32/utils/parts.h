/*****************************************************************************
 *
 * \file
 *
 * \brief Arch file for AVR32.
 *
 * This file defines common AVR32 UC3 series.
 *
 * Copyright (c) 2009 Atmel Corporation. All rights reserved.
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
 ******************************************************************************/


#ifndef _ARCH_H_
#define _ARCH_H_

// UC3 A Series
#define UC3A0    (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3A0128__)   || \
                     defined (__AVR32_UC3A0256__)   || \
                     defined (__AVR32_UC3A0512__)))  \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3A0128__)     || \
                     defined (__AT32UC3A0256__)     || \
                     defined (__AT32UC3A0512__))))

#define UC3A1    (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3A1128__)   || \
                     defined (__AVR32_UC3A1256__)   || \
                     defined (__AVR32_UC3A1512__)))  \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3A1128__)     || \
                     defined (__AT32UC3A1256__)     || \
                     defined (__AT32UC3A1512__))))

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
                     defined (__AVR32_UC3B0512__))) \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3B064__)       || \
                     defined (__AT32UC3B0128__)      || \
                     defined (__AT32UC3B0256__)      || \
                     defined (__AT32UC3B0512__))))

#define UC3B1  (( defined (__GNUC__) && \
                   ( defined (__AVR32_UC3B164__)     || \
                     defined (__AVR32_UC3B1128__)    || \
                     defined (__AVR32_UC3B1256__)    || \
                     defined (__AVR32_UC3B1512__))) \
            ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                   ( defined (__AT32UC3B164__)       || \
                     defined (__AT32UC3B1128__)      || \
                     defined (__AT32UC3B1256__)      || \
                     defined (__AT32UC3B1512__))))

#define UC3B (UC3B0 || UC3B1 )

// UC3 C Series
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


#define UC3C (UC3C0 || UC3C1 || UC3C2 )

// UC3 D Device series
#define UC3D3 (( defined (__GNUC__) && \
                  ( defined (__AVR32_UC128D3__)     || \
                    defined (__AVR32_UC64D3__)))      \
           ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                  ( defined (__AT32UC128D3__)     || \
                    defined (__AT32UC64D3__) )))

#define UC3D4 (( defined (__GNUC__) && \
                  ( defined (__AVR32_UC128D4__)     || \
                    defined (__AVR32_UC64D4__)))      \
           ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                  ( defined (__AT32UC128D4__)     || \
                    defined (__AT32UC64D4__) )))

#define UC3D (UC3D3 || UC3D4)

// UC3 L Device series
#define UC3L0 (( defined (__GNUC__) && \
                  ( defined (__AVR32_UC3L016__)     || \
                    defined (__AVR32_UC3L032__)     || \
                    defined (__AVR32_UC3L064__))) \
           ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                  ( defined (__AT32UC3L016__)     || \
                    defined (__AT32UC3L032__)     || \
                    defined (__AT32UC3L064__))))

#define UC3L3 (( defined (__GNUC__) && \
                  ( defined (__AVR32_UC64L3U__)     || \
                    defined (__AVR32_UC128L3U__)     || \
                    defined (__AVR32_UC256L3U__))) \
             ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                  ( defined (__ATUC64L3U__)     || \
                    defined (__ATUC128L3U__)     || \
                    defined (__ATUC256L3U__))))
#define UC3L4 (( defined (__GNUC__) && \
                  ( defined (__AVR32_UC64L4U__)     || \
                    defined (__AVR32_UC128L4U__)     || \
                    defined (__AVR32_UC256L4U__))) \
             ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                  ( defined (__ATUC64L4U__)     || \
                    defined (__ATUC128L4U__)     || \
                    defined (__ATUC256L4U__))))

#define UC3L3_L4 (UC3L3 || UC3L4)

#define UC3L0128 (( defined (__GNUC__) && \
                  ( defined (__AVR32_UC3L0128__))) \
           ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                  ( defined (__AT32UC3L0128__))))

#define UC3L0256 (( defined (__GNUC__) && \
                  ( defined (__AVR32_UC3L0256__))) \
           ||((defined(__ICCAVR32__) || defined(__AAVR32__)) && \
                  ( defined (__AT32UC3L0256__))))

#define UC3L ( UC3L0 || UC3L0128 || UC3L0256 || UC3L3_L4)

#define UC3  (UC3A || UC3B || UC3C || UC3D || UC3L)

#if ((defined __GNUC__) && (defined __AVR32__)) || (defined __ICCAVR32__ || defined __AAVR32__)
#  if (UC3)
#    include <avr32/io.h>
#  endif
#endif

#if (UC3D)
#include "header_files/uc3d_defines_fix.h"
#endif

#endif  // _ARCH_H_
