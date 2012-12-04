/*****************************************************************************
 *
 * \file
 *
 * \brief SPI driver for AVR32 UC3.
 *
 * This file defines a useful set of functions for the SPI interface on AVR32
 * devices.
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


#ifndef _SPI_H_
#define _SPI_H_

/**
 * \defgroup group_avr32_drivers_spi SPI - Serial Peripheral Interface
 *
 * Driver for the SPI (Serial Peripheral Interface).
 * The SPI circuit is a synchronous serial data link that provides communication with external devices in Master
 * or Slave mode. Connection to Peripheral DMA Controller channel capabilities optimizes data transfers.
 *
 * \{
 */

#include "compiler.h"

//! Time-out value (number of attempts).
#define SPI_TIMEOUT       15000

//! Spi Mode 0.
#define SPI_MODE_0       0

//! Spi Mode 1.
#define SPI_MODE_1       1


//! Status codes used by the SPI driver.
typedef enum
{
  SPI_ERROR = -1,
  SPI_OK = 0,
  SPI_ERROR_TIMEOUT = 1,
  SPI_ERROR_ARGUMENT,
  SPI_ERROR_OVERRUN,
  SPI_ERROR_MODE_FAULT,
  SPI_ERROR_OVERRUN_AND_MODE_FAULT
} spi_status_t;

//! Option structure for SPI channels.
typedef struct
{
  //! The SPI channel to set up.
  uint8_t reg;

  //! Preferred baudrate for the SPI.
  uint32_t baudrate;

  //! Number of bits in each character (8 to 16).
  uint8_t bits;
 //! Delay before first clock pulse after selecting slave (in PBA clock periods).
  uint8_t spck_delay;

  //! Delay between each transfer/character (in PBA clock periods).
  uint8_t trans_delay;

  //! Sets this chip to stay active after last transfer to it.
  uint8_t stay_act;

  //! Which SPI mode to use when transmitting.
  uint8_t spi_mode;

  //! Disables the mode fault detection.
  //! With this bit cleared, the SPI master mode will disable itself if another
  //! master tries to address it.
  uint8_t modfdis;
} spi_options_t;

/*! \brief Reset the SPI.
 *
 * \param spi       Base address of the SPI instance.
 *
 */
static inline void spi_reset(volatile avr32_spi_t *spi)
{
	spi->cr = AVR32_SPI_CR_SWRST_MASK;
}

/*! \brief Set Master Mode of the SPI.
 *
 * \param spi         Base address of the SPI instance.
 */
static inline void spi_set_master_mode(volatile avr32_spi_t *spi)
{
	spi->MR.mstr = 1;
}

/*! \brief Set Slave Mode of the SPI.
 *
 * \param spi         Base address of the SPI instance.
 */
static inline void spi_set_slave_mode(volatile avr32_spi_t *spi)
{
	spi->MR.mstr = 0;
}

/*! \brief Enable Modfault of the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable_modfault(volatile avr32_spi_t *spi)
{
	spi->MR.modfdis = 0;
}

/*! \brief Disable Modfault of the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_disable_modfault(volatile avr32_spi_t *spi)
{
	spi->MR.modfdis = 1;
}

/*! \brief Enable Loopback of the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable_loopback(volatile avr32_spi_t *spi)
{
	spi->MR.llb = 1;
}

/*! \brief Disable Loopback of the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_disable_loopback(volatile avr32_spi_t *spi)
{
	spi->MR.llb = 0;
}

/*! \brief Enable Chip Select Decoding of the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable_chipselect_decoding(volatile avr32_spi_t *spi)
{
	spi->MR.pcsdec = 1;
}

/*! \brief Disable Chip Select Decoding of the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_disable_chipselect_decoding(volatile avr32_spi_t *spi)
{
	spi->MR.pcsdec = 0;
}

/*! \brief Set Chip Select of the SPI.
 *
 * \param spi         Base address of the SPI instance.
 * \param chip_select Chip Select.
 */
static inline void spi_set_chipselect(volatile avr32_spi_t *spi,uint8_t chip_select)
{
	spi->MR.pcs = chip_select;
}

