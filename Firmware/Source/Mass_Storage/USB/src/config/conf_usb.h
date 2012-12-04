#ifndef _CONF_USB_H_
#define _CONF_USB_H_
 
#include "compiler.h"
#include "main.h"
 
#define  USB_DEVICE_VENDOR_ID             USB_VID_ATMEL
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_AVR_MSC
#define  USB_DEVICE_MAJOR_VERSION         1
#define  USB_DEVICE_MINOR_VERSION         0
#define  USB_DEVICE_POWER                 100 // Consumption on Vbus line (mA)
#define  USB_DEVICE_ATTR                \
     (USB_CONFIG_ATTR_BUS_POWERED)
//  (USB_CONFIG_ATTR_SELF_POWERED)
//  (USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_SELF_POWERED)
//  (USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_BUS_POWERED)
 
#define  USB_DEVICE_MANUFACTURE_NAME      "AVR32 Ducky"
#define  USB_DEVICE_PRODUCT_NAME          "Ducky Mass Storage"
#define  USB_DEVICE_SERIAL_NAME           "123123123123"    // Disk SN for MSC
 
 
#if (UC3A3||UC3A4)
     #define  USB_DEVICE_HS_SUPPORT
#endif
 
 
 
#define  UDC_VBUS_EVENT(b_vbus_high)      main_vbus_action(b_vbus_high)
#define  UDC_SOF_EVENT()                  main_sof_action()
#define  UDC_SUSPEND_EVENT()              main_suspend_action()
#define  UDC_RESUME_EVENT()               main_resume_action()
 
// #define  UDC_REMOTEWAKEUP_ENABLE()        user_callback_remotewakeup_enable()
// #define  UDC_REMOTEWAKEUP_DISABLE()       user_callback_remotewakeup_disable()
// #define  UDC_GET_EXTRA_STRING()
 
#define UDI_MSC_GLOBAL_VENDOR_ID            \
    'A', 'T', 'M', 'E', 'L', ' ', ' ', ' '
#define UDI_MSC_GLOBAL_PRODUCT_VERSION            \
    '1', '.', '0', '0'
 
#define  UDI_MSC_ENABLE_EXT()          main_msc_enable()
#define  UDI_MSC_DISABLE_EXT()         main_msc_disable()
 
#define  USB_DEVICE_EP_CTRL_SIZE       64

//! Endpoint numbers used by MSC interface
#define  UDI_MSC_EP_IN                 (1 | USB_EP_DIR_IN)
#define  UDI_MSC_EP_OUT                (2 | USB_EP_DIR_OUT)

//! Interface number is 0 because it is the unique interface
#define  UDI_MSC_IFACE_NUMBER          0

/**
 * \name UDD Configuration
 */
//@{
//! 2 endpoints used by MSC interface
#define  USB_DEVICE_MAX_EP             2
//@}
 
#endif // _CONF_USB_H_
