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

//_____  I N C L U D E S ___________________________________________________

#include "conf_access.h"


#if SD_MMC_SPI_MEM == ENABLE

#include "conf_sd_mmc_spi.h"
#include "sd_mmc_spi.h"
#include "sd_mmc_spi_mem.h"


//_____ M A C R O S ________________________________________________________

#define Sd_mmc_spi_access_signal_on()
#define Sd_mmc_spi_access_signal_off()


//_____ P R I V A T E    D E C L A R A T I O N _____________________________


//_____ D E F I N I T I O N ________________________________________________

//extern xdata uint32_t sd_mmc_spi_mem_size;
extern            uint32_t SD_MMC_SPI_DISK_SIZE;
extern volatile   uint32_t sd_mmc_spi_last_address;
extern            Bool     sd_mmc_spi_init_done;

                  uint8_t  sd_mmc_spi_presence_status = SD_MMC_INSERTED;
extern            Bool     sd_mmc_spi_init_done;


//_____ D E C L A R A T I O N ______________________________________________


void sd_mmc_spi_mem_init(void)
{
  sd_mmc_spi_internal_init();        // Restart Init of SD/MMC card after previous first init
}



Ctrl_status sd_mmc_spi_test_unit_ready(void)
{
  Sd_mmc_spi_access_signal_on();
  switch (sd_mmc_spi_presence_status)
  {
    case SD_MMC_REMOVED:
      sd_mmc_spi_init_done = false;
      if (OK == sd_mmc_spi_mem_check())
      {
        sd_mmc_spi_presence_status = SD_MMC_INSERTED;
        Sd_mmc_spi_access_signal_off();
        return CTRL_BUSY;
      }
      Sd_mmc_spi_access_signal_off();
      return CTRL_NO_PRESENT;

    case SD_MMC_INSERTED:
      if (OK != sd_mmc_spi_mem_check())
      {
        sd_mmc_spi_presence_status = SD_MMC_REMOVING;
        sd_mmc_spi_init_done = false;
        Sd_mmc_spi_access_signal_off();
        return CTRL_BUSY;
      }
      Sd_mmc_spi_access_signal_off();
      return CTRL_GOOD;

    case SD_MMC_REMOVING:
      sd_mmc_spi_presence_status = SD_MMC_REMOVED;
      Sd_mmc_spi_access_signal_off();
      return CTRL_NO_PRESENT;

    default:
      sd_mmc_spi_presence_status = SD_MMC_REMOVED;
      Sd_mmc_spi_access_signal_off();
      return CTRL_BUSY;
  }

/*
  if (OK==sd_mmc_spi_mem_check())
  {
    if (sd_mmc_spi_status_changed == false)
    {
      sd_mmc_spi_status_changed = true;
      return CTRL_BUSY;     // BUSY token must be returned to indicate a status change !
    }
    else
      return CTRL_GOOD;     // the 2nd time the host will ask for unit_ready, we can answer GOOD if we have returned BUSY first !
  }
  else
  {
    if (sd_mmc_spi_status_changed == true)
    {
      sd_mmc_spi_status_changed = false;
      return CTRL_BUSY;     // BUSY token must be returned to indicate a status change !
    }
    else
      return CTRL_NO_PRESENT;
  }
*/
}



Ctrl_status sd_mmc_spi_read_capacity(uint32_t *nb_sector)
{
//   sd_mmc_spi_check_presence();   // ommited because creates interferences with "sd_mmc_spi_test_unit_ready()" function
   Sd_mmc_spi_access_signal_on();

   if (sd_mmc_spi_init_done == false)
   {
      sd_mmc_spi_mem_init();
   }

   if (sd_mmc_spi_init_done == true)
   {
     *nb_sector = sd_mmc_spi_last_block_address+1;
     Sd_mmc_spi_access_signal_off();
     return CTRL_GOOD;
   }
   else
   {
     Sd_mmc_spi_access_signal_off();
     return CTRL_NO_PRESENT;
   }
}


//!
//! @brief This function returns the write protected status of the memory.
//!
//! Only used by memory removal with a HARDWARE SPECIFIC write protected detection
//! ! The user must unplug the memory to change this write protected status,
//! which cannot be for a SD_MMC.
//!
//! @return false  -> the memory is not write-protected (always)
//!/
Bool  sd_mmc_spi_wr_protect(void)
{
   return false;
}


//!
//! @brief This function tells if the memory has been removed or not.
//!
//! @return false  -> The memory isn't removed
//!/
Bool  sd_mmc_spi_removal(void)
{
  return false;
//  return ((OK == sd_mmc_spi_check_presence()) ? false : true);
}



//------------ STANDARD FUNCTIONS to read/write the memory --------------------

#if ACCESS_USB == ENABLED

#include "usb_drv.h"
#include "scsi_decoder.h"