/*! \brief Enable Variable Chip Select of the SPI.
 *
 * \param spi         Base address of the SPI instance.
 */
static inline void spi_enable_variable_chipselect(volatile avr32_spi_t *spi)
{
	spi->MR.ps = 1;
}

/*! \brief Disable Variable Chip Select of the SPI.
 *
 * \param spi         Base address of the SPI instance.
 */
static inline void spi_disable_variable_chipselect(volatile avr32_spi_t *spi)
{
	spi->MR.ps = 0;
}

/*! \brief Set Delay Between Chip Selects of the SPI.
 *
 * \param spi         Base address of the SPI instance.
 * \param delay       Delay.
 */
static inline void spi_set_delay(volatile avr32_spi_t *spi,uint8_t delay)
{
	spi->MR.dlybcs = delay;
}

/*! \brief Set Delay Between Consecutive Transfer on a Chip Selects of the SPI.
 *
 * \param spi         Base address of the SPI instance.
 * \param chip_select Chip Select.
 * \param delay       Delay.
 */

static inline void spi_set_chipselect_delay_bct(volatile avr32_spi_t *spi,
                        uint8_t chip_select, uint8_t delay)
{
  Assert(chip_select <= 3);
  switch(chip_select) {
    case 0:
      spi->CSR0.dlybct = delay;
      break;
    case 1:
      spi->CSR1.dlybct  = delay;
      break;
    case 2:
      spi->CSR2.dlybct  = delay;
      break;
    case 3:
      spi->CSR3.dlybct  = delay;
      break;
  }
}

/*! \brief Set Delay Before SPCK on a Chip Selects of the SPI.
 *
 * \param spi         Base address of the SPI instance.
 * \param chip_select Chip Select.
 * \param delay       Delay.
 */
static inline void spi_set_chipselect_delay_bs(volatile avr32_spi_t *spi,
                        uint8_t chip_select, uint8_t delay)
{
  Assert(chip_select <= 3);
  switch(chip_select) {
    case 0:
      spi->CSR0.dlybs = delay;
      break;
    case 1:
      spi->CSR1.dlybs  = delay;
      break;
    case 2:
      spi->CSR2.dlybs  = delay;
      break;
    case 3:
      spi->CSR3.dlybs  = delay;
      break;
  }
}

/*! \brief Set Delay Before SPCK on a Chip Selects of the SPI.
 *
 * \param spi         Base address of the SPI instance.
 * \param chip_select Chip Select.
 * \param len         Bits per Transfer [8...16].
 */
static inline void spi_set_bits_per_transfer(volatile avr32_spi_t *spi, uint8_t chip_select,
                        uint8_t len)
{
  Assert((len >= 8) && (len <= 16));
  switch(chip_select) {
    case 0:
      spi->CSR0.bits = len - 8;
      break;
    case 1:
      spi->CSR1.bits  = len - 8;
      break;
    case 2:
      spi->CSR2.bits  = len - 8;
      break;
    case 3:
      spi->CSR3.bits  = len - 8;
      break;
  }
}

/*! \brief Set baudrate for a Chip Selects of the SPI.
 *
 * \param spi         Base address of the SPI instance.
 * \param chip_select Chip Select.
 * \param scbr        Baudrate Register.
 */
static inline void spi_set_baudrate_register(volatile avr32_spi_t *spi,uint8_t chip_select,
                        uint8_t scbr)
{
  switch(chip_select) {
    case 0:
      spi->CSR0.scbr = scbr;
      break;
    case 1:
      spi->CSR1.scbr  = scbr;
      break;
    case 2:
      spi->CSR2.scbr  = scbr;
      break;
    case 3:
      spi->CSR3.scbr  = scbr;
      break;
  }
}

/*! \brief Enable Active mode of a Chip Selects of the SPI.
 *
 * \param spi         Base address of the SPI instance.
 * \param chip_select Chip Select.
 */
static inline void spi_enable_active_mode(volatile avr32_spi_t *spi,uint8_t chip_select)
{
  switch(chip_select) {
    case 0:
      spi->CSR0.csaat = 1;
      break;
    case 1:
      spi->CSR1.csaat  = 1;
      break;
    case 2:
      spi->CSR2.csaat  = 1;
      break;
    case 3:
      spi->CSR3.csaat  = 1;
      break;
  }
}

