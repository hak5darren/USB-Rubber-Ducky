/*This file is prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief SD/MMC card driver using an SPI interface.
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

#ifndef _SD_MMC_SPI_H_
#define _SD_MMC_SPI_H_


/*_____ I N C L U D E S ____________________________________________________*/

#include "conf_access.h"

#if SD_MMC_SPI_MEM == DISABLE
  #error sd_mmc_spi.h is #included although SD_MMC_SPI_MEM is disabled
#endif


#include "compiler.h"
#include "spi.h"


/*_____ M A C R O S ________________________________________________________*/

#ifndef MMC_SECTOR_SIZE
#define MMC_SECTOR_SIZE                   512   //default sector size is 512 bytes
#endif

#define byte_adr_of_block(ad)             (ad<<9)   // returns the first byte address of a specified sector/block number (512bytes/block)

/*_____ D E F I N I T I O N ________________________________________________*/

// Card identification
#define MMC_CARD                          0
#define SD_CARD                           1
#define SD_CARD_2                         2
#define SD_CARD_2_SDHC					  3

/* status bits for card types */
#define SD_SPEC_1 0
#define SD_SPEC_2 1
#define SD_SPEC_SDHC 2


// Lock operations
#define OP_UNLOCK                         0x00
#define OP_LOCK                           0x04
#define OP_RESET_PWD                      0x02
#define OP_SET_PWD                        0x01
#define OP_FORCED_ERASE                   0x08

// MMC commands (taken from MMC reference)
#define MMC_GO_IDLE_STATE                 0     ///< initialize card to SPI-type access
#define MMC_SEND_OP_COND                  1     ///< set card operational mode
#define MMC_CMD2                          2     ///< illegal in SPI mode !
#define MMC_SEND_IF_COND                  8
#define MMC_SEND_CSD                      9     ///< get card's CSD
#define MMC_SEND_CID                      10    ///< get card's CID
#define MMC_SEND_STATUS                   13
#define MMC_SET_BLOCKLEN                  16    ///< Set number of bytes to transfer per block
#define MMC_READ_SINGLE_BLOCK             17    ///< read a block
#define MMC_WRITE_BLOCK                   24    ///< write a block
#define MMC_PROGRAM_CSD                   27
#define MMC_SET_WRITE_PROT                28
#define MMC_CLR_WRITE_PROT                29
#define MMC_SEND_WRITE_PROT               30
#define SD_TAG_WR_ERASE_GROUP_START       32
#define SD_TAG_WR_ERASE_GROUP_END         33
#define MMC_TAG_SECTOR_START              32
#define MMC_TAG_SECTOR_END                33
#define MMC_UNTAG_SECTOR                  34
#define MMC_TAG_ERASE_GROUP_START         35    ///< Sets beginning of erase group (mass erase)
#define MMC_TAG_ERASE_GROUP_END           36    ///< Sets end of erase group (mass erase)
#define MMC_UNTAG_ERASE_GROUP             37    ///< Untag (unset) erase group (mass erase)
#define MMC_ERASE                         38    ///< Perform block/mass erase
#define SD_SEND_OP_COND_ACMD              41              ///< Same as MMC_SEND_OP_COND but specific to SD (must be preceeded by CMD55)
#define MMC_LOCK_UNLOCK                   42              ///< To start a lock/unlock/pwd operation
#define SD_APP_CMD55                      55              ///< Use before any specific command (type ACMD)
#define SD_READ_OCR						  58
#define MMC_CRC_ON_OFF                    59    ///< Turns CRC check on/off
// R1 Response bit-defines
#define MMC_R1_BUSY                       0x80  ///< R1 response: bit indicates card is busy
#define MMC_R1_PARAMETER                  0x40
#define MMC_R1_ADDRESS                    0x20
#define MMC_R1_ERASE_SEQ                  0x10
#define MMC_R1_COM_CRC                    0x08
#define MMC_R1_ILLEGAL_COM                0x04
#define MMC_R1_ERASE_RESET                0x02
#define MMC_R1_IDLE_STATE                 0x01
// Data Start tokens
#define MMC_STARTBLOCK_READ               0xFE  ///< when received from card, indicates that a block of data will follow
#define MMC_STARTBLOCK_WRITE              0xFE  ///< when sent to card, indicates that a block of data will follow
#define MMC_STARTBLOCK_MWRITE             0xFC
// Data Stop tokens
#define MMC_STOPTRAN_WRITE                0xFD
// Data Error Token values
#define MMC_DE_MASK                       0x1F
#define MMC_DE_ERROR                      0x01
#define MMC_DE_CC_ERROR                   0x02
#define MMC_DE_ECC_FAIL                   0x04
#define MMC_DE_OUT_OF_RANGE               0x04
#define MMC_DE_CARD_LOCKED                0x04
// Data Response Token values
#define MMC_DR_MASK                       0x1F
#define MMC_DR_ACCEPT                     0x05
#define MMC_DR_REJECT_CRC                 0x0B
#define MMC_DR_REJECT_WRITE_ERROR         0x0D

