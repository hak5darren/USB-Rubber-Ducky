/**
 * \file
 *
 * \brief USB Device Human Interface Device (HID) keyboard interface.
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

#ifndef _UDC_HID_KBD_H_
#define _UDC_HID_KBD_H_

#include "conf_usb.h"
#include "usb_protocol.h"
#include "usb_protocol_hid.h"
#include "udc_desc.h"
#include "udi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup udi_hid_group
 * \defgroup udi_hid_keyboard_group UDI for Human Interface Device keyboard Class
 * base on UDI HID
 * @{
 */

//! Global structure which contains standard UDI API for UDC
extern UDC_DESC_STORAGE udi_api_t udi_api_hid_kbd;

/**
 * \name Interface Descriptor
 *
 * The following structures provide the interface descriptor.
 * It must be implemented in USB configuration descriptor.
 */
//@{

//! Interface descriptor structure for HID keyboard
typedef struct {
	usb_iface_desc_t iface;
	usb_hid_descriptor_t hid;
	usb_ep_desc_t ep;
} udi_hid_kbd_desc_t;

//! Report descriptor for HID keyboard
typedef struct {
	uint8_t array[59];
} udi_hid_kbd_report_desc_t;


//! By default no string associated to this interface
#ifndef UDI_HID_KBD_STRING_ID
#define UDI_HID_KBD_STRING_ID 0
#endif

//! HID keyboard endpoints size
#define UDI_HID_KBD_EP_SIZE  8

//! Content of HID keyboard interface descriptor for all speed
#define UDI_HID_KBD_DESC    {\
	.iface.bLength             = sizeof(usb_iface_desc_t),\
	.iface.bDescriptorType     = USB_DT_INTERFACE,\
	.iface.bInterfaceNumber    = UDI_HID_KBD_IFACE_NUMBER,\
	.iface.bAlternateSetting   = 0,\
	.iface.bNumEndpoints       = 1,\
	.iface.bInterfaceClass     = HID_CLASS,\
	.iface.bInterfaceSubClass  = HID_SUB_CLASS_NOBOOT,\
	.iface.bInterfaceProtocol  = HID_PROTOCOL_KEYBOARD,\
	.iface.iInterface          = UDI_HID_KBD_STRING_ID,\
	.hid.bLength               = sizeof(usb_hid_descriptor_t),\
	.hid.bDescriptorType       = USB_DT_HID,\
	.hid.bcdHID                = LE16(USB_HID_BDC_V1_11),\
	.hid.bCountryCode          = USB_HID_NO_COUNTRY_CODE,\
	.hid.bNumDescriptors       = USB_HID_NUM_DESC,\
	.hid.bRDescriptorType      = USB_DT_HID_REPORT,\
	.hid.wDescriptorLength     = LE16(sizeof(udi_hid_kbd_report_desc_t)),\
	.ep.bLength                = sizeof(usb_ep_desc_t),\
	.ep.bDescriptorType        = USB_DT_ENDPOINT,\
	.ep.bEndpointAddress       = UDI_HID_KBD_EP_IN,\
	.ep.bmAttributes           = USB_EP_TYPE_INTERRUPT,\
	.ep.wMaxPacketSize         = LE16(UDI_HID_KBD_EP_SIZE),\
	.ep.bInterval              = 2,\
	}
//@}



/**
 * \name Interface for application
 *
 * These routines are used by application to send keyboard events
 */
//@{

/**
 * \brief Send events key modifier released
 *
 * \param modifier_id   ID of key modifier
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
bool udi_hid_kbd_modifier_up(uint8_t modifier_id);

/**
 * \brief Send events key modifier pressed
 *
 * \param modifier_id   ID of key modifier
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
bool udi_hid_kbd_modifier_down(uint8_t modifier_id);


/**
 * \brief Send events key modifier released
 *
 * \param key_id   ID of key
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
bool udi_hid_kbd_up(uint8_t key_id);

/**
 * \brief Send events key modifier pressed
 *
 * \param key_id   ID of key
 *
 */
bool udi_hid_kbd_down(uint8_t key_id);
//@}

//@}

#ifdef __cplusplus
}
#endif
#endif // _UDC_HID_KBD_H_