/*! \brief Set Mode of the SPI.
 *
 * \param spi         Base address of the SPI instance.
 * \param chip_select Chip Select.
 * \param flags       SPI Mode.
 */
static inline void spi_set_mode(volatile avr32_spi_t *spi,uint8_t chip_select,
                        uint8_t flags)
{
  switch(chip_select) {
    case 0:
      spi->CSR0.cpol = flags >> 1;
      spi->CSR0.ncpha = (flags & 0x1) ^ 0x1;
      break;
    case 1:
      spi->CSR1.cpol  = flags >> 1;
      spi->CSR1.ncpha = (flags & 0x1) ^ 0x1;
      break;
    case 2:
      spi->CSR2.cpol  = flags >> 1;
      spi->CSR2.ncpha = (flags & 0x1) ^ 0x1;
      break;
    case 3:
      spi->CSR3.cpol  = flags >> 1;
      spi->CSR3.ncpha = (flags & 0x1) ^ 0x1;
      break;
  }
}

/*! \brief Put one data to a SPI peripheral.
 *
 * \param spi Base address of the SPI instance.
 * \param data The data byte to be loaded
 *
 */
static inline void spi_put(volatile avr32_spi_t *spi, uint16_t data)
{
	spi->tdr = data << AVR32_SPI_TDR_TD_OFFSET;
}

/*! \brief Get one data to a SPI peripheral.
 *
 * \param spi Base address of the SPI instance.
 * \return The data byte
 *
 */
static inline uint16_t spi_get(volatile avr32_spi_t *spi)
{
	return (spi->rdr >> AVR32_SPI_RDR_RD_OFFSET);
}

/*! \brief Checks if all transmissions are complete.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return Status.
 *   \retval 1  All transmissions complete.
 *   \retval 0  Transmissions not complete.
 */
static inline bool spi_is_tx_empty(volatile avr32_spi_t *spi)
{
  return (spi->sr & AVR32_SPI_SR_TXEMPTY_MASK) != 0;
}

/*! \brief Checks if all transmissions is ready.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return Status.
 *   \retval 1  All transmissions complete.
 *   \retval 0  Transmissions not complete.
 */
static inline bool spi_is_tx_ready(volatile avr32_spi_t *spi)
{
  return (spi->sr & AVR32_SPI_SR_TDRE_MASK) != 0;
}

/*! \brief Check if the SPI contains a received character.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI Receive Holding Register is full, otherwise \c 0.
 */
static inline bool spi_is_rx_full(volatile avr32_spi_t *spi)
{
  return (spi->sr & AVR32_SPI_SR_RDRF_MASK) != 0;
}

/*! \brief Checks if all reception is ready.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI Receiver is ready, otherwise \c 0.
 */
static inline bool spi_is_rx_ready(volatile avr32_spi_t *spi)
{
  return (spi->sr & (AVR32_SPI_SR_RDRF_MASK | AVR32_SPI_SR_TXEMPTY_MASK)) ==
         (AVR32_SPI_SR_RDRF_MASK | AVR32_SPI_SR_TXEMPTY_MASK);
}

/*! \brief Resets the SPI controller.
 *
 * \param spi Base address of the SPI instance.
 */
extern void spi_reset(volatile avr32_spi_t *spi);

/*! \brief Initializes the SPI in slave mode.
 *
 * \param spi       Base address of the SPI instance.
 * \param bits      Number of bits in each transmitted character (8 to 16).
 * \param spi_mode  Clock polarity and phase.
 *
 * \return Status.
 *   \retval SPI_OK             Success.
 *   \retval SPI_ERROR_ARGUMENT Invalid argument(s) passed.
 */
extern spi_status_t spi_initSlave(volatile avr32_spi_t *spi,
                                  uint8_t bits,
                                  uint8_t spi_mode);

