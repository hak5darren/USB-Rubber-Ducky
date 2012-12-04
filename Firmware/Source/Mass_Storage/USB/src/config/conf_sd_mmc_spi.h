/*****************************************************************************
 *
 * \file
 *
 * \brief SD/MMC configuration file.
 *
 * This file contains the possible external configuration of the SD/MMC.
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
#ifndef _CONF_SD_MMC_SPI_H_
#define _CONF_SD_MMC_SPI_H_

#include "board.h"
#include "conf_access.h"
#include "main.h"

#if SD_MMC_SPI_MEM == DISABLE
  #error conf_sd_mmc_spi.h is #included although SD_MMC_SPI_MEM is disabled
#endif

#include "sd_mmc_spi.h"


//_____ D E F I N I T I O N S ______________________________________________

//! SPI master speed in Hz.
#define SD_MMC_SPI_MASTER_SPEED     12000000

//! Number of bits in each SPI transfer.
#define SD_MMC_SPI_BITS             8


#if !defined(SD_MMC_SPI)
//! Set SD_MMC_SPI, default SPI register address if this is a user board
#warning "Using a default SD_MMC_SPI define value. Edit the conf_sd_mmc_spi.h file to modify that define value according to the current board."
#if (UC3L || UC3B || UC3D)
#define SD_MMC_SPI                 (&AVR32_SPI)
#else
#define SD_MMC_SPI                 (&AVR32_SPI0)
#endif
#endif

#if !defined(SD_MMC_SPI_NPCS)
//! Set SD_MMC_SPI_NPCS, default chip select if this is a user board
#warning "Using a default SD_MMC_SPI_NPCS define value. Edit the conf_sd_mmc_spi.h file to modify that define value according to the current board."
#define SD_MMC_SPI_NPCS            0
#endif

#endif  // _CONF_SD_MMC_SPI_H_
