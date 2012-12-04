/**
 * \file
 *
 * \brief USBB Device Driver header file.
 *
 * Copyright (C) 2009 Atmel Corporation. All rights reserved.
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 * Atmel AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#ifndef _USBB_DEVICE_H_
#define _USBB_DEVICE_H_

#include "compiler.h"
#include "preprocessor.h"


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
#define  UDD_get_endpoint_max_nbr()          (((Rd_bitfield(AVR32_USBB_ufeatures, AVR32_USBB_UFEATURES_EPT_NBR_MAX_MASK) - 1) & ((1 << AVR32_USBB_UFEATURES_EPT_NBR_MAX_SIZE) - 1)) + 1)
//! @}

//! @name USBB Device speeds management
//! @{
  //! Enable/disable device low-speed mode
#define  udd_low_speed_enable()              (Set_bits(AVR32_USBB.udcon, AVR32_USBB_UDCON_LS_MASK))
#define  udd_low_speed_disable()             (Clr_bits(AVR32_USBB.udcon, AVR32_USBB_UDCON_LS_MASK))
  //! Test if device low-speed mode is forced
#define  Is_udd_low_speed_enable()           (Tst_bits(AVR32_USBB.udcon, AVR32_USBB_UDCON_LS_MASK))

#ifdef AVR32_USBB_UDCON_SPDCONF
  //! Enable high speed mode
#  define   udd_high_speed_enable()          (Wr_bitfield(AVR32_USBB.udcon, AVR32_USBB_UDCON_SPDCONF_MASK, 0))
  //! Disable high speed mode
#  define   udd_high_speed_disable()         (Wr_bitfield(AVR32_USBB.udcon, AVR32_USBB_UDCON_SPDCONF_MASK, 3))
  //! Test if controller is in full speed mode
#  define   Is_udd_full_speed_mode()         (Rd_bitfield(AVR32_USBB.usbsta, AVR32_USBB_USBSTA_SPEED_MASK) == AVR32_USBB_USBSTA_SPEED_FULL)
#else
#  define   udd_high_speed_enable()          do { } while (0)
#  define   udd_high_speed_disable()         do { } while (0)
#  define   Is_udd_full_speed_mode()         TRUE
#endif
//! @}

//! @name USBB Device HS test mode management
//! @{
#ifdef AVR32_USBB_UDCON_SPDCONF
  //! Enable high speed test mode
#  define   udd_enable_hs_test_mode()        (Wr_bitfield(AVR32_USBB.udcon, AVR32_USBB_UDCON_SPDCONF_MASK, 2))
#  define   udd_enable_hs_test_mode_j()      (Set_bits(AVR32_USBB.udcon, AVR32_USBB_UDCON_TSTJ_MASK))
#  define   udd_enable_hs_test_mode_k()      (Set_bits(AVR32_USBB.udcon, AVR32_USBB_UDCON_TSTK_MASK))
#  define   udd_enable_hs_test_mode_packet() (Set_bits(AVR32_USBB.udcon, AVR32_USBB_UDCON_TSTPCKT_MASK))
#endif
//! @}

//! @name USBB Device vbus management
//! @{
#define  udd_enable_vbus_interrupt()         (Set_bits(AVR32_USBB.usbcon, AVR32_USBB_USBCON_VBUSTE_MASK))
#define  udd_disable_vbus_interrupt()        (Clr_bits(AVR32_USBB.usbcon, AVR32_USBB_USBCON_VBUSTE_MASK))
#define  Is_udd_vbus_interrupt_enabled()     (Tst_bits(AVR32_USBB.usbcon, AVR32_USBB_USBCON_VBUSTE_MASK))
#define  Is_udd_vbus_high()                  (Tst_bits(AVR32_USBB.usbsta, AVR32_USBB_USBSTA_VBUS_MASK))
#define  Is_udd_vbus_low()                   (!Is_udd_vbus_high())
#define  udd_ack_vbus_transition()           (AVR32_USBB.usbstaclr = AVR32_USBB_USBSTACLR_VBUSTIC_MASK)
#define  udd_raise_vbus_transition()         (AVR32_USBB.usbstaset = AVR32_USBB_USBSTASET_VBUSTIS_MASK)
#define  Is_udd_vbus_transition()            (Tst_bits(AVR32_USBB.usbsta, AVR32_USBB_USBSTA_VBUSTI_MASK))
//! @}


//! @name USBB device attach control
//! These macros manage the USBB Device attach.
//! @{
  //! detaches from USB bus
#define  udd_detach_device()                 (Set_bits(AVR32_USBB.udcon, AVR32_USBB_UDCON_DETACH_MASK))
  //! attaches to USB bus
#define  udd_attach_device()                 (Clr_bits(AVR32_USBB.udcon, AVR32_USBB_UDCON_DETACH_MASK))
  //! test if the device is detached
#define  Is_udd_detached()                   (Tst_bits(AVR32_USBB.udcon, AVR32_USBB_UDCON_DETACH_MASK))
//! @}


//! @name USBB device bus events control
//! These macros manage the USBB Device bus events.
//! @{

//! Initiates a remote wake-up event
//! @{
#define  udd_initiate_remote_wake_up()       (Set_bits(AVR32_USBB.udcon, AVR32_USBB_UDCON_RMWKUP_MASK))
#define  Is_udd_pending_remote_wake_up()     (Tst_bits(AVR32_USBB.udcon, AVR32_USBB_UDCON_RMWKUP_MASK))
//! @}

//! Manage upstream resume event (=remote wakeup)
//! The USB driver sends a resume signal called "Upstream Resume"
//! @{
#define  udd_enable_remote_wake_up_interrupt()     (AVR32_USBB.udinteset = AVR32_USBB_UDINTESET_UPRSMES_MASK)
#define  udd_disable_remote_wake_up_interrupt()    (AVR32_USBB.udinteclr = AVR32_USBB_UDINTECLR_UPRSMEC_MASK)
#define  Is_udd_remote_wake_up_interrupt_enabled() (Tst_bits(AVR32_USBB.udinte, AVR32_USBB_UDINTE_UPRSME_MASK))
#define  udd_ack_remote_wake_up_start()            (AVR32_USBB.udintclr = AVR32_USBB_UDINTCLR_UPRSMC_MASK)
#define  udd_raise_remote_wake_up_start()          (AVR32_USBB.udintset = AVR32_USBB_UDINTSET_UPRSMS_MASK)
#define  Is_udd_remote_wake_up_start()             (Tst_bits(AVR32_USBB.udint, AVR32_USBB_UDINT_UPRSM_MASK))
//! @}

//! Manage end of resume event (=remote wakeup)
//! The USB controller detects a valid "End of Resume" signal initiated by the host
//! @{
#define  udd_enable_resume_interrupt()             (AVR32_USBB.udinteset = AVR32_USBB_UDINTESET_EORSMES_MASK)
#define  udd_disable_resume_interrupt()            (AVR32_USBB.udinteclr = AVR32_USBB_UDINTECLR_EORSMEC_MASK)
#define  Is_udd_resume_interrupt_enabled()         (Tst_bits(AVR32_USBB.udinte, AVR32_USBB_UDINTE_EORSME_MASK))
#define  udd_ack_resume()                          (AVR32_USBB.udintclr = AVR32_USBB_UDINTCLR_EORSMC_MASK)
#define  udd_raise_resume()                        (AVR32_USBB.udintset = AVR32_USBB_UDINTSET_EORSMS_MASK)
#define  Is_udd_resume()                           (Tst_bits(AVR32_USBB.udint, AVR32_USBB_UDINT_EORSM_MASK))
//! @}

//! Manage wake-up event (=usb line activity)
//! The USB controller is reactivated by a filtered non-idle signal from the lines
//! @{
#define  udd_enable_wake_up_interrupt()            (AVR32_USBB.udinteset = AVR32_USBB_UDINTESET_WAKEUPES_MASK)
#define  udd_disable_wake_up_interrupt()           (AVR32_USBB.udinteclr = AVR32_USBB_UDINTECLR_WAKEUPEC_MASK)
#define  Is_udd_wake_up_interrupt_enabled()        (Tst_bits(AVR32_USBB.udinte, AVR32_USBB_UDINTE_WAKEUPE_MASK))
#define  udd_ack_wake_up()                         (AVR32_USBB.udintclr = AVR32_USBB_UDINTCLR_WAKEUPC_MASK)
#define  udd_raise_wake_up()                       (AVR32_USBB.udintset = AVR32_USBB_UDINTSET_WAKEUPS_MASK)
#define  Is_udd_wake_up()                          (Tst_bits(AVR32_USBB.udint, AVR32_USBB_UDINT_WAKEUP_MASK))
//! @}

//! Manage reset event
//! Set when a USB "End of Reset" has been detected
//! @{
#define  udd_enable_reset_interrupt()              (AVR32_USBB.udinteset = AVR32_USBB_UDINTESET_EORSTES_MASK)
#define  udd_disable_reset_interrupt()             (AVR32_USBB.udinteclr = AVR32_USBB_UDINTECLR_EORSTEC_MASK)
#define  Is_udd_reset_interrupt_enabled()          (Tst_bits(AVR32_USBB.udinte, AVR32_USBB_UDINTE_EORSTE_MASK))
#define  udd_ack_reset()                           (AVR32_USBB.udintclr = AVR32_USBB_UDINTCLR_EORSTC_MASK)
#define  udd_raise_reset()                         (AVR32_USBB.udintset = AVR32_USBB_UDINTSET_EORSTS_MASK)
#define  Is_udd_reset()                            (Tst_bits(AVR32_USBB.udint, AVR32_USBB_UDINT_EORST_MASK))
//! @}

//! Manage sart of frame event
//! @{
#define  udd_enable_sof_interrupt()                (AVR32_USBB.udinteset = AVR32_USBB_UDINTESET_SOFES_MASK)
#define  udd_disable_sof_interrupt()               (AVR32_USBB.udinteclr = AVR32_USBB_UDINTECLR_SOFEC_MASK)
#define  Is_udd_sof_interrupt_enabled()            (Tst_bits(AVR32_USBB.udinte, AVR32_USBB_UDINTE_SOFE_MASK))
#define  udd_ack_sof()                             (AVR32_USBB.udintclr = AVR32_USBB_UDINTCLR_SOFC_MASK)
#define  udd_raise_sof()                           (AVR32_USBB.udintset = AVR32_USBB_UDINTSET_SOFS_MASK)
#define  Is_udd_sof()                              (Tst_bits(AVR32_USBB.udint, AVR32_USBB_UDINT_SOF_MASK))
#define  udd_frame_number()                        (Rd_bitfield(AVR32_USBB.udfnum, AVR32_USBB_UDFNUM_FNUM_MASK))
#define  Is_udd_frame_number_crc_error()           (Tst_bits(AVR32_USBB.udfnum, AVR32_USBB_UDFNUM_FNCERR_MASK))
//! @}

//! Manage suspend event
//! @{
#define  udd_enable_suspend_interrupt()            (AVR32_USBB.udinteset = AVR32_USBB_UDINTESET_SUSPES_MASK)
#define  udd_disable_suspend_interrupt()           (AVR32_USBB.udinteclr = AVR32_USBB_UDINTECLR_SUSPEC_MASK)
#define  Is_udd_suspend_interrupt_enabled()        (Tst_bits(AVR32_USBB.udinte, AVR32_USBB_UDINTE_SUSPE_MASK))
#define  udd_ack_suspend()                         (AVR32_USBB.udintclr = AVR32_USBB_UDINTCLR_SUSPC_MASK)
#define  udd_raise_suspend()                       (AVR32_USBB.udintset = AVR32_USBB_UDINTSET_SUSPS_MASK)
#define  Is_udd_suspend()                          (Tst_bits(AVR32_USBB.udint, AVR32_USBB_UDINT_SUSP_MASK))
//! @}

//! @}

//! @name USBB device address control
//! These macros manage the USBB Device address.
//! @{
  //! enables USB device address
#define  udd_enable_address()                      (Set_bits(AVR32_USBB.udcon, AVR32_USBB_UDCON_ADDEN_MASK))
  //! disables USB device address
#define  udd_disable_address()                     (Clr_bits(AVR32_USBB.udcon, AVR32_USBB_UDCON_ADDEN_MASK))
#define  Is_udd_address_enabled()                  (Tst_bits(AVR32_USBB.udcon, AVR32_USBB_UDCON_ADDEN_MASK))
  //! configures the USB device address
#define  udd_configure_address(addr)               (Wr_bitfield(AVR32_USBB.udcon, AVR32_USBB_UDCON_UADD_MASK, addr))
  //! gets the currently configured USB device address
#define  udd_get_configured_address()              (Rd_bitfield(AVR32_USBB.udcon, AVR32_USBB_UDCON_UADD_MASK))
//! @}


//! @name USBB Device endpoint drivers
//! These macros manage the common features of the endpoints.
//! @{

//! Generic macro for USBB registers that can be arrayed
//! @{
#define USBB_ARRAY(reg,index)              ((&AVR32_USBB.reg)[(index)])
//! @}

//! @name USBB Device endpoint configguration
//! @{
  //! enables the selected endpoint
#define  udd_enable_endpoint(ep)                   (Set_bits(AVR32_USBB.uerst, AVR32_USBB_UERST_EPEN0_MASK << (ep)))
  //! disables the selected endpoint
#define  udd_disable_endpoint(ep)                  (Clr_bits(AVR32_USBB.uerst, AVR32_USBB_UERST_EPEN0_MASK << (ep)))
  //! tests if the selected endpoint is enabled
#define  Is_udd_endpoint_enabled(ep)               (Tst_bits(AVR32_USBB.uerst, AVR32_USBB_UERST_EPEN0_MASK << (ep)))
  //! resets the selected endpoint
#define  udd_reset_endpoint(ep)                    (Set_bits(AVR32_USBB.uerst, AVR32_USBB_UERST_EPRST0_MASK << (ep)),\
                                                   Clr_bits(AVR32_USBB.uerst, AVR32_USBB_UERST_EPRST0_MASK << (ep)))
  //! tests if the selected endpoint is being reset
#define  Is_udd_resetting_endpoint(ep)             (Tst_bits(AVR32_USBB.uerst, AVR32_USBB_UERST_EPRST0_MASK << (ep)))

  //! configures the selected endpoint type
#define  udd_configure_endpoint_type(ep, type)     (Wr_bitfield(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_EPTYPE_MASK, type))
  //! gets the configured selected endpoint type
#define  udd_get_endpoint_type(ep)                 (Rd_bitfield(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_EPTYPE_MASK))
  //! enables the bank autoswitch for the selected endpoint
#define  udd_enable_endpoint_bank_autoswitch(ep)   (Set_bits(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_AUTOSW_MASK))
  //! disables the bank autoswitch for the selected endpoint
#define  udd_disable_endpoint_bank_autoswitch(ep)   (Clr_bits(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_AUTOSW_MASK))
#define  Is_udd_endpoint_bank_autoswitch_enabled(ep) (Tst_bits(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_AUTOSW_MASK))
  //! configures the selected endpoint direction
#define  udd_configure_endpoint_direction(ep, dir) (Wr_bitfield(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_EPDIR_MASK, dir))
  //! gets the configured selected endpoint direction
#define  udd_get_endpoint_direction(ep)            (Rd_bitfield(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_EPDIR_MASK))
#define  Is_udd_endpoint_in(ep)                    (Tst_bits(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_EPDIR_MASK))
  //! Bounds given integer size to allowed range and rounds it up to the nearest
  //! available greater size, then applies register format of USBB controller
  //! for endpoint size bit-field.
#define  udd_format_endpoint_size(size)            (32 - clz(((U32)min(max(size, 8), 1024) << 1) - 1) - 1 - 3)
  //! configures the selected endpoint size
#define  udd_configure_endpoint_size(ep, size)     (Wr_bitfield(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_EPSIZE_MASK, udd_format_endpoint_size(size)))
  //! gets the configured selected endpoint size
#define  udd_get_endpoint_size(ep)                 (8 << Rd_bitfield(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_EPSIZE_MASK))
  //! configures the selected endpoint number of banks
#define  udd_configure_endpoint_bank(ep, bank)     (Wr_bitfield(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_EPBK_MASK, bank))
  //! gets the configured selected endpoint number of banks
#define  udd_get_endpoint_bank(ep)                 (Rd_bitfield(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_EPBK_MASK))
  //! allocates the configuration selected endpoint in DPRAM memory
#define  udd_allocate_memory(ep)                   (Set_bits(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_ALLOC_MASK))
  //! un-allocates the configuration selected endpoint in DPRAM memory
#define  udd_unallocate_memory(ep)                 (Clr_bits(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_ALLOC_MASK))
#define  Is_udd_memory_allocated(ep)               (Tst_bits(USBB_ARRAY(uecfg0,ep), AVR32_USBB_UECFG0_ALLOC_MASK))

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
#define  Is_udd_endpoint_configured(ep)            (Tst_bits(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_CFGOK_MASK))
  //! returns the control direction
#define  udd_control_direction()                   (Rd_bitfield(USBB_ARRAY(uesta0(EP_CONTROL), AVR32_USBB_UESTA0_CTRLDIR_MASK))

  //! resets the data toggle sequence
#define  udd_reset_data_toggle(ep)                 (USBB_ARRAY(uecon0set,ep) = AVR32_USBB_UECON0SET_RSTDTS_MASK)
  //! tests if the data toggle sequence is being reset
#define  Is_udd_data_toggle_reset(ep)              (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_RSTDT_MASK))
  //! returns data toggle
#define  udd_data_toggle(ep)                       (Rd_bitfield(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_DTSEQ_MASK))
//! @}


//! @name USBB Device control endpoint
//! These macros contorl the endpoints.
//! @{

//! @name USBB Device control endpoint interrupts
//! These macros control the endpoints interrupts.
//! @{
  //! enables the selected endpoint interrupt
#define  udd_enable_endpoint_interrupt(ep)         (AVR32_USBB.udinteset = AVR32_USBB_UDINTESET_EP0INTES_MASK << (ep))
  //! disables the selected endpoint interrupt
#define  udd_disable_endpoint_interrupt(ep)        (AVR32_USBB.udinteclr = AVR32_USBB_UDINTECLR_EP0INTEC_MASK << (ep))
  //! tests if the selected endpoint interrupt is enabled
#define  Is_udd_endpoint_interrupt_enabled(ep)     (Tst_bits(AVR32_USBB.udinte, AVR32_USBB_UDINTE_EP0INTE_MASK << (ep)))
  //! tests if an interrupt is triggered by the selected endpoint
#define  Is_udd_endpoint_interrupt(ep)             (Tst_bits(AVR32_USBB.udint, AVR32_USBB_UDINT_EP0INT_MASK << (ep)))
  //! returns the lowest endpoint number generating an endpoint interrupt or MAX_PEP_NB if none
#define  udd_get_interrupt_endpoint_number()       (ctz(((AVR32_USBB.udint >> AVR32_USBB_UDINT_EP0INT_OFFSET) &\
                                                   (AVR32_USBB.udinte >> AVR32_USBB_UDINTE_EP0INTE_OFFSET)) |\
                                                   (1 << MAX_PEP_NB)))
//! @}

//! @name USBB Device control endpoint errors
//! These macros control the endpoint errors.
//! @{
  //! enables the STALL handshake
#define  udd_enable_stall_handshake(ep)            (USBB_ARRAY(uecon0set,ep) = AVR32_USBB_UECON0SET_STALLRQS_MASK)
  //! disables the STALL handshake
#define  udd_disable_stall_handshake(ep)           (USBB_ARRAY(uecon0clr,ep) = AVR32_USBB_UECON0CLR_STALLRQC_MASK)
  //! tests if STALL handshake request is running
#define  Is_udd_endpoint_stall_requested(ep)       (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_STALLRQ_MASK))
  //! tests if STALL sent
#define  Is_udd_stall(ep)                          (Tst_bits(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_STALLEDI_MASK))
  //! acks STALL sent
#define  udd_ack_stall(ep)                         (USBB_ARRAY(uesta0clr,ep) = AVR32_USBB_UESTA0CLR_STALLEDIC_MASK)
  //! raises STALL sent
#define  udd_raise_stall(ep)                       (USBB_ARRAY(uesta0set,ep) = AVR32_USBB_UESTA0SET_STALLEDIS_MASK)
  //! enables STALL sent interrupt
#define  udd_enable_stall_interrupt(ep)            (USBB_ARRAY(uecon0set,ep) = AVR32_USBB_UECON0SET_STALLEDES_MASK)
  //! disables STALL sent interrupt
#define  udd_disable_stall_interrupt(ep)           (USBB_ARRAY(uecon0clr,ep) = AVR32_USBB_UECON0CLR_STALLEDEC_MASK)
  //! tests if STALL sent interrupt is enabled
#define  Is_udd_stall_interrupt_enabled(ep)        (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_STALLEDE_MASK))

  //! tests if NAK OUT received
#define  Is_udd_nak_out(ep)                        (Tst_bits(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_NAKOUTI_MASK))
  //! acks NAK OUT received
#define  udd_ack_nak_out(ep)                       (USBB_ARRAY(uesta0clr,ep) = AVR32_USBB_UESTA0CLR_NAKOUTIC_MASK)
  //! raises NAK OUT received
#define  udd_raise_nak_out(ep)                     (USBB_ARRAY(uesta0set,ep) = AVR32_USBB_UESTA0SET_NAKOUTIS_MASK)
  //! enables NAK OUT interrupt
#define  udd_enable_nak_out_interrupt(ep)          (USBB_ARRAY(uecon0set,ep) = AVR32_USBB_UECON0SET_NAKOUTES_MASK)
  //! disables NAK OUT interrupt
#define  udd_disable_nak_out_interrupt(ep)         (USBB_ARRAY(uecon0clr,ep) = AVR32_USBB_UECON0CLR_NAKOUTEC_MASK)
  //! tests if NAK OUT interrupt is enabled
#define  Is_udd_nak_out_interrupt_enabled(ep)      (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_NAKOUTE_MASK))

  //! tests if NAK IN received
#define  Is_udd_nak_in(ep)                         (Tst_bits(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_NAKINI_MASK))
  //! acks NAK IN received
#define  udd_ack_nak_in(ep)                        (USBB_ARRAY(uesta0clr,ep) = AVR32_USBB_UESTA0CLR_NAKINIC_MASK)
  //! raises NAK IN received
#define  udd_raise_nak_in(ep)                      (USBB_ARRAY(uesta0set,ep) = AVR32_USBB_UESTA0SET_NAKINIS_MASK)
  //! enables NAK IN interrupt
#define  udd_enable_nak_in_interrupt(ep)           (USBB_ARRAY(uecon0set,ep) = AVR32_USBB_UECON0SET_NAKINES_MASK)
  //! disables NAK IN interrupt
#define  udd_disable_nak_in_interrupt(ep)          (USBB_ARRAY(uecon0clr,ep) = AVR32_USBB_UECON0CLR_NAKINEC_MASK)
  //! tests if NAK IN interrupt is enabled
#define  Is_udd_nak_in_interrupt_enabled(ep)       (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_NAKINE_MASK))

  //! acks endpoint isochronous overflow interrupt
#define  udd_ack_overflow_interrupt(ep)            (USBB_ARRAY(uesta0clr,ep) = AVR32_USBB_UESTA0CLR_OVERFIC_MASK)
  //! raises endpoint isochronous overflow interrupt
#define  udd_raise_overflow_interrupt(ep)          (USBB_ARRAY(uesta0set,ep) = AVR32_USBB_UESTA0SET_OVERFIS_MASK)
  //! tests if an overflow occurs
#define  Is_udd_overflow(ep)                       (Tst_bits(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_OVERFI_MASK))
  //! enables overflow interrupt
#define  udd_enable_overflow_interrupt(ep)         (USBB_ARRAY(uecon0set,ep) = AVR32_USBB_UECON0SET_OVERFES_MASK)
  //! disables overflow interrupt
#define  udd_disable_overflow_interrupt(ep)        (USBB_ARRAY(uecon0clr,ep) = AVR32_USBB_UECON0CLR_OVERFEC_MASK)
  //! tests if overflow interrupt is enabled
#define  Is_udd_overflow_interrupt_enabled(ep)     (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_OVERFE_MASK))

  //! acks endpoint isochronous underflow interrupt
#define  udd_ack_underflow_interrupt(ep)           (USBB_ARRAY(uesta0clr,ep) = AVR32_USBB_UESTA0CLR_UNDERFIC_MASK)
  //! raises endpoint isochronous underflow interrupt
#define  udd_raise_underflow_interrupt(ep)         (USBB_ARRAY(uesta0set,ep) = AVR32_USBB_UESTA0SET_UNDERFIS_MASK)
  //! tests if an underflow occurs
#define  Is_udd_underflow(ep)                      (Tst_bits(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_UNDERFI_MASK))
  //! enables underflow interrupt
#define  udd_enable_underflow_interrupt(ep)        (USBB_ARRAY(uecon0set,ep) = AVR32_USBB_UECON0SET_RXSTPES_MASK)
  //! disables underflow interrupt
#define  udd_disable_underflow_interrupt(ep)       (USBB_ARRAY(uecon0clr,ep) = AVR32_USBB_UECON0CLR_RXSTPEC_MASK)
  //! tests if underflow interrupt is enabled
#define  Is_udd_underflow_interrupt_enabled(ep)    (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_RXSTPE_MASK))

  //! tests if CRC ERROR ISO OUT detected
#define  Is_udd_crc_error(ep)                      (Tst_bits(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_STALLEDI_MASK))
  //! acks CRC ERROR ISO OUT detected
#define  udd_ack_crc_error(ep)                     (USBB_ARRAY(uesta0clr,ep) = AVR32_USBB_UESTA0CLR_STALLEDIC_MASK)
  //! raises CRC ERROR ISO OUT detected
#define  udd_raise_crc_error(ep)                   (USBB_ARRAY(uesta0set,ep) = AVR32_USBB_UESTA0SET_STALLEDIS_MASK)
  //! enables CRC ERROR ISO OUT detected interrupt
#define  udd_enable_crc_error_interrupt(ep)        (USBB_ARRAY(uecon0set,ep) = AVR32_USBB_UECON0SET_STALLEDES_MASK)
  //! disables CRC ERROR ISO OUT detected interrupt
#define  udd_disable_crc_error_interrupt(ep)       (USBB_ARRAY(uecon0clr,ep) = AVR32_USBB_UECON0CLR_STALLEDEC_MASK)
  //! tests if CRC ERROR ISO OUT detected interrupt is enabled
#define  Is_udd_crc_error_interrupt_enabled(ep)    (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_STALLEDE_MASK))
//! @}

//! @name USBB Device control endpoint errors
//! These macros control the endpoint errors.
//! @{

  //! tests if endpoint read allowed
#define  Is_udd_read_enabled(ep)                   (Tst_bits(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_RWALL_MASK))
  //! tests if endpoint write allowed
#define  Is_udd_write_enabled(ep)                  (Tst_bits(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_RWALL_MASK))

  //! returns the byte count
#define  udd_byte_count(ep)                        (Rd_bitfield(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_BYCT_MASK))
  //! clears FIFOCON bit
#define  udd_ack_fifocon(ep)                       (USBB_ARRAY(uecon0clr,ep) = AVR32_USBB_UECON0CLR_FIFOCONC_MASK)
  //! tests if FIFOCON bit set
#define  Is_udd_fifocon(ep)                        (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_FIFOCON_MASK))

  //! returns the number of busy banks
#define  udd_nb_busy_bank(ep)                      (Rd_bitfield(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_NBUSYBK_MASK))
  //! returns the number of the current bank
#define  udd_current_bank(ep)                      (Rd_bitfield(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_CURRBK_MASK))
  //! kills last bank
#define  udd_kill_last_in_bank(ep)                 (USBB_ARRAY(uecon0set,ep) = AVR32_USBB_UECON0SET_KILLBKS_MASK)
  //! tests if last bank killed
#define  Is_udd_last_in_bank_killed(ep)            (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_KILLBK_MASK))
  //! forces all banks full (OUT) or free (IN) interrupt
#define  udd_force_bank_interrupt(ep)              (USBB_ARRAY(uesta0set,ep) = AVR32_USBB_UESTA0SET_NBUSYBKS_MASK)
  //! unforces all banks full (OUT) or free (IN) interrupt
#define  udd_unforce_bank_interrupt(ep)            (USBB_ARRAY(uesta0set,ep) = AVR32_USBB_UESTA0SET_NBUSYBKS_MASK)
  //! enables all banks full (OUT) or free (IN) interrupt
#define  udd_enable_bank_interrupt(ep)             (USBB_ARRAY(uecon0set,ep) = AVR32_USBB_UECON0SET_NBUSYBKES_MASK)
  //! disables all banks full (OUT) or free (IN) interrupt
#define  udd_disable_bank_interrupt(ep)            (USBB_ARRAY(uecon0clr,ep) = AVR32_USBB_UECON0CLR_NBUSYBKEC_MASK)
  //! tests if all banks full (OUT) or free (IN) interrupt enabled
#define  Is_udd_bank_interrupt_enabled(ep)         (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_NBUSYBKE_MASK))

  //! tests if SHORT PACKET received
#define  Is_udd_short_packet(ep)                   (Tst_bits(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_SHORTPACKETI_MASK))
  //! acks SHORT PACKET received
#define  udd_ack_short_packet(ep)                  (USBB_ARRAY(uesta0clr,ep) = AVR32_USBB_UESTA0CLR_SHORTPACKETIC_MASK)
  //! raises SHORT PACKET received
#define  udd_raise_short_packet(ep)                (USBB_ARRAY(uesta0set,ep) = AVR32_USBB_UESTA0SET_SHORTPACKETIS_MASK)
  //! enables SHORT PACKET received interrupt
#define  udd_enable_short_packet_interrupt(ep)     (USBB_ARRAY(uecon0set,ep) = AVR32_USBB_UECON0SET_SHORTPACKETES_MASK)
  //! disables SHORT PACKET received interrupt
#define  udd_disable_short_packet_interrupt(ep)    (USBB_ARRAY(uecon0clr,ep) = AVR32_USBB_UECON0CLR_SHORTPACKETEC_MASK)
  //! tests if SHORT PACKET received interrupt is enabled
#define  Is_udd_short_packet_interrupt_enabled(ep) (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_SHORTPACKETE_MASK))

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
  //! enables the disabling of HDMA requests by endpoint interrupts
#define  udd_enable_endpoint_int_dis_hdma_req(ep)     (USBB_ARRAY(uecon0set(ep) = AVR32_USBB_UECON0SET_EPDISHDMAS_MASK)
  //! disables the disabling of HDMA requests by endpoint interrupts
#define  udd_disable_endpoint_int_dis_hdma_req(ep)    (USBB_ARRAY(uecon0clr(ep) = AVR32_USBB_UECON0CLR_EPDISHDMAC_MASK)
  //! tests if the disabling of HDMA requests by endpoint interrupts is enabled
#define  Is_udd_endpoint_int_dis_hdma_req_enabled(ep) (Tst_bits(USBB_ARRAY(uecon0(ep), AVR32_USBB_UECON0_EPDISHDMA_MASK))

  //! raises the selected endpoint DMA channel interrupt
#define  udd_raise_endpoint_dma_interrupt(ep)         (AVR32_USBB.udintset = AVR32_USBB_UDINTSET_DMA1INTS_MASK << ((ep) - 1))
  //! tests if an interrupt is triggered by the selected endpoint DMA channel
#define  Is_udd_endpoint_dma_interrupt(ep)            (Tst_bits(AVR32_USBB.udint, AVR32_USBB_UDINT_DMA1INT_MASK << ((ep) - 1)))
  //! enables the selected endpoint DMA channel interrupt
#define  udd_enable_endpoint_dma_interrupt(ep)        (AVR32_USBB.udinteset = AVR32_USBB_UDINTESET_DMA1INTES_MASK << ((ep) - 1))
  //! disables the selected endpoint DMA channel interrupt
#define  udd_disable_endpoint_dma_interrupt(ep)       (AVR32_USBB.udinteclr = AVR32_USBB_UDINTECLR_DMA1INTEC_MASK << ((ep) - 1))
  //! tests if the selected endpoint DMA channel interrupt is enabled
#define  Is_udd_endpoint_dma_interrupt_enabled(ep)    (Tst_bits(AVR32_USBB.udinte, AVR32_USBB_UDINTE_DMA1INTE_MASK << ((ep) - 1)))

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
} avr32_usbb_uxdmax_t;
      //! Structure for DMA registers
#define  USBB_UDDMA_ARRAY(ep)                (((volatile avr32_usbb_uxdmax_t *)&AVR32_USBB.uddma1_nextdesc)[(ep) - 1])

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

//! @name USBB Device control endpoint errors
//! These macros control the endpoint errors.
//! @{

  //! tests if SETUP received
#define  Is_udd_setup_received(ep)                    (Tst_bits(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_RXSTPI_MASK))
  //! acks SETUP received                            
#define  udd_ack_setup_received(ep)                   (USBB_ARRAY(uesta0clr,ep) = AVR32_USBB_UESTA0CLR_RXSTPIC_MASK)
  //! raises SETUP received                          
#define  udd_raise_setup_received(ep)                 (USBB_ARRAY(uesta0set,ep) = AVR32_USBB_UESTA0SET_RXSTPIS_MASK)
  //! enables SETUP received interrupt               
#define  udd_enable_setup_received_interrupt(ep)      (USBB_ARRAY(uecon0set,ep) = AVR32_USBB_UECON0SET_RXSTPES_MASK)
  //! disables SETUP received interrupt              
#define  udd_disable_setup_received_interrupt()       (USBB_ARRAY(uecon0clr(EP_CONTROL) = AVR32_USBB_UECON0CLR_RXSTPEC_MASK)
  //! tests if SETUP received interrupt is enabled
#define  Is_udd_setup_received_interrupt_enabled(ep)  (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_RXSTPE_MASK))

  //! tests if OUT received
#define  Is_udd_out_received(ep)                   (Tst_bits(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_RXOUTI_MASK))
  //! acks OUT received
#define  udd_ack_out_received(ep)                  (USBB_ARRAY(uesta0clr,ep) = AVR32_USBB_UESTA0CLR_RXOUTIC_MASK)
  //! raises OUT received
#define  udd_raise_out_received(ep)                (USBB_ARRAY(uesta0set,ep) = AVR32_USBB_UESTA0SET_RXOUTIS_MASK)
  //! enables OUT received interrupt
#define  udd_enable_out_received_interrupt(ep)     (USBB_ARRAY(uecon0set,ep) = AVR32_USBB_UECON0SET_RXOUTES_MASK)
  //! disables OUT received interrupt
#define  udd_disable_out_received_interrupt(ep)    (USBB_ARRAY(uecon0clr,ep) = AVR32_USBB_UECON0CLR_RXOUTEC_MASK)
  //! tests if OUT received interrupt is enabled
#define  Is_udd_out_received_interrupt_enabled(ep) (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_RXOUTE_MASK))

  //! tests if IN sending
#define  Is_udd_in_send(ep)                        (Tst_bits(USBB_ARRAY(uesta0,ep), AVR32_USBB_UESTA0_TXINI_MASK))
  //! acks IN sending                             
#define  udd_ack_in_send(ep)                       (USBB_ARRAY(uesta0clr,ep) = AVR32_USBB_UESTA0CLR_TXINIC_MASK)
  //! raises IN sending                           
#define  udd_raise_in_send(ep)                     (USBB_ARRAY(uesta0set,ep) = AVR32_USBB_UESTA0SET_TXINIS_MASK)
  //! enables IN sending interrupt                
#define  udd_enable_in_send_interrupt(ep)          (USBB_ARRAY(uecon0set,ep) = AVR32_USBB_UECON0SET_TXINES_MASK)
  //! disables IN sending interrupt               
#define  udd_disable_in_send_interrupt(ep)         (USBB_ARRAY(uecon0clr,ep) = AVR32_USBB_UECON0CLR_TXINEC_MASK)
  //! tests if IN sending interrupt is enabled    
#define  Is_udd_in_send_interrupt_enabled(ep)      (Tst_bits(USBB_ARRAY(uecon0,ep), AVR32_USBB_UECON0_TXINE_MASK))
//! @}          

//! @}

#endif // _USBB_DEVICE_H_