#define SDHC_CARD                         1
#define SD_CARD_T                         0 
                              
#define SD_FAILURE                       -1
#define SD_MMC                            0
/*_____ D E C L A R A T I O N ______________________________________________*/

//! Low-level functions (basic management)
extern Bool sd_mmc_spi_internal_init(void);
extern Bool sd_mmc_spi_init(spi_options_t spiOptions, unsigned int pba_hz);             // initializes the SD/MMC card (reset, init, analyse)
extern Bool sd_mmc_spi_check_presence(void);    // check the presence of the card
extern Bool sd_mmc_spi_mem_check(void);         // check the presence of the card, and initialize if inserted
extern Bool sd_mmc_spi_wait_not_busy (void);    // wait for the card to be not busy (exits with timeout)
extern Bool sd_mmc_spi_get_csd(uint8_t *);      // stores the CSD of the card into csd[16]
extern Bool sd_mmc_spi_get_cid(uint8_t *);      // stores the CID of the card into cid[16]
extern int  sd_mmc_spi_get_if(void);
extern int  sd_mmc_spi_check_hc(void);
extern void sd_mmc_spi_get_capacity(void);                     // extract parameters from CSD and compute capacity, last block adress, erase group size
extern Bool sd_mmc_spi_get_status(void);                       // read the status register of the card (R2 response)
extern uint8_t   sd_mmc_spi_send_and_read(uint8_t);            // send a byte on SPI and returns the received byte
extern uint8_t   sd_mmc_spi_send_command(uint8_t, uint32_t);   // send a single command + argument (R1 response expected and returned), with memory select then unselect
extern uint8_t   sd_mmc_spi_command(uint8_t, uint32_t);        // send a command + argument (R1 response expected and returned), without memory selct/unselect

//! Protection functions (optionnal)
extern Bool is_sd_mmc_spi_write_pwd_locked(void);                    // check if the lock protection on the card is featured and enabled
extern Bool sd_mmc_spi_lock_operation(uint8_t, uint8_t, uint8_t *);  // use this function to lock/unlock the card or modify password

//! Functions for preparing block read/write
extern Bool sd_mmc_spi_read_open (uint32_t);         // to call before first access to a random page
extern Bool sd_mmc_spi_read_close (void);
extern Bool sd_mmc_spi_write_open (uint32_t);        // to call before first access to a random page
extern void sd_mmc_spi_write_close (void);

//! Funtions to link USB DEVICE flow with MMC
extern Bool sd_mmc_spi_write_sector (uint16_t);      // write a 512b sector from USB buffer
extern Bool sd_mmc_spi_read_sector (uint16_t);       // reads a 512b sector to an USB buffer
extern Bool sd_mmc_spi_read_multiple_sector(uint16_t nb_sector);
extern Bool sd_mmc_spi_write_multiple_sector(uint16_t nb_sector);
extern void sd_mmc_spi_read_multiple_sector_callback(const void *psector);
extern void sd_mmc_spi_write_multiple_sector_callback(void *psector);


/*
//! Funtions to link USB HOST flow with MMC
bit     sd_mmc_spi_host_write_sector (uint16_t);
bit     sd_mmc_spi_host_read_sector (uint16_t);
*/

//! Functions to read/write one sector (512btes) with ram buffer pointer
extern Bool sd_mmc_spi_read_sector_to_ram(void *ram);     // reads a data block and send it to a buffer (512b)
extern Bool sd_mmc_spi_write_sector_from_ram(const void *ram);  // writes a data block from a buffer (512b)
extern Bool sd_mmc_spi_erase_sector_group(uint32_t, uint32_t);    // erase a group of sectors defined by start and end address (details in sd_mmc_spi.c)


//!functions used to make a transfer from SD_MMC to RAM using the PDCA
//Max reading size is block
extern Bool sd_mmc_spi_read_open_PDCA (uint32_t);         // to call before first access to a random page
extern void sd_mmc_spi_read_close_PDCA (void);       // unselect the memory


extern uint8_t           csd[16];                    // stores the Card Specific Data
extern volatile uint32_t capacity;                   // stores the capacity in bytes
extern volatile uint16_t capacity_mult;
extern volatile uint32_t sd_mmc_spi_last_block_address;
extern  uint16_t         erase_group_size;
extern  uint8_t          r1;
extern  uint16_t         r2;
extern  uint8_t          card_type;                   // stores SD_CARD or MMC_CARD type card
extern  Bool        sd_mmc_spi_init_done;


#endif  // _SD_MMC_SPI_H_
