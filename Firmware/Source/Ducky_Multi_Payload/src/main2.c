//_____  M A I N ___________________________________________________________
//
// Module		: RubberDucky
// Description	: Simple USB HID Keyboard injection
// Date			: February 3, 2012
// Credit		: Mostly borrowed from ATMEL's example code
//__________________________________________________________________________

//_____  I N C L U D E S ___________________________________________________
#include <string.h>
#include "compiler.h"
#include "main.h"
#include "preprocessor.h"
#include "board.h"
#include "print_funcs.h"
#include "ctrl_access.h"
#include "power_clocks_lib.h"
#include "gpio.h"
#include "usart.h"
#include "spi.h"
#include "conf_sd_mmc_spi.h"
#include "fat.h"
#include "file.h"
#include "navigation.h"
#include "conf_usb.h"
#include "udc.h"
#include "udd.h"
#include "led.h"
#include "udi_hid_kbd.h"
#include "sysclk.h"
#include "sleepmgr.h"

//_____ M A C R O S ________________________________________________________
// shell USART Configuration
#define SHL_USART               (&AVR32_USART1)
#define SHL_USART_RX_PIN        AVR32_USART1_RXD_0_0_PIN
#define SHL_USART_RX_FUNCTION   AVR32_USART1_RXD_0_0_FUNCTION
#define SHL_USART_TX_PIN        AVR32_USART1_TXD_0_0_PIN
#define SHL_USART_TX_FUNCTION   AVR32_USART1_TXD_0_0_FUNCTION
#define SHL_USART_BAUDRATE      57600


//_____ D E C L A R A T I O N S ____________________________________________
// init status var
//static bool main_b_kbd_enable = false;

// filename
const char *injectFile = "A:\\inject.bin";

// state machine enum
typedef enum injectState {
	state_IDLE,
	state_START_INJECT,
	state_INJECTING,
	state_KEY_DOWN,
	state_KEY_UP,
	state_MOD_DOWN,
	state_MOD_KEY_DOWN,
	state_MOD_KEY_UP,
	state_MOD_UP,
	state_WAIT
} injectState_t;


//_____ F U N C T I O N S __________________________________________________

// initializes the SD/MMC memory resources: GPIO, SPI and MMC
//-------------------------------------------------------------------
static void sd_mmc_resources_init(long pba_hz) {
  
	// GPIO pins used for SD/MMC interface
	static const gpio_map_t SD_MMC_SPI_GPIO_MAP = {
		{SD_MMC_SPI_SCK_PIN,  SD_MMC_SPI_SCK_FUNCTION },  // SPI Clock.
		{SD_MMC_SPI_MISO_PIN, SD_MMC_SPI_MISO_FUNCTION},  // MISO.
		{SD_MMC_SPI_MOSI_PIN, SD_MMC_SPI_MOSI_FUNCTION},  // MOSI.
		{SD_MMC_SPI_NPCS_PIN, SD_MMC_SPI_NPCS_FUNCTION}   // Chip Select NPCS.
	};

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

	// assign I/Os to SPI.
	gpio_enable_module(SD_MMC_SPI_GPIO_MAP,
						sizeof(SD_MMC_SPI_GPIO_MAP) / sizeof(SD_MMC_SPI_GPIO_MAP[0]));

	// initialize as master.
	spi_initMaster(SD_MMC_SPI, &spiOptions);

	// set SPI selection mode: variable_ps, pcs_decode, delay.
	spi_selectionMode(SD_MMC_SPI, 0, 0, 0);

	// enable SPI module.
	spi_enable(SD_MMC_SPI);

	// Initialize SD/MMC driver with SPI clock (PBA).
	sd_mmc_spi_init(spiOptions, pba_hz);
}

