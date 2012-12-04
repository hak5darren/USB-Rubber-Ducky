#include "compiler.h"
 #include "conf_usb.h"
 #include "udi_msc.h"
 #include "board.h"
 #include "gpio.h"
 #include "ui.h"
 #include "led.h"
 
 void ui_init(void)
 {
     LED_On(LED0);
     LED_Off(LED1);
 }
 
 void ui_powerdown(void)
 {
     LED_Off(LED0);
     LED_Off(LED1);
 }
 
 void ui_wakeup(void)
 {
     LED_On(LED0);
 }
 
 void ui_start_read(void)
 {
     LED_On(LED1);
 }
 
 void ui_stop_read(void)
 {
     LED_Off(LED1);
 }
 
 void ui_start_write(void)
 {
     LED_On(LED0);
	 LED_On(LED1);
 }
 
 void ui_stop_write(void)
 {
     LED_Off(LED0);
	 LED_Off(LED1);
 }
 
 void ui_process(uint16_t framenumber)
 {
     if ((framenumber % 1000) == 0) {
         //LED_On(LED1);
     }
     if ((framenumber % 1000) == 500) {
         //LED_Off(LED1);
     }
 }
 
 