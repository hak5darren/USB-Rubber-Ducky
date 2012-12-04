/*This file is prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief CTRL_ACCESS interface for SD/MMC card.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices with an SPI module can be used.
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

#ifndef _SD_MMC_SPI_MEM_H_
#define _SD_MMC_SPI_MEM_H_


#include "conf_access.h"

#if SD_MMC_SPI_MEM == DISABLE
  #error sd_mmc_spi_mem.h is #included although SD_MMC_SPI_MEM is disabled
#endif


#include "ctrl_access.h"


//_____ D E F I N I T I O N S ______________________________________________

#define   SD_MMC_REMOVED       0
#define   SD_MMC_INSERTED      1
#define   SD_MMC_REMOVING      2


//---- CONTROL FONCTIONS ----
//!
//! @brief This function initializes the hw/sw resources required to drive the SD_MMC_SPI.
//!/
extern void           sd_mmc_spi_mem_init(void);

//!
//! @brief This function tests the state of the SD_MMC memory and sends it to the Host.
//!        For a PC, this device is seen as a removable media
//!        Before indicating any modification of the status of the media (GOOD->NO_PRESENT or vice-versa),
//!         the function must return the BUSY data to make the PC accepting the change
//!
//! @return                Ctrl_status
//!   Media is ready       ->    CTRL_GOOD
//!   Media not present    ->    CTRL_NO_PRESENT
//!   Media has changed    ->    CTRL_BUSY
//!/
extern Ctrl_status    sd_mmc_spi_test_unit_ready(void);

//!
//! @brief This function gives the address of the last valid sector.
//!
//! @param *nb_sector  number of sector (sector = 512B). OUT
//!
//! @return                Ctrl_status
//!   Media ready          ->  CTRL_GOOD
//!   Media not present    ->  CTRL_NO_PRESENT
//!/
extern Ctrl_status    sd_mmc_spi_read_capacity(uint32_t *nb_sector);

//!
//! @brief This function returns the write protected status of the memory.
//!
//! Only used by memory removal with a HARDWARE SPECIFIC write protected detection
//! ! The user must unplug the memory to change this write protected status,
//! which cannot be for a SD_MMC.
//!
//! @return false  -> the memory is not write-protected (always)
//!/
extern Bool           sd_mmc_spi_wr_protect(void);

//!
//! @brief This function tells if the memory has been removed or not.
//!
//! @return false  -> The memory isn't removed
//!
extern Bool           sd_mmc_spi_removal(void);


//---- ACCESS DATA FONCTIONS ----

#if ACCESS_USB == ENABLED
// Standard functions for open in read/write mode the device

//!
//! @brief This function performs a read operation of n sectors from a given address on.
//! (sector = 512B)
//!
//!         DATA FLOW is: SD_MMC => USB
//!
//! @param addr         Sector address to start the read from
//! @param nb_sector    Number of sectors to transfer
//!
//! @return                Ctrl_status
//!   It is ready    ->    CTRL_GOOD
//!   A error occur  ->    CTRL_FAIL
//!
extern Ctrl_status    sd_mmc_spi_usb_read_10(uint32_t addr, uint16_t nb_sector);

//! This fonction initialises the SD/MMC memory for a write operation
//!
//!         DATA FLOW is: USB => SD_MMC
//!
//! (sector = 512B)
//! @param addr         Sector address to start write
//! @param nb_sector    Number of sectors to transfer
//!
//! @return                Ctrl_status
//!   It is ready    ->    CTRL_GOOD
//!   An error occurs  ->    CTRL_FAIL
//!
extern Ctrl_status    sd_mmc_spi_usb_write_10(uint32_t addr, uint16_t nb_sector);

#endif // #if ACCESS_USB == ENABLED

#if ACCESS_MEM_TO_RAM == ENABLED
// Standard functions for read/write 1 sector to 1 sector ram buffer


//! This fonction reads 1 sector from SD/MMC to internal ram buffer
//!
//!         DATA FLOW is: SD/MMC => RAM
//!
//! (sector = 512B)
//! @param addr         Sector address to read
//! @param ram          Ram buffer pointer
//!
//! @return                Ctrl_status
//!   It is ready      ->    CTRL_GOOD
//!   An error occurs  ->    CTRL_FAIL
//!
extern Ctrl_status    sd_mmc_spi_mem_2_ram(uint32_t addr, void *ram);

//! This fonction initialises the memory for a write operation
//! from ram buffer to SD/MMC (1 sector)
//!
//!         DATA FLOW is: RAM => SD/MMC
//!
//! (sector = 512B)
//! @param addr         Sector address to write
//! @param ram          Ram buffer pointer
//!
//! @return                Ctrl_status
//!   It is ready      ->    CTRL_GOOD
//!   An error occurs  ->    CTRL_FAIL
//!
extern Ctrl_status    sd_mmc_spi_ram_2_mem(uint32_t addr, const void *ram);

#endif // end #if ACCESS_MEM_TO_RAM == ENABLED


#endif  // _SD_MMC_SPI_MEM_H_
