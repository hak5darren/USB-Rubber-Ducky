/**
 * \file
 *
 * \brief USBB Device Driver header file.
 *
 * Copyright (c) 2009-2011 Atmel Corporation. All rights reserved.
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

#ifndef _USBB_DEVICE_H_
#define _USBB_DEVICE_H_

#include "compiler.h"
#include "preprocessor.h"
#include "usbb_otg.h"


//! \ingroup usb_device_group
//! \defgroup udd_group USB Device Driver (UDD)
//! USBB low-level driver for USB device mode
//!
//! @warning Bit-masks are used instead of bit-fields because PB registers
//! require 32-bit write accesses while AVR32-GCC 4.0.2 builds 8-bit
//! accesses even when volatile unsigned int bit-fields are specified.
//! @{

//! @name USBB Device IP properties
//! These macros give access to IP properties
//! @{
  //! Get maximal number of endpoints
#define  udd_get_endpoint_max_nbr() \
		(((USBB_RD_BITFIELD(UFEATURES_EPT_NBR,MAX) - 1) \
		& ((1 << AVR32_USBB_UFEATURES_EPT_NBR_MAX_SIZE) - 1)) + 1)
//! @}

//! @name USBB Device speeds management
//! @{
  //! Enable/disable device low-speed mode
#define  udd_low_speed_enable()              USBB_SET_BITS(UDCON,LS)
#define  udd_low_speed_disable()             USBB_CLR_BITS(UDCON,LS)
  //! Test if device low-speed mode is forced
#define  Is_udd_low_speed_enable()           USBB_TST_BITS(UDCON,LS)

#ifdef AVR32_USBB_UDCON_SPDCONF
  //! Enable high speed mode
#  define   udd_high_speed_enable()          USBB_WR_BITFIELD(UDCON,SPDCONF,0)
  //! Disable high speed mode
#  define   udd_high_speed_disable()         USBB_WR_BITFIELD(UDCON,SPDCONF,3)
  //! Test if controller is in full speed mode
#  define   Is_udd_full_speed_mode() \
		(USBB_RD_BITFIELD(USBSTA,SPEED) == AVR32_USBB_USBSTA_SPEED_FULL)
#else
#  define   udd_high_speed_enable()          do { } while (0)
#  define   udd_high_speed_disable()         do { } while (0)
#  define   Is_udd_full_speed_mode()         true
#endif
//! @}

//! @name USBB Device HS test mode management
//! @{
#ifdef AVR32_USBB_UDCON_SPDCONF
  //! Enable high speed test mode
#  define   udd_enable_hs_test_mode()        (USBB_WR_BITFIELD(UDCON,SPDCONF, 2))
#  define   udd_enable_hs_test_mode_j()      USBB_SET_BITS(UDCON,TSTJ)
#  define   udd_enable_hs_test_mode_k()      USBB_SET_BITS(UDCON,TSTK)
#  define   udd_enable_hs_test_mode_packet() USBB_SET_BITS(UDCON,TSTPCKT)
#endif
//! @}

//! @name USBB device attach control
//! These macros manage the USBB Device attach.
//! @{
  //! detaches from USB bus
#define  udd_detach_device()                 USBB_SET_BITS(UDCON,DETACH)
  //! attaches to USB bus
#define  udd_attach_device()                 USBB_CLR_BITS(UDCON,DETACH)
  //! test if the device is detached
#define  Is_udd_detached()                   USBB_TST_BITS(UDCON,DETACH)
//! @}


//! @name USBB device bus events control
//! These macros manage the USBB Device bus events.
//! @{

//! Initiates a remote wake-up event
//! @{
#define  udd_initiate_remote_wake_up()       USBB_SET_BITS(UDCON,RMWKUP)
#define  Is_udd_pending_remote_wake_up()     USBB_TST_BITS(UDCON,RMWKUP)
//! @}

//! Manage upstream resume event (=remote wakeup from device)
//! The USB driver sends a resume signal called "Upstream Resume"
//! @{
#define  udd_enable_remote_wake_up_interrupt()     USBB_REG_SET(UDINTE,UPRSME)
#define  udd_disable_remote_wake_up_interrupt()    USBB_REG_CLR(UDINTE,UPRSME)
#define  Is_udd_remote_wake_up_interrupt_enabled() USBB_TST_BITS(UDINTE,UPRSME)
#define  udd_ack_remote_wake_up_start()            USBB_REG_CLR(UDINT,UPRSM)
#define  udd_raise_remote_wake_up_start()          USBB_REG_SET(UDINT,UPRSM)
#define  Is_udd_remote_wake_up_start()             USBB_TST_BITS(UDINT,UPRSM)
//! @}

//! Manage downstream resume event (=remote wakeup from host)
//! The USB controller detects a valid "End of Resume" signal initiated by the host
//! @{
#define  udd_enable_resume_interrupt()             USBB_REG_SET(UDINTE,EORSME)
#define  udd_disable_resume_interrupt()            USBB_REG_CLR(UDINTE,EORSME)
#define  Is_udd_resume_interrupt_enabled()         USBB_TST_BITS(UDINTE,EORSME)
#define  udd_ack_resume()                          USBB_REG_CLR(UDINT,EORSM)
#define  udd_raise_resume()                        USBB_REG_SET(UDINT,EORSM)
#define  Is_udd_resume()                           USBB_TST_BITS(UDINT,EORSM)
//! @}

//! Manage wake-up event (=usb line activity)
//! The USB controller is reactivated by a filtered non-idle signal from the lines
//! @{
#define  udd_enable_wake_up_interrupt()            USBB_REG_SET(UDINTE,WAKEUPE)
#define  udd_disable_wake_up_interrupt()           USBB_REG_CLR(UDINTE,WAKEUPE)
#define  Is_udd_wake_up_interrupt_enabled()        USBB_TST_BITS(UDINTE,WAKEUPE)
#define  udd_ack_wake_up()                         USBB_REG_CLR(UDINT,WAKEUP)
#define  udd_raise_wake_up()                       USBB_REG_SET(UDINT,WAKEUP)
#define  Is_udd_wake_up()                          USBB_TST_BITS(UDINT,WAKEUP)
//! @}

//! Manage reset event
//! Set when a USB "End of Reset" has been detected
//! @{
#define  udd_enable_reset_interrupt()              USBB_REG_SET(UDINTE,EORSTE)
#define  udd_disable_reset_interrupt()             USBB_REG_CLR(UDINTE,EORSTE)
#define  Is_udd_reset_interrupt_enabled()          USBB_TST_BITS(UDINTE,EORSTE)
#define  udd_ack_reset()                           USBB_REG_CLR(UDINT,EORST)
#define  udd_raise_reset()                         USBB_REG_SET(UDINT,EORST)
#define  Is_udd_reset()                            USBB_TST_BITS(UDINT,EORST)
//! @}

//! Manage start of frame event
//! @{
#define  udd_enable_sof_interrupt()                USBB_REG_SET(UDINTE,SOFE)
#define  udd_disable_sof_interrupt()               USBB_REG_CLR(UDINTE,SOFE)
#define  Is_udd_sof_interrupt_enabled()            USBB_TST_BITS(UDINTE,SOFE)
#define  udd_ack_sof()                             USBB_REG_CLR(UDINT,SOF)
#define  udd_raise_sof()                           USBB_REG_SET(UDINT,SOF)
#define  Is_udd_sof()                              USBB_TST_BITS(UDINT,SOF)
#define  udd_frame_number()                        (USBB_RD_BITFIELD(UDFNUM,FNUM))
#define  Is_udd_frame_number_crc_error()           USBB_TST_BITS(UDFNUM,FNCERR)
//! @}

//! Manage Micro start of frame event (High Speed Only)
//! @{
#define  udd_enable_msof_interrupt()               USBB_REG_SET(UDINTE,MSOFE)
#define  udd_disable_msof_interrupt()              USBB_REG_CLR(UDINTE,MSOFE)
#define  Is_udd_msof_interrupt_enabled()           USBB_TST_BITS(UDINTE,MSOFE)
#define  udd_ack_msof()                            USBB_REG_CLR(UDINT,MSOF)
#define  udd_raise_msof()                          USBB_REG_SET(UDINT,MSOF)
#define  Is_udd_msof()                             USBB_TST_BITS(UDINT,MSOF)
#define  udd_micro_frame_number() \
		(Rd_bitfield(AVR32_USBB.udfnum, \
		(AVR32_USBB_UDFNUM_FNUM_MASK|AVR32_USBB_UDFNUM_MFNUM_MASK)))
//! @}

//! Manage suspend event
//! @{
#define  udd_enable_suspend_interrupt()            USBB_REG_SET(UDINTE,SUSPE)
#define  udd_disable_suspend_interrupt()           USBB_REG_CLR(UDINTE,SUSPE)
#define  Is_udd_suspend_interrupt_enabled()        USBB_TST_BITS(UDINTE,SUSPE)
#define  udd_ack_suspend()                         USBB_REG_CLR(UDINT,SUSP)
#define  udd_raise_suspend()                       USBB_REG_SET(UDINT,SUSP)
#define  Is_udd_suspend()                          USBB_TST_BITS(UDINT,SUSP)
//! @}

//! @}

//! @name USBB device address control
//! These macros manage the USBB Device address.
//! @{
  //! enables USB device address
#define  udd_enable_address()                      USBB_SET_BITS(UDCON,ADDEN)
  //! disables USB device address
#define  udd_disable_address()                     USBB_CLR_BITS(UDCON,ADDEN)
#define  Is_udd_address_enabled()                  USBB_TST_BITS(UDCON,ADDEN)
  //! configures the USB device address
#define  udd_configure_address(addr)               (USBB_WR_BITFIELD(UDCON,UADD, addr))
  //! gets the currently configured USB device address
#define  udd_get_configured_address()              (USBB_RD_BITFIELD(UDCON,UADD))
//! @}


//! @name USBB Device endpoint drivers
//! These macros manage the common features of the endpoints.
//! @{

//! Generic macro for USBB registers that can be arrayed
//! @{
#define USBB_ARRAY(reg,index)   (((volatile unsigned long*)(&AVR32_USBB.reg))[index])
#define USBB_EP_CLR_BITS(reg, bit, ep) \
		(Clr_bits(USBB_ARRAY(TPASTE2(reg,0),ep),\
		TPASTE5(AVR32_USBB_,reg,0_,bit,_MASK)))
#define USBB_EP_SET_BITS(reg, bit, ep) \
		(Set_bits(USBB_ARRAY(TPASTE2(reg,0),ep),\
		TPASTE5(AVR32_USBB_,reg,0_,bit,_MASK)))
#define USBB_EP_TST_BITS(reg, bit, ep) \
		(Tst_bits(USBB_ARRAY(TPASTE2(reg,0),ep),\
		TPASTE5(AVR32_USBB_,reg,0_,bit,_MASK)))
#define USBB_EP_RD_BITFIELD(reg, bit, ep) \
		(Rd_bitfield(USBB_ARRAY(TPASTE2(reg,0),ep),\
		TPASTE5(AVR32_USBB_,reg,0_,bit,_MASK)))
#define USBB_EP_WR_BITFIELD(reg, bit, ep, value) \
		(Wr_bitfield(USBB_ARRAY(TPASTE2(reg,0),ep),\
		TPASTE5(AVR32_USBB_,reg,0_,bit,_MASK), value))
#define USBB_EP_REG_CLR(reg, bit, ep) \
		(USBB_ARRAY(TPASTE2(reg,0CLR),ep) \
		 = TPASTE5(AVR32_USBB_,reg,0CLR_,bit,C_MASK))
#define USBB_EP_REG_SET(reg, bit, ep) \
		(USBB_ARRAY(TPASTE2(reg,0SET),ep) \
		 = TPASTE5(AVR32_USBB_,reg,0SET_,bit,S_MASK))
//! @}

//! @name USBB Device endpoint configuration
//! @{
  //! enables the selected endpoint
#define  udd_enable_endpoint(ep) \
		(Set_bits(AVR32_USBB.uerst, AVR32_USBB_UERST_EPEN0_MASK << (ep)))
  //! disables the selected endpoint
#define  udd_disable_endpoint(ep) \
		(Clr_bits(AVR32_USBB.uerst, AVR32_USBB_UERST_EPEN0_MASK << (ep)))
  //! tests if the selected endpoint is enabled
#define  Is_udd_endpoint_enabled(ep) \
		(Tst_bits(AVR32_USBB.uerst, AVR32_USBB_UERST_EPEN0_MASK << (ep)))
  //! resets the selected endpoint
#define  udd_reset_endpoint(ep) \
		(Set_bits(AVR32_USBB.uerst, AVR32_USBB_UERST_EPRST0_MASK << (ep)),\
		Clr_bits(AVR32_USBB.uerst, AVR32_USBB_UERST_EPRST0_MASK << (ep)))
  //! tests if the selected endpoint is being reset
#define  Is_udd_resetting_endpoint(ep) \
		(Tst_bits(AVR32_USBB.uerst, AVR32_USBB_UERST_EPRST0_MASK << (ep)))

  //! configures the selected endpoint type
#define  udd_configure_endpoint_type(ep, type)       USBB_EP_WR_BITFIELD(UECFG,EPTYPE,ep,type)
  //! gets the configured selected endpoint type
#define  udd_get_endpoint_type(ep)                   USBB_EP_RD_BITFIELD(UECFG,EPTYPE,ep)
  //! enables the bank autoswitch for the selected endpoint
#define  udd_enable_endpoint_bank_autoswitch(ep)     USBB_EP_SET_BITS(UECFG,AUTOSW,ep)
  //! disables the bank autoswitch for the selected endpoint
#define  udd_disable_endpoint_bank_autoswitch(ep)    USBB_EP_CLR_BITS(UECFG,AUTOSW,ep)
#define  Is_udd_endpoint_bank_autoswitch_enabled(ep) USBB_EP_TST_BITS(UECFG,AUTOSW,ep)
  //! configures the selected endpoint direction
#define  udd_configure_endpoint_direction(ep, dir)   USBB_EP_WR_BITFIELD(UECFG,EPDIR,ep,dir)
  //! gets the configured selected endpoint direction
#define  udd_get_endpoint_direction(ep)              USBB_EP_RD_BITFIELD(UECFG,EPDIR,ep)
#define  Is_udd_endpoint_in(ep)                      USBB_EP_TST_BITS(UECFG,EPDIR,ep)
  //! Bounds given integer size to allowed range and rounds it up to the nearest
  //! available greater size, then applies register format of USBB controller
  //! for endpoint size bit-field.
#define  udd_format_endpoint_size(size) \
		(32 - clz(((U32)min(max(size, 8), 1024) << 1) - 1) - 1 - 3)
  //! configures the selected endpoint size
#define  udd_configure_endpoint_size(ep, size) \
		USBB_EP_WR_BITFIELD(UECFG,EPSIZE,ep, udd_format_endpoint_size(size))
  //! gets the configured selected endpoint size
#define  udd_get_endpoint_size(ep)                   (8<<USBB_EP_RD_BITFIELD(UECFG,EPSIZE,ep))
  //! configures the selected endpoint number of banks
#define  udd_configure_endpoint_bank(ep, bank)       USBB_EP_WR_BITFIELD(UECFG,EPBK,ep,bank)
  //! gets the configured selected endpoint number of banks
#define  udd_get_endpoint_bank(ep)                   USBB_EP_RD_BITFIELD(UECFG,EPBK,ep)
  //! allocates the configuration selected endpoint in DPRAM memory
#define  udd_allocate_memory(ep)                     USBB_EP_SET_BITS(UECFG,ALLOC,ep)
  //! un-allocates the configuration selected endpoint in DPRAM memory
#define  udd_unallocate_memory(ep)                   USBB_EP_CLR_BITS(UECFG,ALLOC,ep)
#define  Is_udd_memory_allocated(ep)                 USBB_EP_TST_BITS(UECFG,ALLOC,ep)

  //! configures selected endpoint in one step
#define  udd_configure_endpoint(ep, type, dir, size, bank) \
(\
   Wr_bits(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_EPTYPE_MASK |\
                                  AVR32_USBB_UECFG0_EPDIR_MASK  |\
                                  AVR32_USBB_UECFG0_EPSIZE_MASK |\
                                  AVR32_USBB_UECFG0_EPBK_MASK,   \
            (((U32)(type) << AVR32_USBB_UECFG0_EPTYPE_OFFSET) & AVR32_USBB_UECFG0_EPTYPE_MASK) |\
            (((U32)(dir ) << AVR32_USBB_UECFG0_EPDIR_OFFSET ) & AVR32_USBB_UECFG0_EPDIR_MASK ) |\
            ( (U32)udd_format_endpoint_size(size) << AVR32_USBB_UECFG0_EPSIZE_OFFSET         ) |\
            (((U32)(bank) << AVR32_USBB_UECFG0_EPBK_OFFSET  ) & AVR32_USBB_UECFG0_EPBK_MASK  ))\
)
  //! tests if current endpoint is configured
#define  Is_udd_endpoint_configured(ep)              USBB_EP_TST_BITS(UESTA,CFGOK,ep)
  //! returns the control direction
#define  udd_control_direction() \
		(Rd_bitfield(USBB_ARRAY(uesta0(EP_CONTROL), AVR32_USBB_UESTA0_CTRLDIR_MASK))

  //! resets the data toggle sequence
#define  udd_reset_data_toggle(ep)                   USBB_EP_REG_SET(UECON,RSTDT,ep)
  //! tests if the data toggle sequence is being reset
#define  Is_udd_data_toggle_reset(ep)                USBB_EP_TST_BITS(UECON,RSTDT,ep)
  //! returns data toggle
#define  udd_data_toggle(ep)                         USBB_EP_RD_BITFIELD(UESTA,DTSEQ,ep)
//! @}


//! @name USBB Device control endpoint
//! These macros control the endpoints.
//! @{

//! @name USBB Device control endpoint interrupts
//! These macros control the endpoints interrupts.
//! @{
  //! enables the selected endpoint interrupt
#define  udd_enable_endpoint_interrupt(ep) \
		 (AVR32_USBB.udinteset = AVR32_USBB_UDINTESET_EP0INTES_MASK << (ep))
  //! disables the selected endpoint interrupt
#define  udd_disable_endpoint_interrupt(ep) \
		(AVR32_USBB.udinteclr = AVR32_USBB_UDINTECLR_EP0INTEC_MASK << (ep))
  //! tests if the selected endpoint interrupt is enabled
#define  Is_udd_endpoint_interrupt_enabled(ep) \
		(Tst_bits(AVR32_USBB.udinte, AVR32_USBB_UDINTE_EP0INTE_MASK << (ep)))
  //! tests if an interrupt is triggered by the selected endpoint
#define  Is_udd_endpoint_interrupt(ep) \
		(Tst_bits(AVR32_USBB.udint, AVR32_USBB_UDINT_EP0INT_MASK << (ep)))
  //! returns the lowest endpoint number generating an endpoint interrupt or AVR32_USBB_EPT_NUM if none
#define  udd_get_interrupt_endpoint_number() \
		(ctz(((AVR32_USBB.udint >> AVR32_USBB_UDINT_EP0INT_OFFSET) &\
		(AVR32_USBB.udinte >> AVR32_USBB_UDINTE_EP0INTE_OFFSET)) |\
		(1 << AVR32_USBB_EPT_NUM)))
//! @}

//! @name USBB Device control endpoint errors
//! These macros control the endpoint errors.
//! @{
  //! enables the STALL handshake
#define  udd_enable_stall_handshake(ep)            USBB_EP_REG_SET(UECON,STALLRQ,ep)
  //! disables the STALL handshake
#define  udd_disable_stall_handshake(ep)           USBB_EP_REG_CLR(UECON,STALLRQ,ep)
  //! tests if STALL handshake request is running
#define  Is_udd_endpoint_stall_requested(ep)       USBB_EP_TST_BITS(UECON,STALLRQ,ep)
  //! tests if STALL sent
#define  Is_udd_stall(ep)                          USBB_EP_TST_BITS(UESTA,STALLEDI,ep)
  //! acks STALL sent
#define  udd_ack_stall(ep)                         USBB_EP_REG_CLR(UESTA,STALLEDI,ep)
  //! raises STALL sent
#define  udd_raise_stall(ep)                       USBB_EP_REG_SET(UESTA,STALLEDI,ep)
  //! enables STALL sent interrupt
#define  udd_enable_stall_interrupt(ep)            USBB_EP_REG_SET(UECON,STALLEDE,ep)
  //! disables STALL sent interrupt
#define  udd_disable_stall_interrupt(ep)           USBB_EP_REG_CLR(UECON,STALLEDE,ep)
  //! tests if STALL sent interrupt is enabled
#define  Is_udd_stall_interrupt_enabled(ep)        USBB_EP_TST_BITS(UECON,STALLEDE,ep)

  //! tests if NAK OUT received
#define  Is_udd_nak_out(ep)                        USBB_EP_TST_BITS(UESTA,NAKOUTI,ep)
  //! acks NAK OUT received
#define  udd_ack_nak_out(ep)                       USBB_EP_REG_CLR(UESTA,NAKOUTI,ep)
  //! raises NAK OUT received
#define  udd_raise_nak_out(ep)                     USBB_EP_REG_SET(UESTA,NAKOUTI,ep)
  //! enables NAK OUT interrupt
#define  udd_enable_nak_out_interrupt(ep)          USBB_EP_REG_SET(UECON,NAKOUTE,ep)
  //! disables NAK OUT interrupt
#define  udd_disable_nak_out_interrupt(ep)         USBB_EP_REG_CLR(UECON,NAKOUTE,ep)
  //! tests if NAK OUT interrupt is enabled
#define  Is_udd_nak_out_interrupt_enabled(ep)      USBB_EP_TST_BITS(UECON,NAKOUTE,ep)

  //! tests if NAK IN received
#define  Is_udd_nak_in(ep)                         USBB_EP_TST_BITS(UESTA,NAKINI,ep)
  //! acks NAK IN received
#define  udd_ack_nak_in(ep)                        USBB_EP_REG_CLR(UESTA,NAKINI,ep)
  //! raises NAK IN received
#define  udd_raise_nak_in(ep)                      USBB_EP_REG_SET(UESTA,NAKINI,ep)
  //! enables NAK IN interrupt
#define  udd_enable_nak_in_interrupt(ep)           USBB_EP_REG_SET(UECON,NAKINE,ep)
  //! disables NAK IN interrupt
#define  udd_disable_nak_in_interrupt(ep)          USBB_EP_REG_CLR(UECON,NAKINE,ep)
  //! tests if NAK IN interrupt is enabled
#define  Is_udd_nak_in_interrupt_enabled(ep)       USBB_EP_TST_BITS(UECON,NAKINE,ep)

  //! acks endpoint isochronous overflow interrupt
#define  udd_ack_overflow_interrupt(ep)            USBB_EP_REG_CLR(UESTA,OVERFI,ep)
  //! raises endpoint isochronous overflow interrupt
#define  udd_raise_overflow_interrupt(ep)          USBB_EP_REG_SET(UESTA,OVERFI,ep)
  //! tests if an overflow occurs
#define  Is_udd_overflow(ep)                       USBB_EP_TST_BITS(UESTA,OVERFI,ep)
  //! enables overflow interrupt
#define  udd_enable_overflow_interrupt(ep)         USBB_EP_REG_SET(UECON,OVERFE,ep)
  //! disables overflow interrupt
#define  udd_disable_overflow_interrupt(ep)        USBB_EP_REG_CLR(UECON,OVERFE,ep)
  //! tests if overflow interrupt is enabled
#define  Is_udd_overflow_interrupt_enabled(ep)     USBB_EP_TST_BITS(UECON,OVERFE,ep)

  //! acks endpoint isochronous underflow interrupt
#define  udd_ack_underflow_interrupt(ep)           USBB_EP_REG_CLR(UESTA,UNDERFI,ep)
  //! raises endpoint isochronous underflow interrupt
#define  udd_raise_underflow_interrupt(ep)         USBB_EP_REG_SET(UESTA,UNDERFI,ep)
  //! tests if an underflow occurs
#define  Is_udd_underflow(ep)                      USBB_EP_TST_BITS(UESTA,UNDERFI,ep)
  //! enables underflow interrupt
#define  udd_enable_underflow_interrupt(ep)        USBB_EP_REG_SET(UECON,RXSTPE,ep)
  //! disables underflow interrupt
#define  udd_disable_underflow_interrupt(ep)       USBB_EP_REG_CLR(UECON,RXSTPE,ep)
  //! tests if underflow interrupt is enabled
#define  Is_udd_underflow_interrupt_enabled(ep)    USBB_EP_TST_BITS(UECON,RXSTPE,ep)

  //! tests if CRC ERROR ISO OUT detected
#define  Is_udd_crc_error(ep)                      USBB_EP_TST_BITS(UESTA,STALLEDI,ep)
  //! acks CRC ERROR ISO OUT detected
#define  udd_ack_crc_error(ep)                     USBB_EP_REG_CLR(UESTA,STALLEDI,ep)
  //! raises CRC ERROR ISO OUT detected
#define  udd_raise_crc_error(ep)                   USBB_EP_REG_SET(UESTA,STALLEDI,ep)
  //! enables CRC ERROR ISO OUT detected interrupt
#define  udd_enable_crc_error_interrupt(ep)        USBB_EP_REG_SET(UECON,STALLEDE,ep)
  //! disables CRC ERROR ISO OUT detected interrupt
#define  udd_disable_crc_error_interrupt(ep)       USBB_EP_REG_CLR(UECON,STALLEDE,ep)
  //! tests if CRC ERROR ISO OUT detected interrupt is enabled
#define  Is_udd_crc_error_interrupt_enabled(ep)    USBB_EP_TST_BITS(UECON,STALLEDE,ep)
//! @}

//! @name USBB Device control endpoint transfer
//! These macros control the endpoint transfer.
//! @{

  //! tests if endpoint read allowed
#define  Is_udd_read_enabled(ep)                   USBB_EP_TST_BITS(UESTA,RWALL,ep)
  //! tests if endpoint write allowed
#define  Is_udd_write_enabled(ep)                  USBB_EP_TST_BITS(UESTA,RWALL,ep)

  //! returns the byte count
#define  udd_byte_count(ep)                        USBB_EP_RD_BITFIELD(UESTA,BYCT,ep)
  //! clears FIFOCON bit
#define  udd_ack_fifocon(ep)                       USBB_EP_REG_CLR(UECON,FIFOCON,ep)
  //! tests if FIFOCON bit set
#define  Is_udd_fifocon(ep)                        USBB_EP_TST_BITS(UECON,FIFOCON,ep)

  //! returns the number of busy banks
#define  udd_nb_busy_bank(ep)                      USBB_EP_RD_BITFIELD(UESTA,NBUSYBK,ep)
  //! returns the number of the current bank
#define  udd_current_bank(ep)                      USBB_EP_RD_BITFIELD(UESTA,CURRBK,ep)
  //! kills last bank
#define  udd_kill_last_in_bank(ep)                 USBB_EP_REG_SET(UECON,KILLBK,ep)
  //! tests if last bank killed
#define  Is_udd_last_in_bank_killed(ep)            USBB_EP_TST_BITS(UECON,KILLBK,ep)
  //! forces all banks full (OUT) or free (IN) interrupt
#define  udd_force_bank_interrupt(ep)              USBB_EP_REG_SET(UESTA,NBUSYBK,ep)
  //! unforces all banks full (OUT) or free (IN) interrupt
#define  udd_unforce_bank_interrupt(ep)            USBB_EP_REG_SET(UESTA,NBUSYBK,ep)
  //! enables all banks full (OUT) or free (IN) interrupt
#define  udd_enable_bank_interrupt(ep)             USBB_EP_REG_SET(UECON,NBUSYBKE,ep)
  //! disables all banks full (OUT) or free (IN) interrupt
#define  udd_disable_bank_interrupt(ep)            USBB_EP_REG_CLR(UECON,NBUSYBKE,ep)
  //! tests if all banks full (OUT) or free (IN) interrupt enabled
#define  Is_udd_bank_interrupt_enabled(ep)         USBB_EP_TST_BITS(UECON,NBUSYBKE,ep)

  //! tests if SHORT PACKET received
#define  Is_udd_short_packet(ep)                   USBB_EP_TST_BITS(UESTA,SHORTPACKETI,ep)
  //! acks SHORT PACKET received
#define  udd_ack_short_packet(ep)                  USBB_EP_REG_CLR(UESTA,SHORTPACKETI,ep)
  //! raises SHORT PACKET received
#define  udd_raise_short_packet(ep)                USBB_EP_REG_SET(UESTA,SHORTPACKETI,ep)
  //! enables SHORT PACKET received interrupt
#define  udd_enable_short_packet_interrupt(ep)     USBB_EP_REG_SET(UECON,SHORTPACKETE,ep)
  //! disables SHORT PACKET received interrupt
#define  udd_disable_short_packet_interrupt(ep)    USBB_EP_REG_CLR(UECON,SHORTPACKETE,ep)
  //! tests if SHORT PACKET received interrupt is enabled
#define  Is_udd_short_packet_interrupt_enabled(ep) USBB_EP_TST_BITS(UECON,SHORTPACKETE,ep)

  //! tests if SETUP received
#define  Is_udd_setup_received(ep)                 USBB_EP_TST_BITS(UESTA,RXSTPI,ep)
  //! acks SETUP received
#define  udd_ack_setup_received(ep)                USBB_EP_REG_CLR(UESTA,RXSTPI,ep)
  //! raises SETUP received
#define  udd_raise_setup_received(ep)              USBB_EP_REG_SET(UESTA,RXSTPI,ep)
  //! enables SETUP received interrupt
#define  udd_enable_setup_received_interrupt(ep)   USBB_EP_REG_SET(UECON,RXSTPE,ep)
  //! disables SETUP received interrupt
#define  udd_disable_setup_received_interrupt(ep)  USBB_EP_REG_CLR(UECON,RXSTPE,ep)
  //! tests if SETUP received interrupt is enabled
#define  Is_udd_setup_received_interrupt_enabled(ep) USBB_EP_TST_BITS(UECON,RXSTPE,ep)

  //! tests if OUT received
#define  Is_udd_out_received(ep)                   USBB_EP_TST_BITS(UESTA,RXOUTI,ep)
  //! acks OUT received
#define  udd_ack_out_received(ep)                  USBB_EP_REG_CLR(UESTA,RXOUTI,ep)
  //! raises OUT received
#define  udd_raise_out_received(ep)                USBB_EP_REG_SET(UESTA,RXOUTI,ep)
  //! enables OUT received interrupt
#define  udd_enable_out_received_interrupt(ep)     USBB_EP_REG_SET(UECON,RXOUTE,ep)
  //! disables OUT received interrupt
#define  udd_disable_out_received_interrupt(ep)    USBB_EP_REG_CLR(UECON,RXOUTE,ep)
  //! tests if OUT received interrupt is enabled
#define  Is_udd_out_received_interrupt_enabled(ep) USBB_EP_TST_BITS(UECON,RXOUTE,ep)

  //! tests if IN sending
#define  Is_udd_in_send(ep)                        USBB_EP_TST_BITS(UESTA,TXINI,ep)
  //! acks IN sending
#define  udd_ack_in_send(ep)                       USBB_EP_REG_CLR(UESTA,TXINI,ep)
  //! raises IN sending
#define  udd_raise_in_send(ep)                     USBB_EP_REG_SET(UESTA,TXINI,ep)
  //! enables IN sending interrupt
#define  udd_enable_in_send_interrupt(ep)          USBB_EP_REG_SET(UECON,TXINE,ep)
  //! disables IN sending interrupt
#define  udd_disable_in_send_interrupt(ep)         USBB_EP_REG_CLR(UECON,TXINE,ep)
  //! tests if IN sending interrupt is enabled
#define  Is_udd_in_send_interrupt_enabled(ep)      USBB_EP_TST_BITS(UECON,TXINE,ep)


  //! Get 64-, 32-, 16- or 8-bit access to FIFO data register of selected endpoint.
  //! @param ep     Endpoint of which to access FIFO data register
  //! @param scale  Data scale in bits: 64, 32, 16 or 8
  //! @return       Volatile 64-, 32-, 16- or 8-bit data pointer to FIFO data register
  //! @warning It is up to the user of this macro to make sure that all accesses
  //! are aligned with their natural boundaries except 64-bit accesses which
  //! require only 32-bit alignment.
  //! @warning It is up to the user of this macro to make sure that used HSB
  //! addresses are identical to the DPRAM internal pointer modulo 32 bits.
#define  udd_get_endpoint_fifo_access(ep, scale) \
          (((volatile TPASTE2(U, scale) (*)[0x10000 / ((scale) / 8)])AVR32_USBB_SLAVE)[(ep)])

//! @name USBB endpoint DMA drivers
//! These macros manage the common features of the endpoint DMA channels.
//! @{

  //! Maximum transfer size on USB DMA
#define UDD_ENDPOINT_MAX_TRANS 0x10000

#define  udd_enable_endpoint_int_dis_hdma_req(ep)     USBB_EP_REG_SET(UECON,EPDISHDMA,ep)
#define  udd_disable_endpoint_int_dis_hdma_req(ep)    USBB_EP_REG_CLR(UECON,EPDISHDMA,ep)
#define  Is_udd_endpoint_int_dis_hdma_req_enabled(ep) USBB_EP_TST_BITS(UECON,EPDISHDMA,ep)

#define  udd_raise_endpoint_dma_interrupt(ep) \
		(AVR32_USBB.udintset = AVR32_USBB_UDINTSET_DMA1INTS_MASK << ((ep) - 1))
#define  udd_clear_endpoint_dma_interrupt(ep) \
		(AVR32_USBB.udintclr = AVR32_USBB_UDINTSET_DMA1INTS_MASK << ((ep) - 1))
#define  Is_udd_endpoint_dma_interrupt(ep) \
		(Tst_bits(AVR32_USBB.udint, AVR32_USBB_UDINT_DMA1INT_MASK << ((ep) - 1)))
#define  udd_enable_endpoint_dma_interrupt(ep) \
		(AVR32_USBB.udinteset = AVR32_USBB_UDINTESET_DMA1INTES_MASK << ((ep) - 1))
#define  udd_disable_endpoint_dma_interrupt(ep) \
		(AVR32_USBB.udinteclr = AVR32_USBB_UDINTECLR_DMA1INTEC_MASK << ((ep) - 1))
#define  Is_udd_endpoint_dma_interrupt_enabled(ep) \
		(Tst_bits(AVR32_USBB.udinte, AVR32_USBB_UDINTE_DMA1INTE_MASK << ((ep) - 1)))

  //! Access points to the USBB device DMA memory map with arrayed registers
  //! @{
      //! Structure for DMA registers
typedef struct {
	union {
		unsigned long nextdesc;
		avr32_usbb_uddma1_nextdesc_t NEXTDESC;
	};
	unsigned long addr;
	union {
		unsigned long control;
		avr32_usbb_uddma1_control_t CONTROL;
	};
	union {
		unsigned long status;
		avr32_usbb_uddma1_status_t STATUS;
	};
} avr32_usbb_uddmax_t;
      //! Structure for DMA registers
#define  USBB_UDDMA_ARRAY(ep) \
		(((volatile avr32_usbb_uddmax_t *)&AVR32_USBB.uddma1_nextdesc)[(ep) - 1])

      //! Set control desc to selected endpoint DMA channel
#define  udd_endpoint_dma_set_control(ep,desc)     (USBB_UDDMA_ARRAY(ep).control=desc)
      //! Get control desc to selected endpoint DMA channel
#define  udd_endpoint_dma_get_control(ep)          (USBB_UDDMA_ARRAY(ep).control)
      //! Set RAM address to selected endpoint DMA channel
#define  udd_endpoint_dma_set_addr(ep,add)         (USBB_UDDMA_ARRAY(ep).addr=add)
      //! Get status to selected endpoint DMA channel
#define  udd_endpoint_dma_get_status(ep)           (USBB_UDDMA_ARRAY(ep).status)
   //! @}
//! @}

//! @}

void udd_ep_abort(udd_ep_id_t ep);
bool udd_ep_set_halt(udd_ep_id_t ep);
bool udd_ep_wait_stall_clear(udd_ep_id_t ep,udd_callback_halt_cleared_t callback);
bool udd_ep_run(udd_ep_id_t ep, bool b_shortpacket,
		uint8_t * buf, iram_size_t buf_size,
		udd_callback_trans_t callback);
void udd_ep_free(udd_ep_id_t ep);
bool udd_ep_alloc(udd_ep_id_t ep, uint8_t bmAttributes,
		uint16_t MaxEndpointSize);
	bool udd_ep_is_halted(udd_ep_id_t ep);
	bool udd_ep_clear_halt(udd_ep_id_t ep);
		

#endif // _USBB_DEVICE_H_

