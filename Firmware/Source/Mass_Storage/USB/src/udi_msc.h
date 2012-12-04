 #ifndef _UDI_MSC_H_
 #define _UDI_MSC_H_
 
 #include "conf_usb.h"
 #include "usb_protocol.h"
 #include "usb_protocol_msc.h"
 #include "udd.h"
 #include "udc_desc.h"
 #include "udi.h"
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
 
 typedef struct {
     usb_iface_desc_t iface;
     usb_ep_desc_t ep_in;
     usb_ep_desc_t ep_out;
 } udi_msc_desc_t;
 
 #ifndef UDI_MSC_STRING_ID
 #define UDI_MSC_STRING_ID     0
 #endif
 
 #define UDI_MSC_EPS_SIZE_FS   64
 
 #define UDI_MSC_EPS_SIZE_HS   512
 
 #define UDI_MSC_DESC      \
    .iface.bLength             = sizeof(usb_iface_desc_t),\
    .iface.bDescriptorType     = USB_DT_INTERFACE,\
    .iface.bInterfaceNumber    = UDI_MSC_IFACE_NUMBER,\
    .iface.bAlternateSetting   = 0,\
    .iface.bNumEndpoints       = 2,\
    .iface.bInterfaceClass     = MSC_CLASS,\
    .iface.bInterfaceSubClass  = MSC_SUBCLASS_TRANSPARENT,\
    .iface.bInterfaceProtocol  = MSC_PROTOCOL_BULK,\
    .iface.iInterface          = UDI_MSC_STRING_ID,\
    .ep_in.bLength             = sizeof(usb_ep_desc_t),\
    .ep_in.bDescriptorType     = USB_DT_ENDPOINT,\
    .ep_in.bEndpointAddress    = UDI_MSC_EP_IN,\
    .ep_in.bmAttributes        = USB_EP_TYPE_BULK,\
    .ep_in.bInterval           = 0,\
    .ep_out.bLength            = sizeof(usb_ep_desc_t),\
    .ep_out.bDescriptorType    = USB_DT_ENDPOINT,\
    .ep_out.bEndpointAddress   = UDI_MSC_EP_OUT,\
    .ep_out.bmAttributes       = USB_EP_TYPE_BULK,\
    .ep_out.bInterval          = 0,
 
 #define UDI_MSC_DESC_FS   {\
    UDI_MSC_DESC \
    .ep_in.wMaxPacketSize      = LE16(UDI_MSC_EPS_SIZE_FS),\
    .ep_out.wMaxPacketSize     = LE16(UDI_MSC_EPS_SIZE_FS),\
    }
 
 #define UDI_MSC_DESC_HS   {\
    UDI_MSC_DESC \
    .ep_in.wMaxPacketSize      = LE16(UDI_MSC_EPS_SIZE_HS),\
    .ep_out.wMaxPacketSize     = LE16(UDI_MSC_EPS_SIZE_HS),\
    }
 
 
 
 extern UDC_DESC_STORAGE udi_api_t udi_api_msc;
 
 
 bool udi_msc_process_trans(void);
 
 bool udi_msc_trans_block(bool b_read, uint8_t * block, iram_size_t block_size,
         void (*callback) (udd_ep_status_t status, iram_size_t n));
 
 
 
 #ifdef __cplusplus
 }
 #endif
 #endif // _UDI_MSC_H_