//_____  M A I N ___________________________________________________________
//
// Module		: Ducky Mass Storage
// Description	: Simple USB (MMC/SDCARD) Mass Storage Device
// Date			: June 7, 2012
// Author       : Snake
// Credit		: ATMEL
//__________________________________________________________________________

#include <asf.h>

#include "compiler.h"
 #include "preprocessor.h"
 #include "board.h"
 #include "gpio.h"
 #include "sysclk.h"
 #include "sleepmgr.h"
 #include "conf_usb.h"
 #include "conf_sd_mmc_spi.h"
 #include "udd.h"
 #include "udc.h"
 #include "udi_msc.h"
 #include "ui.h"
 
#include "usb_protocol.h"
#include "usb_protocol_msc.h"
#include "spc_protocol.h"
#include "sbc_protocol.h"
#include "ctrl_access.h"
 
 static bool main_b_msc_enable = false;
 
 int main(void)
 {
     irq_initialize_vectors();
     cpu_irq_enable();
 
     // Initialize the sleep manager
     sleepmgr_init();
     sysclk_init();
     board_init();
 
     memories_initialization(FOSC0);
	 //sd_mmc_resources_init(FOSC0);
	 
     // Start USB stack to authorize VBus monitoring
     udc_start();
 
     if (!udc_include_vbus_monitoring()) {
         // VBUS monitoring is not available on this product
         // thereby VBUS has to be considered as present
         main_vbus_action(true);
     }
 
     // The main loop manages only the power mode
     // because the USB management is done by interrupt	 
       while (true) {
 
         if (main_b_msc_enable) {
             if (!udi_msc_process_trans()) {
                 sleepmgr_enter_sleep();
             }
         }else{
             sleepmgr_enter_sleep();
         }
     }
 }
 
 void main_vbus_action(bool b_high)
 {
     if (b_high) {
         // Attach USB Device
         udc_attach();
     } else {
         // VBUS not present
         udc_detach();
     }
 }
 
 void main_suspend_action(void)
 {

 }
 
 void main_resume_action(void)
 {
 }
 
 void main_sof_action(void)
 {
	   if (!main_b_msc_enable)
         return;
     ui_process(udd_get_frame_number());
 }

 
 void main_remotewakeup_enable(void)
 {
	 
 }
 
 void main_remotewakeup_disable(void){
	 
 }
 
 bool main_msc_enable(){
	 main_b_msc_enable = true;
     return true;
 }
 
 void main_msc_disable(){
	 
 }
 
 void memories_initialization(long pba_hz)
 {
	 #if (defined SD_MMC_SPI_MEM) && (SD_MMC_SPI_MEM == ENABLE)
    // SPI options.
    spi_options_t spiOptions = {
        .reg          = SD_MMC_SPI_NPCS,
        .baudrate     = SD_MMC_SPI_MASTER_SPEED,  // Defined in conf_sd_mmc_spi.h.
        .bits         = SD_MMC_SPI_BITS,          // Defined in conf_sd_mmc_spi.h.
        .spck_delay   = 0,
        .trans_delay  = 0,
        .stay_act     = 1,
        .spi_mode     = 0,
        .modfdis      = 1
    };

    sysclk_enable_peripheral_clock(SD_MMC_SPI);

    // If the SPI used by the SD/MMC is not enabled.
    if (!spi_is_enabled(SD_MMC_SPI)) {
        // Initialize as master.
        spi_initMaster(SD_MMC_SPI, &spiOptions);
        // Set selection mode: variable_ps, pcs_decode, delay.
        spi_selectionMode(SD_MMC_SPI, 0, 0, 0);
        // Enable SPI.
        spi_enable(SD_MMC_SPI);
    }

    // Initialize SD/MMC with SPI PB clock.
    sd_mmc_spi_init(spiOptions,pba_hz);
#endif  // SD_MMC_SPI_MEM == ENABLE
}