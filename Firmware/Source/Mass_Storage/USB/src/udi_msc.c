/*
 * udi_msc.c
 *
 * Created: 27/04/2012 15:58:27
 *  Author: Andy
 */ 
#include "conf_usb.h"
 #include "usb_protocol.h"
 #include "usb_protocol_msc.h"
 #include "spc_protocol.h"
 #include "sbc_protocol.h"
 #include "udd.h"
 #include "udc.h"
 #include "udi_msc.h"
 #include "ctrl_access.h"
 #include <string.h>
 
 
 
 bool udi_msc_enable(void);
 void udi_msc_disable(void);
 bool udi_msc_setup(void);
 uint8_t udi_msc_getsetting(void);
 
 UDC_DESC_STORAGE udi_api_t udi_api_msc = {
     .enable = udi_msc_enable,
     .disable = udi_msc_disable,
     .setup = udi_msc_setup,
     .getsetting = udi_msc_getsetting,
     .sof_notify = NULL,
 };
 
 
 #define  UDI_MSC_BLOCK_SIZE   512L
 
 
 
 UDC_BSS(4) static struct usb_msc_cbw udi_msc_cbw;
 UDC_DATA(4) static struct usb_msc_csw udi_msc_csw =
         {.dCSWSignature = CPU_TO_BE32(USB_CSW_SIGNATURE) };
 UDC_DATA(4) static uint8_t udi_msc_nb_lun = 0;
 UDC_BSS(4) static struct scsi_request_sense_data udi_msc_sense;
 
 
 static bool udi_msc_b_cbw_invalid = false;
 static bool udi_msc_b_trans_req = false;
 static bool udi_msc_b_read;
 static uint32_t udi_msc_addr;
 static uint16_t udi_msc_nb_block;
 volatile bool udi_msc_b_ack_trans = true;
 volatile bool udi_msc_b_abort_trans;
 
 
 
 
 
 static void udi_msc_cbw_invalid(void);
 
 static void udi_msc_csw_invalid(void);
 
 static void udi_msc_cbw_wait(void);
 
 void udi_msc_cbw_received(udd_ep_status_t status, iram_size_t nb_received);
 
 static bool udi_msc_cbw_validate(uint32_t alloc_len, uint8_t dir_flag);
 
 
 
 static void udi_msc_data_send(uint8_t * buffer, uint8_t buf_size);
 
 void udi_msc_data_sent(udd_ep_status_t status, iram_size_t nb_sent);
 
 
 
 static void udi_msc_csw_process(void);
 
 void udi_msc_csw_send(void);
 
 void udi_msc_csw_sent(udd_ep_status_t status, iram_size_t nb_sent);
 
 
 
 static void udi_msc_clear_sense(void);
 
 static void udi_msc_sense_fail(uint8_t sense_key, uint16_t add_sense,
         uint32_t lba);
 
 static void udi_msc_sense_pass(void);
 
 static void udi_msc_sense_fail_not_present(void);
 
 static void udi_msc_sense_fail_busy_or_change(void);
 
 static void udi_msc_sense_fail_hardware(void);
 
 static void udi_msc_sense_fail_protected(void);
 
 static void udi_msc_sense_fail_cdb_invalid(void);
 
 static void udi_msc_sense_command_invalid(void);
 
 
 
 static void udi_msc_spc_requestsense(void);
 
 static void udi_msc_spc_inquiry(void);
 
 static bool udi_msc_spc_testunitready_global(void);
 
 static void udi_msc_spc_testunitready(void);
 
 static void udi_msc_spc_mode_sense(bool b_sense10);
 
 static void udi_msc_sbc_read_capacity(void);
 
 static void udi_msc_sbc_trans(bool b_read);
 
 
 
 bool udi_msc_enable(void)
 {
     udi_msc_b_trans_req = false;
     udi_msc_b_cbw_invalid = false;
     udi_msc_nb_lun = get_nb_lun();
     if (0 == udi_msc_nb_lun)
         return false;   // No lun available, then not authorize to enable interface
     udi_msc_nb_lun--;
     // Call application callback
     // to initialize memories or signal that interface is enabled
     if (!UDI_MSC_ENABLE_EXT())
         return false;
     // Start MSC process by CBW reception
     udi_msc_cbw_wait();
     return true;
 }
 
 
 void udi_msc_disable(void)
 {
     udi_msc_b_trans_req = false;
     UDI_MSC_DISABLE_EXT();
 }
 
 
 bool udi_msc_setup(void)
 {
     if (Udd_setup_is_in()) {
         // Requests Interface GET
         if (Udd_setup_type() == USB_REQ_TYPE_CLASS) {
             // Requests Class Interface Get
             switch (udd_g_ctrlreq.req.bRequest) {
             case USB_REQ_MSC_GET_MAX_LUN:
                 // Give the number of memories available
                 if (1 != udd_g_ctrlreq.req.wLength)
                     return false;   // Error for USB host
                 if (0 != udd_g_ctrlreq.req.wValue)
                     return false;
                 udd_g_ctrlreq.payload = &udi_msc_nb_lun;
                 udd_g_ctrlreq.payload_size = 1;
                 return true;
             }
         }
     }
     if (Udd_setup_is_out()) {
         // Requests Interface SET
         if (Udd_setup_type() == USB_REQ_TYPE_CLASS) {
             // Requests Class Interface Set
             switch (udd_g_ctrlreq.req.bRequest) {
             case USB_REQ_MSC_BULK_RESET:
                 // Reset MSC interface
                 if (0 != udd_g_ctrlreq.req.wLength)
                     return false;
                 if (0 != udd_g_ctrlreq.req.wValue)
                     return false;
                 udi_msc_b_cbw_invalid = false;
                 udi_msc_b_trans_req = false;
                 // Abort all tasks (transfer or clear stall wait) on endpoints
                 udd_ep_abort(UDI_MSC_EP_OUT);
                 udd_ep_abort(UDI_MSC_EP_IN);
                 // Restart by CBW wait
                 udi_msc_cbw_wait();
                 return true;
             }
         }
     }
     return false;   // Not supported request
 }
 
 uint8_t udi_msc_getsetting(void)
 {
     return 0;   // MSC don't have multiple alternate setting
 }
 
 
 //---------------------------------------------
 //------- Routines to process CBW packet
 
 static void udi_msc_cbw_invalid(void)
 {
     if (!udi_msc_b_cbw_invalid)
         return; // Don't restall endpoint if error reseted by setup
     udd_ep_set_halt(UDI_MSC_EP_OUT);
     // If stall cleared then restall it. Only Setup MSC Reset can clear it
     udd_ep_wait_stall_clear(UDI_MSC_EP_OUT, udi_msc_cbw_invalid);
 }
 
 static void udi_msc_csw_invalid(void)
 {
     if (!udi_msc_b_cbw_invalid)
         return; // Don't restall endpoint if error reseted by setup
     udd_ep_set_halt(UDI_MSC_EP_IN);
     // If stall cleared then restall it. Only Setup MSC Reset can clear it
     udd_ep_wait_stall_clear(UDI_MSC_EP_IN, udi_msc_csw_invalid);
 }
 
 static void udi_msc_cbw_wait(void)
 {
     // Register buffer and callback on OUT endpoint
     if (!udd_ep_run(UDI_MSC_EP_OUT, true,
                     (uint8_t *) & udi_msc_cbw,
                     sizeof(udi_msc_cbw),
                     udi_msc_cbw_received)) {
         // OUT endpoint not available (halted), then wait a clear of halt.
         udd_ep_wait_stall_clear(UDI_MSC_EP_OUT, udi_msc_cbw_wait);
     }
 }
 
 
 void udi_msc_cbw_received(udd_ep_status_t status, iram_size_t nb_received)
 {
     // Check status of transfer
     if (UDD_EP_TRANSFER_OK != status) {
         // Tranfert aborted
         // Now wait MSC setup reset to relaunch CBW reception
         return;
     }
     // Check CBW integrity:
     // transfer status/CBW length/CBW signature
     if ((sizeof(udi_msc_cbw) != nb_received)
             || (udi_msc_cbw.dCBWSignature !=
                     CPU_TO_BE32(USB_CBW_SIGNATURE))) {
         // (5.2.1) Devices receiving a CBW with an invalid signature should stall
         // further traffic on the Bulk In pipe, and either stall further traffic
         // or accept and discard further traffic on the Bulk Out pipe, until
         // reset recovery.
         udi_msc_b_cbw_invalid = true;
         udi_msc_cbw_invalid();
         udi_msc_csw_invalid();
         return;
     }
     // Check LUN asked
     udi_msc_cbw.bCBWLUN &= USB_CBW_LUN_MASK;
     if (udi_msc_cbw.bCBWLUN > udi_msc_nb_lun) {
         // Bad LUN, then stop command process
         udi_msc_sense_fail_cdb_invalid();
         udi_msc_csw_process();
         return;
     }
     // Prepare CSW residue field with the size requested
     udi_msc_csw.dCSWDataResidue =
             le32_to_cpu(udi_msc_cbw.dCBWDataTransferLength);
 
     // Decode opcode
     switch (udi_msc_cbw.CDB[0]) {
     case SPC_REQUEST_SENSE:
         udi_msc_spc_requestsense();
         break;
 
     case SPC_INQUIRY:
         udi_msc_spc_inquiry();
         break;
 
     case SPC_MODE_SENSE6:
         udi_msc_spc_mode_sense(false);
         break;
     case SPC_MODE_SENSE10:
         udi_msc_spc_mode_sense(true);
         break;
 
     case SPC_TEST_UNIT_READY:
         udi_msc_spc_testunitready();
         break;
 
     case SBC_READ_CAPACITY10:
         udi_msc_sbc_read_capacity();
         break;
 
         // Optional but can not reply INVALID COMMAND because
         // this command is used by the Linux 2.4 kernel.
         // Otherwise the disk will not mount.
     case SBC_START_STOP_UNIT:
         // Accepts request to support plug/plug in case of card reader
     case SPC_PREVENT_ALLOW_MEDIUM_REMOVAL:
         // Accepts request to support full format from Windows
     case SBC_VERIFY10:
         udi_msc_sense_pass();
         udi_msc_csw_process();
         break;
 
     case SBC_READ10:
         udi_msc_sbc_trans(true);
         break;
 
     case SBC_WRITE10:
         udi_msc_sbc_trans(false);
         break;
 
     default:
         udi_msc_sense_command_invalid();
         udi_msc_csw_process();
         break;
     }
 }
 
 
 static bool udi_msc_cbw_validate(uint32_t alloc_len, uint8_t dir_flag)
 {
     /*
      * The following cases should result in a phase error:
      *  - Case  2: Hn < Di
      *  - Case  3: Hn < Do
      *  - Case  7: Hi < Di
      *  - Case  8: Hi <> Do
      *  - Case 10: Ho <> Di
      *  - Case 13: Ho < Do
      */
     if (((udi_msc_cbw.bmCBWFlags ^ dir_flag) & USB_CBW_DIRECTION_IN)
             || (udi_msc_csw.dCSWDataResidue < alloc_len)) {
         udi_msc_sense_fail_cdb_invalid();
         udi_msc_csw_process();
         return false;
     }
 
     /*
      * The following cases should result in a stall and nonzero
      * residue:
      *  - Case  4: Hi > Dn
      *  - Case  5: Hi > Di
      *  - Case  9: Ho > Dn
      *  - Case 11: Ho > Do
      */
     return true;
 }
 
 
 //---------------------------------------------
 //------- Routines to process small data packet
 
 static void udi_msc_data_send(uint8_t * buffer, uint8_t buf_size)
 {
     // Sends data on IN endpoint
     if (!udd_ep_run(UDI_MSC_EP_IN, true,
                     buffer, buf_size, udi_msc_data_sent)) {
         // If endpoint not available, then exit process command
         udi_msc_sense_fail_hardware();
         udi_msc_csw_process();
     }
 }
 
 
 void udi_msc_data_sent(udd_ep_status_t status, iram_size_t nb_sent)
 {
     if (UDD_EP_TRANSFER_OK != status) {
         // Error protocol
         // Now wait MSC setup reset to relaunch CBW reception
         return;
     }
     // Update sense data
     udi_msc_sense_pass();
     // Update CSW
     udi_msc_csw.dCSWDataResidue -= nb_sent;
     udi_msc_csw_process();
 }
 
 
 //---------------------------------------------
 //------- Routines to process CSW packet
 
 static void udi_msc_csw_process(void)
 {
     if (0 != udi_msc_csw.dCSWDataResidue) {
         // Residue not NULL
         // then STALL next request from USB host on corresponding endpoint
         if (udi_msc_cbw.bmCBWFlags & USB_CBW_DIRECTION_IN)
             udd_ep_set_halt(UDI_MSC_EP_IN);
         else
             udd_ep_set_halt(UDI_MSC_EP_OUT);
     }
     // Prepare and send CSW
     udi_msc_csw.dCSWTag = udi_msc_cbw.dCBWTag;
     udi_msc_csw.dCSWDataResidue = cpu_to_le32(udi_msc_csw.dCSWDataResidue);
     udi_msc_csw_send();
 }
 
 
 void udi_msc_csw_send(void)
 {
     // Sends CSW on IN endpoint
     if (!udd_ep_run(UDI_MSC_EP_IN, false,
                     (uint8_t *) & udi_msc_csw,
                     sizeof(udi_msc_csw),
                     udi_msc_csw_sent)) {
         // Endpoint not available
         // then restart CSW sent when endpoint IN STALL will be cleared
         udd_ep_wait_stall_clear(UDI_MSC_EP_IN, udi_msc_csw_send);
     }
 }
 
 
 void udi_msc_csw_sent(udd_ep_status_t status, iram_size_t nb_sent)
 {
     // CSW is sent or not
     // In all case, restart process and wait CBW
     udi_msc_cbw_wait();
 }
 
 
 //---------------------------------------------
 //------- Routines manage sense data
 
 static void udi_msc_clear_sense(void)
 {
     memset((uint8_t*)&udi_msc_sense, 0, sizeof(struct scsi_request_sense_data));
     udi_msc_sense.valid_reponse_code = SCSI_SENSE_VALID | SCSI_SENSE_CURRENT;
     udi_msc_sense.AddSenseLen = SCSI_SENSE_ADDL_LEN(sizeof(udi_msc_sense));
 }
 
 static void udi_msc_sense_fail(uint8_t sense_key, uint16_t add_sense,
         uint32_t lba)
 {
     udi_msc_clear_sense();
     udi_msc_csw.bCSWStatus = USB_CSW_STATUS_FAIL;
     udi_msc_sense.sense_flag_key = sense_key;
     udi_msc_sense.information[0] = lba >> 24;
     udi_msc_sense.information[1] = lba >> 16;
     udi_msc_sense.information[2] = lba >> 8;
     udi_msc_sense.information[3] = lba;
     udi_msc_sense.AddSenseCode = add_sense >> 8;
     udi_msc_sense.AddSnsCodeQlfr = add_sense;
 }
 
 static void udi_msc_sense_pass(void)
 {
     udi_msc_clear_sense();
     udi_msc_csw.bCSWStatus = USB_CSW_STATUS_PASS;
 }
 
 
 static void udi_msc_sense_fail_not_present(void)
 {
     udi_msc_sense_fail(SCSI_SK_NOT_READY, SCSI_ASC_MEDIUM_NOT_PRESENT, 0);
 }
 
 static void udi_msc_sense_fail_busy_or_change(void)
 {
     udi_msc_sense_fail(SCSI_SK_UNIT_ATTENTION,
             SCSI_ASC_NOT_READY_TO_READY_CHANGE, 0);
 }
 
 static void udi_msc_sense_fail_hardware(void)
 {
     udi_msc_sense_fail(SCSI_SK_HARDWARE_ERROR,
             SCSI_ASC_NO_ADDITIONAL_SENSE_INFO, 0);
 }
 
 static void udi_msc_sense_fail_protected(void)
 {
     udi_msc_sense_fail(SCSI_SK_DATA_PROTECT, SCSI_ASC_WRITE_PROTECTED, 0);
 }
 
 static void udi_msc_sense_fail_cdb_invalid(void)
 {
     udi_msc_sense_fail(SCSI_SK_ILLEGAL_REQUEST,
             SCSI_ASC_INVALID_FIELD_IN_CDB, 0);
 }
 
 static void udi_msc_sense_command_invalid(void)
 {
     udi_msc_sense_fail(SCSI_SK_ILLEGAL_REQUEST,
             SCSI_ASC_INVALID_COMMAND_OPERATION_CODE, 0);
 }
 
 
 //---------------------------------------------
 //------- Routines manage SCSI Commands
 
 static void udi_msc_spc_requestsense(void)
 {
     uint8_t length = udi_msc_cbw.CDB[4];
 
     // Can't send more than sense data length
     if (length > sizeof(udi_msc_sense))
         length = sizeof(udi_msc_sense);
 
     if (!udi_msc_cbw_validate(length, USB_CBW_DIRECTION_IN))
         return;
     // Send sense data
     udi_msc_data_send((uint8_t*)&udi_msc_sense, length);
 }
 
 
 static void udi_msc_spc_inquiry(void)
 {
     uint8_t length, i;
     UDC_DATA(4)
     // Constant inquiry data for all LUNs
     static struct scsi_inquiry_data udi_msc_inquiry_data = {
         .pq_pdt = SCSI_INQ_PQ_CONNECTED | SCSI_INQ_DT_DIR_ACCESS,
 #ifdef UDI_MSC_NOT_REMOVABLE
         .flags1 = 0,
 #else
         .flags1 = SCSI_INQ_RMB,
 #endif
         .version = SCSI_INQ_VER_SPC,
         .flags3 = SCSI_INQ_RSP_SPC2,
         .addl_len = SCSI_INQ_ADDL_LEN(sizeof(struct scsi_inquiry_data)),
         .vendor_id = {UDI_MSC_GLOBAL_VENDOR_ID},
         .product_rev = {UDI_MSC_GLOBAL_PRODUCT_VERSION},
     };
 
     length = udi_msc_cbw.CDB[4];
 
     // Can't send more than inquiry data length
     if (length > sizeof(udi_msc_inquiry_data))
         length = sizeof(udi_msc_inquiry_data);
 
     if (!udi_msc_cbw_validate(length, USB_CBW_DIRECTION_IN))
         return;
     if ((0 != (udi_msc_cbw.CDB[1] & (SCSI_INQ_REQ_EVPD | SCSI_INQ_REQ_CMDT)))
             || (0 != udi_msc_cbw.CDB[2])) {
         // CMDT and EPVD bits are not at 0
         // PAGE or OPERATION CODE fields are not empty
         //  = No standard inquiry asked
         udi_msc_sense_fail_cdb_invalid();   // Command is unsupported
         udi_msc_csw_process();
         return;
     }
     //* Fill product ID field
     // Copy name in product id field
     memcpy(udi_msc_inquiry_data.product_id,
             mem_name(udi_msc_cbw.bCBWLUN),
             sizeof(udi_msc_inquiry_data.product_id));
     // Search end of name '/0'
     i = 0;
     while (sizeof(udi_msc_inquiry_data.product_id) != i) {
         if (0 == udi_msc_inquiry_data.product_id[i])
             break;
         i++;
     }
     // Padding with space char
     while (sizeof(udi_msc_inquiry_data.product_id) != i) {
         udi_msc_inquiry_data.product_id[i] = ' ';
         i++;
     }
 
     // Send inquiry data
     udi_msc_data_send((uint8_t *) & udi_msc_inquiry_data, length);
 }
 
 
 static bool udi_msc_spc_testunitready_global(void)
 {
     switch (mem_test_unit_ready(udi_msc_cbw.bCBWLUN)) {
     case CTRL_GOOD:
         return true;    // Don't change sense data
     case CTRL_BUSY:
         udi_msc_sense_fail_busy_or_change();
         break;
     case CTRL_NO_PRESENT:
         udi_msc_sense_fail_not_present();
         break;
     case CTRL_FAIL:
     default:
         udi_msc_sense_fail_hardware();
         break;
     }
     return false;
 }
 
 
 static void udi_msc_spc_testunitready(void)
 {
     if (udi_msc_spc_testunitready_global()) {
         // LUN ready, then update sense data with status pass
         udi_msc_sense_pass();
     }
     // Send status in CSW packet
     udi_msc_csw_process();
 }
 
 
 static void udi_msc_spc_mode_sense(bool b_sense10)
 {
     // Union of all mode sense structures
     union sense_6_10 {
         struct {
             struct scsi_mode_param_header6 header;
             struct spc_control_page_info_execpt sense_data;
         } s6;
         struct {
             struct scsi_mode_param_header10 header;
             struct spc_control_page_info_execpt sense_data;
         } s10;
     };
 
     uint8_t data_sense_lgt;
     uint8_t mode;
     uint8_t request_lgt;
     uint8_t wp;
     struct spc_control_page_info_execpt *ptr_mode;
     UDC_BSS(4)  static union sense_6_10 sense;
 
     // Clear all fields
     memset(&sense, 0, sizeof(sense));
 
     // Initialize process
     if (b_sense10) {
         request_lgt = udi_msc_cbw.CDB[8];
         ptr_mode = &sense.s10.sense_data;
         data_sense_lgt = sizeof(struct scsi_mode_param_header10);
     } else {
         request_lgt = udi_msc_cbw.CDB[4];
         ptr_mode = &sense.s6.sense_data;
         data_sense_lgt = sizeof(struct scsi_mode_param_header6);
     }
 
     // No Block descriptor
 
     // Fill page(s)
     mode = udi_msc_cbw.CDB[2] & SCSI_MS_MODE_ALL;
     if ((SCSI_MS_MODE_INFEXP == mode)
             || (SCSI_MS_MODE_ALL == mode)) {
         // Informational exceptions control page (from SPC)
         ptr_mode->page_code =
                 SCSI_MS_MODE_INFEXP;
         ptr_mode->page_length =
                 SPC_MP_INFEXP_PAGE_LENGTH;
         ptr_mode->mrie =
                 SPC_MP_INFEXP_MRIE_NO_SENSE;
         data_sense_lgt += sizeof(struct spc_control_page_info_execpt);
     }
     // Can't send more than mode sense data length
     if (request_lgt > data_sense_lgt)
         request_lgt = data_sense_lgt;
     if (!udi_msc_cbw_validate(request_lgt, USB_CBW_DIRECTION_IN))
         return;
 
     // Fill mode parameter header length
     wp = (mem_wr_protect(udi_msc_cbw.bCBWLUN)) ? SCSI_MS_SBC_WP : 0;
 
     if (b_sense10) {
         sense.s10.header.mode_data_length =
                 cpu_to_be16((data_sense_lgt - 2));
         //sense.s10.header.medium_type                 = 0;
         sense.s10.header.device_specific_parameter = wp;
         //sense.s10.header.block_descriptor_length     = 0;
     } else {
         sense.s6.header.mode_data_length = data_sense_lgt - 1;
         //sense.s6.header.medium_type                  = 0;
         sense.s6.header.device_specific_parameter = wp;
         //sense.s6.header.block_descriptor_length      = 0;
     }
 
     // Send mode sense data
     udi_msc_data_send((uint8_t *) & sense, request_lgt);
 }
 
 
 static void udi_msc_sbc_read_capacity(void)
 {
     UDC_BSS(4) static struct sbc_read_capacity10_data udi_msc_capacity;
 
     if (!udi_msc_cbw_validate(sizeof(udi_msc_capacity),
                     USB_CBW_DIRECTION_IN))
         return;
 
     // Get capacity of LUN
     switch (mem_read_capacity(udi_msc_cbw.bCBWLUN,
                     &udi_msc_capacity.max_lba)) {
     case CTRL_GOOD:
         break;
     case CTRL_BUSY:
         udi_msc_sense_fail_busy_or_change();
         udi_msc_csw_process();
         return;
     case CTRL_NO_PRESENT:
         udi_msc_sense_fail_not_present();
         udi_msc_csw_process();
         return;
     default:
         udi_msc_sense_fail_hardware();
         udi_msc_csw_process();
         return;
     }
 
     // Format capacity data
     udi_msc_capacity.block_len = CPU_TO_BE32(UDI_MSC_BLOCK_SIZE);
     udi_msc_capacity.max_lba = cpu_to_be32(udi_msc_capacity.max_lba);
     // Send the corresponding sense data
     udi_msc_data_send((uint8_t *) & udi_msc_capacity,
             sizeof(udi_msc_capacity));
 }
 
 
 static void udi_msc_sbc_trans(bool b_read)
 {
     uint32_t trans_size;
 
     if (!b_read) {
         // Write operation then check Write Protect
         if (mem_wr_protect(udi_msc_cbw.bCBWLUN)) {
             // Write not authorized
             udi_msc_sense_fail_protected();
             udi_msc_csw_process();
             return;
         }
     }
     // Read/Write command fields (address and number of block)
     MSB0(udi_msc_addr) = udi_msc_cbw.CDB[2];
     MSB1(udi_msc_addr) = udi_msc_cbw.CDB[3];
     MSB2(udi_msc_addr) = udi_msc_cbw.CDB[4];
     MSB3(udi_msc_addr) = udi_msc_cbw.CDB[5];
     MSB(udi_msc_nb_block) = udi_msc_cbw.CDB[7];
     LSB(udi_msc_nb_block) = udi_msc_cbw.CDB[8];
 
     // Compute number of byte to transfer and valid it
     trans_size = (uint32_t) udi_msc_nb_block *UDI_MSC_BLOCK_SIZE;
     if (!udi_msc_cbw_validate(trans_size,
                     (b_read) ? USB_CBW_DIRECTION_IN :
                     USB_CBW_DIRECTION_OUT))
         return;
 
     // Record transfer request to do it in main loop and not under interrupt
     udi_msc_b_read = b_read;
     udi_msc_b_trans_req = true;
 }
 
 
 bool udi_msc_process_trans(void)
 {
     Ctrl_status status;
 
     if (!udi_msc_b_trans_req)
         return false;   // No Transfer request to do
     udi_msc_b_trans_req = false;
 
     // Start transfer
     if (udi_msc_b_read) {
         status = memory_2_usb(udi_msc_cbw.bCBWLUN, udi_msc_addr,
                 udi_msc_nb_block);
     } else {
         status = usb_2_memory(udi_msc_cbw.bCBWLUN, udi_msc_addr,
                 udi_msc_nb_block);
     }
 
     // Check status of transfer
     switch (status) {
     case CTRL_GOOD:
         udi_msc_sense_pass();
         break;
     case CTRL_BUSY:
         udi_msc_sense_fail_busy_or_change();
         break;
     case CTRL_NO_PRESENT:
         udi_msc_sense_fail_not_present();
         break;
     default:
     case CTRL_FAIL:
         udi_msc_sense_fail_hardware();
         break;
     }
     // Send status of transfer in CSW packet
     udi_msc_csw_process();
     return true;
 }
 
 
 static void udi_msc_trans_ack(udd_ep_status_t status, iram_size_t n)
 {
     // Update variable to signal the end of transfer
     udi_msc_b_abort_trans = (UDD_EP_TRANSFER_OK != status) ? true : false;
     udi_msc_b_ack_trans = true;
 }
 
 
 bool udi_msc_trans_block(bool b_read, uint8_t * block, iram_size_t block_size,
         void (*callback) (udd_ep_status_t status, iram_size_t n))
 {
     if (!udi_msc_b_ack_trans)
         return false;   // No possible, transfer on going
 
     // Start transfer Internal RAM<->USB line
     udi_msc_b_ack_trans = false;
     if (!udd_ep_run((b_read) ? UDI_MSC_EP_IN : UDI_MSC_EP_OUT,
                     false,
                     block,
                     block_size,
                     (NULL == callback) ? udi_msc_trans_ack :
                     callback)) {
         udi_msc_b_ack_trans = true;
         return false;
     }
     if (NULL == callback) {
         while (!udi_msc_b_ack_trans);
         if (udi_msc_b_abort_trans) {
             return false;
         }
         udi_msc_csw.dCSWDataResidue -= block_size;
         return (!udi_msc_b_abort_trans);
     }
     udi_msc_csw.dCSWDataResidue -= block_size;
     return true;
 }