/*! \brief Sets up the SPI in a test mode where the transmitter is connected to
 *         the receiver (local loopback).
 *
 * \param spi Base address of the SPI instance.
 *
 * \return Status.
 *   \retval SPI_OK Success.
 */
extern spi_status_t spi_initTest(volatile avr32_spi_t *spi);

/*! \brief Initializes the SPI in master mode.
 *
 * \param spi     Base address of the SPI instance.
 * \param options Pointer to a structure containing initialization options.
 *
 * \return Status.
 *   \retval SPI_OK             Success.
 *   \retval SPI_ERROR_ARGUMENT Invalid argument(s) passed.
 */
extern spi_status_t spi_initMaster(volatile avr32_spi_t *spi, const spi_options_t *options);

/*! \brief Calculates the baudrate divider.
 *
 * \param baudrate Baudrate value.
 * \param pb_hz  SPI module input clock frequency (PBA clock, Hz).
 *
 * \return Divider or error code.
 *   \retval >=0  Success.
 *   \retval  <0  Error.
 */
extern int16_t getBaudDiv(const unsigned int baudrate, uint32_t pb_hz);

/*! \brief Sets up how and when the slave chips are selected (master mode only).
 *
 * \param spi         Base address of the SPI instance.
 * \param variable_ps Target slave is selected in transfer register for every
 *                    character to transmit.
 * \param pcs_decode  The four chip select lines are decoded externally. Values
 *                    0 to 14 can be given to \ref spi_selectChip.
 * \param delay       Delay in PBA periods between chip selects.
 *
 * \return Status.
 *   \retval SPI_OK             Success.
 *   \retval SPI_ERROR_ARGUMENT Invalid argument(s) passed.
 */
extern spi_status_t spi_selectionMode(volatile avr32_spi_t *spi,
                                      uint8_t variable_ps,
                                      uint8_t pcs_decode,
                                      uint8_t delay);
/*! \brief Selects slave chip.
 *
 * \param spi   Base address of the SPI instance.
 * \param chip  Slave chip number (normal: 0 to 3, extarnally decoded signal: 0
 *              to 14).
 *
 * \return Status.
 *   \retval SPI_OK             Success.
 *   \retval SPI_ERROR_ARGUMENT Invalid argument(s) passed.
 */
extern spi_status_t spi_selectChip(volatile avr32_spi_t *spi, unsigned char chip);

/*! \brief Unselects slave chip.
 *
 * \param spi   Base address of the SPI instance.
 * \param chip  Slave chip number (normal: 0 to 3, extarnally decoded signal: 0
 *              to 14).
 *
 * \return Status.
 *   \retval SPI_OK             Success.
 *   \retval SPI_ERROR_TIMEOUT  Time-out.
 *
 * \note Will block program execution until time-out occurs if last transmission
 *       is not complete. Invoke \ref spi_writeEndCheck beforehand if needed.
 */
extern spi_status_t spi_unselectChip(volatile avr32_spi_t *spi, unsigned char chip);

/*! \brief Sets options for a specific slave chip.
 *
 * The baudrate field has to be written before transfer in master mode. Four
 * similar registers exist, one for each slave. When using encoded slave
 * addressing, reg=0 sets options for slaves 0 to 3, reg=1 for slaves 4 to 7 and
 * so on.
 *
 * \param spi     Base address of the SPI instance.
 * \param options Pointer to a structure containing initialization options for
 *                an SPI channel.
 * \param pb_hz  SPI module input clock frequency (PBA clock, Hz).
 *
 * \return Status.
 *   \retval SPI_OK             Success.
 *   \retval SPI_ERROR_ARGUMENT Invalid argument(s) passed.
 */
extern spi_status_t spi_setupChipReg(volatile avr32_spi_t *spi,
                                     const spi_options_t *options,
                                     uint32_t pb_hz);
/*! \brief Enables the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
extern void spi_enable(volatile avr32_spi_t *spi);

/*! \brief Disables the SPI.
 *
 * Ensures that nothing is transferred while setting up buffers.
 *
 * \param spi Base address of the SPI instance.
 *
 * \warning This may cause data loss if used on a slave SPI.
 */
extern void spi_disable(volatile avr32_spi_t *spi);