// process a USB frame
//-------------------------------------------------------------------
void process_frame(uint16_t framenumber)
{
	static uint8_t cpt_sof = 0;
	static injectState_t state = state_START_INJECT;
	static uint8_t wait = 0;
	static uint16_t debounce = 0;
	static uint16_t injectToken = 0x0000;
	
	// scan process running each 2ms
	cpt_sof++;
	if( 2 > cpt_sof )
		return;
	cpt_sof = 0;	
	
	// pulse led
	LED_Set_Intensity( LED0, framenumber >> 1 );	
	
	// debounce switch
	if( debounce > 0 ) --debounce;
		
	// injection state machine
	switch(state) {

		case state_IDLE:
			// check switch
			if( gpio_get_pin_value(GPIO_JOYSTICK_PUSH) == GPIO_JOYSTICK_PUSH_PRESSED ) {
	
				// debounce
				if( debounce == 0 ) {
					state = state_START_INJECT;
					debounce = 250;
				}			
			}		
			break;		
			
		case state_START_INJECT:
			file_open(FOPEN_MODE_R);		
			state = state_INJECTING;
			break;
			
		case state_INJECTING:				
			
			if( file_eof() ) {
				file_close();	
				state = state_IDLE;
				break;
			}
			
			injectToken = ( file_getc() | ( file_getc() << 8 ) );			
						
			if( ( injectToken&0xff ) == 0x00 ) {				
				wait = injectToken>>8;
				state = state_WAIT;
			}
			else if( ( injectToken>>8 ) == 0x00 ) {
				state = state_KEY_DOWN;
			}				
			else {
				state = state_MOD_DOWN;					
			}					
			break;
			
		case state_KEY_DOWN:
			udi_hid_kbd_down(injectToken&0xff);
			state = state_KEY_UP;
			break;

		case state_KEY_UP:
			udi_hid_kbd_up(injectToken&0xff);
			state = state_INJECTING;
			break;			
			
		case state_MOD_DOWN:
			udi_hid_kbd_modifier_down(injectToken>>8);
			state = state_MOD_KEY_DOWN;
			break;

		case state_MOD_KEY_DOWN:
			udi_hid_kbd_down(injectToken&0xff);
			state = state_MOD_KEY_UP;
			break;

		case state_MOD_KEY_UP:
			udi_hid_kbd_up(injectToken&0xff);
			state = state_MOD_UP;		
			break;
			
		case state_MOD_UP:
			udi_hid_kbd_modifier_up(injectToken>>8);
			state = state_INJECTING;
			break;	
			
		case state_WAIT:
			if( --wait == 0 ) {
				state = state_INJECTING;
			}
			break;
			
		default:
			state = state_IDLE;
	}
}

// main
//-------------------------------------------------------------------
int main(void) {
	
	uint32_t sizeTemp;
	
	// init cpu
	irq_initialize_vectors();
	cpu_irq_enable();

	// init board
	sleepmgr_init();
	sysclk_init();
	board_init();

	// initialize SD/MMC resources: GPIO, SPI.
	sd_mmc_resources_init(FOSC0);
	
	// test if the memory is ready - using the control access memory abstraction layer (/SERVICES/MEMORY/CTRL_ACCESS/)
	if (mem_test_unit_ready(LUN_ID_SD_MMC_SPI_MEM) == CTRL_GOOD) {
		// Get and display the capacity
		mem_read_capacity(LUN_ID_SD_MMC_SPI_MEM, &sizeTemp);
	}
	else {
		//  error - we can't proceed - sit and spin...
		while(true) { LED_On( LED1 ); }
	}
		
	// Start USB stack
	udc_start();
	udc_attach();
	
	while(true) {
		//sleepmgr_enter_sleep();
	}
}

//-------------------------------------------------------------------
void main_suspend_action(void)
{
	LED_Off(LED0);
	LED_Off(LED1);
}

//-------------------------------------------------------------------
void main_resume_action(void)
{
}
 
//-------------------------------------------------------------------
void main_sof_action(void)
{
	if( main_b_kbd_enable )	{
		process_frame( udd_get_frame_number() );
	}	
}

//-------------------------------------------------------------------
// If remote wakeup enable/disable is supported insert code below
void main_remotewakeup_enable(void)
{
}

//-------------------------------------------------------------------
void main_remotewakeup_disable(void)
{
}

//-------------------------------------------------------------------
bool main_kbd_enable(void)
{
	//main_b_kbd_enable = true;
	return true;
}

//-------------------------------------------------------------------
void main_kbd_disable(void)
{
	//main_b_kbd_enable = false; mod 
	return false;
}

//-------------------------------------------------------------------
void main_kbd_change(uint8_t value) 
{
	//old code 2 lines
	// we use the setreport as the trigger to start the launch
	//main_b_kbd_enable = true;
	
	//this is called when LEDs CAPS LCK, NUM LCK change
	if (value & HID_LED_NUM_LOCK) {
	// Here, turn on Num LED
	} else{
	// Here, turn off Num LED
	}
	if (value & HID_LED_CAPS_LOCK) {
	// Here, turn on Caps LED
	} else {
	// Here, turn off Caps LED
	}
}