Ctrl_status sd_mmc_spi_usb_read_10(uint32_t addr, uint16_t nb_sector)
{
Bool status;

   if (sd_mmc_spi_init_done == false)
   {
      sd_mmc_spi_mem_init();
   }

   if (sd_mmc_spi_init_done != true)
     return CTRL_NO_PRESENT;

   Sd_mmc_spi_access_signal_on();

   if( !sd_mmc_spi_read_open(addr) )
     goto sd_mmc_spi_usb_read_10_fail;

   if( !sd_mmc_spi_read_multiple_sector(nb_sector) )
     goto sd_mmc_spi_usb_read_10_fail;

   if( !sd_mmc_spi_read_close() )
     goto sd_mmc_spi_usb_read_10_fail;

   Sd_mmc_spi_access_signal_off();
   return CTRL_GOOD;

sd_mmc_spi_usb_read_10_fail:
   Sd_mmc_spi_access_signal_off();
   return CTRL_FAIL;
}


void sd_mmc_spi_read_multiple_sector_callback(const void *psector)
{
  uint16_t data_to_transfer = MMC_SECTOR_SIZE;

  while (data_to_transfer)
  {
    while (!Is_usb_in_ready(g_scsi_ep_ms_in));

    Usb_reset_endpoint_fifo_access(g_scsi_ep_ms_in);
    data_to_transfer = usb_write_ep_txpacket(g_scsi_ep_ms_in, psector,
                                             data_to_transfer, &psector);
    Usb_ack_in_ready_send(g_scsi_ep_ms_in);
  }
}



Ctrl_status sd_mmc_spi_usb_write_10(uint32_t addr, uint16_t nb_sector)
{
  Bool status;

   if (sd_mmc_spi_init_done == false)
   {
      sd_mmc_spi_mem_init();
   }

   if (sd_mmc_spi_init_done == true)
   {
     Sd_mmc_spi_access_signal_on();
     sd_mmc_spi_write_open(addr);
     status = sd_mmc_spi_write_multiple_sector(nb_sector);
     sd_mmc_spi_write_close();
     Sd_mmc_spi_access_signal_off();
     if (status == OK)
       return CTRL_GOOD;
     else
       return CTRL_NO_PRESENT;
   }
   else
     return CTRL_NO_PRESENT;
}


void sd_mmc_spi_write_multiple_sector_callback(void *psector)
{
  uint16_t data_to_transfer = MMC_SECTOR_SIZE;

  while (data_to_transfer)
  {
    while (!Is_usb_out_received(g_scsi_ep_ms_out));

    Usb_reset_endpoint_fifo_access(g_scsi_ep_ms_out);
    data_to_transfer = usb_read_ep_rxpacket(g_scsi_ep_ms_out, psector,
                                            data_to_transfer, &psector);
    Usb_ack_out_received_free(g_scsi_ep_ms_out);
  }
}

#endif // ACCESS_USB == ENABLED


//------------ Standard functions for read/write 1 sector to 1 sector ram buffer -----------------

#if ACCESS_MEM_TO_RAM == ENABLED

Ctrl_status sd_mmc_spi_mem_2_ram(uint32_t addr, void *ram)
{
   Sd_mmc_spi_access_signal_on();
   sd_mmc_spi_check_presence();

   if (sd_mmc_spi_init_done == false)
   {
      sd_mmc_spi_mem_init();
   }

   if (sd_mmc_spi_init_done != true)
     return CTRL_NO_PRESENT;

   if( !sd_mmc_spi_read_open(addr) )
     goto sd_mmc_spi_mem_2_ram_fail;

   if( !sd_mmc_spi_read_sector_to_ram(ram))
     goto sd_mmc_spi_mem_2_ram_fail;

   if( !sd_mmc_spi_read_close() )
     goto sd_mmc_spi_mem_2_ram_fail;

   Sd_mmc_spi_access_signal_off();
   return CTRL_GOOD;

sd_mmc_spi_mem_2_ram_fail:
   Sd_mmc_spi_access_signal_off();
   return CTRL_FAIL;
}


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
Ctrl_status    sd_mmc_spi_ram_2_mem(uint32_t addr, const void *ram)
{
   Sd_mmc_spi_access_signal_on();
   sd_mmc_spi_check_presence();

   if (sd_mmc_spi_init_done == false)
   {
      sd_mmc_spi_mem_init();
   }

   if (sd_mmc_spi_init_done == true)
   {
     sd_mmc_spi_write_open(addr);
     if (KO == sd_mmc_spi_write_sector_from_ram(ram))
     {
       sd_mmc_spi_write_close();
       Sd_mmc_spi_access_signal_off();
       return CTRL_NO_PRESENT;
     }
     sd_mmc_spi_write_close();
     Sd_mmc_spi_access_signal_off();
     return CTRL_GOOD;
   }
   Sd_mmc_spi_access_signal_off();

   return CTRL_NO_PRESENT;
}


#endif // ACCESS_MEM_TO_RAM == ENABLED


#endif  // SD_MMC_SPI_MEM == ENABLE
