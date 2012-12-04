#ifndef _CONF_ACCESS_H_
 #define _CONF_ACCESS_H_
 
 #include "compiler.h"
 #include "board.h"
 
 
 #define LUN_0                DISABLE    //!< On-Chip Virtual Memory.
 #define LUN_1                DISABLE     //!< AT45DBX Data Flash.
 #define LUN_2                ENABLE     //!< SD/MMC Card over SPI.
 #define LUN_3                DISABLE    //!< SD/MMC Card over MCI Slot 0.
 #define LUN_4                DISABLE
 #define LUN_5                DISABLE
 #define LUN_6                DISABLE
 #define LUN_7                DISABLE
 #define LUN_USB              DISABLE    //!< Host Mass-Storage Memory.
 
 
 
 #define VIRTUAL_MEM                             LUN_0
 #define LUN_ID_VIRTUAL_MEM                      LUN_ID_0
 #define LUN_0_INCLUDE                           "virtual_mem.h"
 #define Lun_0_test_unit_ready                   virtual_test_unit_ready
 #define Lun_0_read_capacity                     virtual_read_capacity
 #define Lun_0_wr_protect                        virtual_wr_protect
 #define Lun_0_removal                           virtual_removal
 #define Lun_0_usb_read_10                       virtual_usb_read_10
 #define Lun_0_usb_write_10                      virtual_usb_write_10
 #define Lun_0_mem_2_ram                         virtual_mem_2_ram
 #define Lun_0_ram_2_mem                         virtual_ram_2_mem
 #define LUN_0_NAME                              "\"On-Chip Virtual Memory\""
 
 #define AT45DBX_MEM                             LUN_1
 #define LUN_ID_AT45DBX_MEM                      LUN_ID_1
 #define LUN_1_INCLUDE                           "at45dbx_mem.h"
 #define Lun_1_test_unit_ready                   at45dbx_test_unit_ready
 #define Lun_1_read_capacity                     at45dbx_read_capacity
 #define Lun_1_wr_protect                        at45dbx_wr_protect
 #define Lun_1_removal                           at45dbx_removal
 #define Lun_1_usb_read_10                       at45dbx_usb_read_10
 #define Lun_1_usb_write_10                      at45dbx_usb_write_10
 #define Lun_1_mem_2_ram                         at45dbx_df_2_ram
 #define Lun_1_ram_2_mem                         at45dbx_ram_2_df
 #define LUN_1_NAME                              "\"AT45DBX Data Flash\""
 
 #define SD_MMC_SPI_MEM                          LUN_2
 #define LUN_ID_SD_MMC_SPI_MEM                   LUN_ID_2
 #define LUN_2_INCLUDE                           "sd_mmc_spi_mem.h"
 #define Lun_2_test_unit_ready                   sd_mmc_spi_test_unit_ready
 #define Lun_2_read_capacity                     sd_mmc_spi_read_capacity
 #define Lun_2_wr_protect                        sd_mmc_spi_wr_protect
 #define Lun_2_removal                           sd_mmc_spi_removal
 #define Lun_2_usb_read_10                       sd_mmc_spi_usb_read_10
 #define Lun_2_usb_write_10                      sd_mmc_spi_usb_write_10
 #define Lun_2_mem_2_ram                         sd_mmc_spi_mem_2_ram
 #define Lun_2_ram_2_mem                         sd_mmc_spi_ram_2_mem
 #define LUN_2_NAME                              "\"Ducky USB Drive\""
 
 #define SD_MMC_MCI_0_MEM                        LUN_3
 #define LUN_ID_SD_MMC_MCI_0_MEM                 LUN_ID_3
 #define LUN_3_INCLUDE                           "sd_mmc_mci_mem.h"
 #define Lun_3_test_unit_ready                   sd_mmc_mci_test_unit_ready_0
 #define Lun_3_read_capacity                     sd_mmc_mci_read_capacity_0
 #define Lun_3_wr_protect                        sd_mmc_mci_wr_protect_0
 #define Lun_3_removal                           sd_mmc_mci_removal_0
 #define Lun_3_usb_read_10                       sd_mmc_mci_usb_read_10_0
 #define Lun_3_usb_write_10                      sd_mmc_mci_usb_write_10_0
 #define Lun_3_mem_2_ram                         sd_mmc_mci_mem_2_ram_0
 #define Lun_3_ram_2_mem                         sd_mmc_mci_ram_2_mem_0
 #define LUN_3_NAME                              "\"SD/MMC Card over MCI Slot 0\""
 
 #define MEM_USB                                 LUN_USB
 #define LUN_ID_MEM_USB                          LUN_ID_USB
 #define LUN_USB_INCLUDE                         "host_mem.h"
 #define Lun_usb_test_unit_ready(lun)            host_test_unit_ready(lun)
 #define Lun_usb_read_capacity(lun, nb_sect)     host_read_capacity(lun, nb_sect)
 #define Lun_usb_read_sector_size(lun)           host_read_sector_size(lun)
 #define Lun_usb_wr_protect(lun)                 host_wr_protect(lun)
 #define Lun_usb_removal()                       host_removal()
 #define Lun_usb_mem_2_ram(addr, ram)            host_read_10_ram(addr, ram)
 #define Lun_usb_ram_2_mem(addr, ram)            host_write_10_ram(addr, ram)
 #define LUN_USB_NAME                            "\"Host Mass-Storage Memory\""
 
 
 #define memory_start_read_action(nb_sectors)    ui_start_read()
 #define memory_stop_read_action()               ui_stop_read()
 #define memory_start_write_action(nb_sectors)   ui_start_write()
 #define memory_stop_write_action()              ui_stop_write()
 #include "ui.h"
 
 
 #define ACCESS_USB           true    //!< MEM <-> USB interface.
 #define ACCESS_MEM_TO_RAM    false   //!< MEM <-> RAM interface.
 #define ACCESS_STREAM        false   //!< Streaming MEM <-> MEM interface.
 #define ACCESS_STREAM_RECORD false   //!< Streaming MEM <-> MEM interface in record mode.
 #define ACCESS_MEM_TO_MEM    false   //!< MEM <-> MEM interface.
 #define ACCESS_CODEC         false   //!< Codec interface.

 
 #define GLOBAL_WR_PROTECT    false   //!< Management of a global write protection.
 
 
  #endif // _CONF_ACCESS_H_