/*! \brief Tests if the SPI is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI is enabled, otherwise \c 0.
 */
extern int spi_is_enabled(volatile avr32_spi_t *spi);

/*! \brief Checks if there is no data in the transmit register.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return Status.
 *   \retval 1  No data in TDR.
 *   \retval 0  Some data in TDR.
 */
extern unsigned char spi_writeRegisterEmptyCheck(volatile avr32_spi_t *spi);

/*! \brief Writes one data word in master fixed peripheral select mode or in
 *         slave mode.
 *
 * \param spi   Base address of the SPI instance.
 * \param data  The data word to write.
 *
 * \return Status.
 *   \retval SPI_OK             Success.
 *   \retval SPI_ERROR_TIMEOUT  Time-out.
 *
 * \note Will block program execution until time-out occurs if transmitter is
 *       busy and transmit buffer is full. Invoke
 *       \ref spi_writeRegisterEmptyCheck beforehand if needed.
 *
 * \note Once the data has been written to the transmit buffer, the end of
 *       transmission is not waited for. Invoke \ref spi_writeEndCheck if
 *       needed.
 */
extern spi_status_t spi_write(volatile avr32_spi_t *spi, uint16_t data);

/*! \brief Selects a slave in master variable peripheral select mode and writes
 *         one data word to it.
 *
 * \param spi       Base address of the SPI instance.
 * \param data      The data word to write.
 * \param pcs       Slave selector (bit 0 -> nCS line 0, bit 1 -> nCS line 1,
 *                  etc.).
 * \param lastxfer  Boolean indicating whether this is the last data word
 *                  transfer.
 *
 * \return Status.
 *   \retval SPI_OK             Success.
 *   \retval SPI_ERROR_TIMEOUT  Time-out.
 *   \retval SPI_ERROR_ARGUMENT Invalid argument(s) passed.
 *
 * \note Will block program execution until time-out occurs if transmitter is
 *       busy and transmit buffer is full. Invoke
 *       \ref spi_writeRegisterEmptyCheck beforehand if needed.
 *
 * \note Once the data has been written to the transmit buffer, the end of
 *       transmission is not waited for. Invoke \ref spi_writeEndCheck if
 *       needed.
 */
extern spi_status_t spi_variableSlaveWrite(volatile avr32_spi_t *spi,
                                           uint16_t data,
                                           uint8_t pcs,
                                           uint8_t lastxfer);

/*! \brief Checks if all transmissions are complete.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return Status.
 *   \retval 1  All transmissions complete.
 *   \retval 0  Transmissions not complete.
 */
extern unsigned char spi_writeEndCheck(volatile avr32_spi_t *spi);

/*! \brief Checks if there is data in the receive register.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return Status.
 *   \retval 1  Some data in RDR.
 *   \retval 0  No data in RDR.
 */
extern unsigned char spi_readRegisterFullCheck(volatile avr32_spi_t *spi);

/*! \brief Reads one data word in master mode or in slave mode.
 *
 * \param spi   Base address of the SPI instance.
 * \param data  Pointer to the location where to store the received data word.
 *
 * \return Status.
 *   \retval SPI_OK             Success.
 *   \retval SPI_ERROR_TIMEOUT  Time-out.
 *
 * \note Will block program execution until time-out occurs if no data is
 *       received or last transmission is not complete. Invoke
 *       \ref spi_writeEndCheck or \ref spi_readRegisterFullCheck beforehand if
 *       needed.
 */
extern spi_status_t spi_read(volatile avr32_spi_t *spi, uint16_t *data);

/*! \brief Gets status information from the SPI.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return Status.
 *   \retval SPI_OK                           Success.
 *   \retval SPI_ERROR_OVERRUN                Overrun error.
 *   \retval SPI_ERROR_MODE_FAULT             Mode fault (SPI addressed as slave
 *                                            while in master mode).
 *   \retval SPI_ERROR_OVERRUN_AND_MODE_FAULT Overrun error and mode fault.
 */
extern unsigned char spi_getStatus(volatile avr32_spi_t *spi);

/**
 * \}
 */

#endif  // _SPI_H_
