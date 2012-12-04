/*****************************************************************************
 *
 * \file
 *
 * \brief GPIO software driver interface for AVR UC3.
 *
 * Copyright (c) 2010-2011 Atmel Corporation. All rights reserved.
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
 *****************************************************************************/


#include "gpio.h"

//! GPIO module instance.
#define GPIO  AVR32_GPIO


/*! \name Peripheral Bus Interface
 */
//! @{


int gpio_enable_module(const gpio_map_t gpiomap, uint32_t size)
{
  int status = GPIO_SUCCESS;
  uint32_t i;

  for (i = 0; i < size; i++)
  {
    status |= gpio_enable_module_pin(gpiomap->pin, gpiomap->function);
    gpiomap++;
  }

  return status;
}


int gpio_enable_module_pin(uint32_t pin, uint32_t function)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];

  // Enable the correct function.
  switch (function)
  {
  case 0: // A function.
    gpio_port->pmr0c = 1 << (pin & 0x1F);
    gpio_port->pmr1c = 1 << (pin & 0x1F);
#if (AVR32_GPIO_H_VERSION >= 210)
    gpio_port->pmr2c = 1 << (pin & 0x1F);
#endif
    break;

  case 1: // B function.
    gpio_port->pmr0s = 1 << (pin & 0x1F);
    gpio_port->pmr1c = 1 << (pin & 0x1F);
#if (AVR32_GPIO_H_VERSION >= 210)
    gpio_port->pmr2c = 1 << (pin & 0x1F);
#endif
    break;

  case 2: // C function.
    gpio_port->pmr0c = 1 << (pin & 0x1F);
    gpio_port->pmr1s = 1 << (pin & 0x1F);
#if (AVR32_GPIO_H_VERSION >= 210)
    gpio_port->pmr2c = 1 << (pin & 0x1F);
#endif
    break;

  case 3: // D function.
    gpio_port->pmr0s = 1 << (pin & 0x1F);
    gpio_port->pmr1s = 1 << (pin & 0x1F);
#if (AVR32_GPIO_H_VERSION >= 210)
    gpio_port->pmr2c = 1 << (pin & 0x1F);
#endif
    break;

#if (AVR32_GPIO_H_VERSION >= 210)
  case 4: // E function.
    gpio_port->pmr0c = 1 << (pin & 0x1F);
    gpio_port->pmr1c = 1 << (pin & 0x1F);
    gpio_port->pmr2s = 1 << (pin & 0x1F);
    break;

  case 5: // F function.
    gpio_port->pmr0s = 1 << (pin & 0x1F);
    gpio_port->pmr1c = 1 << (pin & 0x1F);
    gpio_port->pmr2s = 1 << (pin & 0x1F);
    break;

  case 6: // G function.
    gpio_port->pmr0c = 1 << (pin & 0x1F);
    gpio_port->pmr1s = 1 << (pin & 0x1F);
    gpio_port->pmr2s = 1 << (pin & 0x1F);
    break;

  case 7: // H function.
    gpio_port->pmr0s = 1 << (pin & 0x1F);
    gpio_port->pmr1s = 1 << (pin & 0x1F);
    gpio_port->pmr2s = 1 << (pin & 0x1F);
    break;
#endif

  default:
    return GPIO_INVALID_ARGUMENT;
  }

  // Disable GPIO control.
  gpio_port->gperc = 1 << (pin & 0x1F);

  return GPIO_SUCCESS;
}


void gpio_enable_gpio(const gpio_map_t gpiomap, uint32_t size)
{
  uint32_t i;

  for (i = 0; i < size; i++)
  {
    gpio_enable_gpio_pin(gpiomap->pin);
    gpiomap++;
  }
}


void gpio_enable_gpio_pin(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->oderc = 1 << (pin & 0x1F);
  gpio_port->gpers = 1 << (pin & 0x1F);
}


// The open-drain mode is not synthesized on the current AVR32 products.
// If one day some AVR32 products have this feature, the corresponding part
// numbers should be listed in the #if below.
// Note that other functions are available in this driver to use pins with open
// drain in GPIO mode. The advantage of the open-drain mode functions over these
// other functions is that they can be used not only in GPIO mode but also in
// module mode.
#if 0


void gpio_enable_pin_open_drain(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->odmers = 1 << (pin & 0x1F);
}


void gpio_disable_pin_open_drain(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->odmerc = 1 << (pin & 0x1F);
}


#endif


void gpio_enable_pin_pull_up(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->puers = 1 << (pin & 0x1F);
#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) || defined(AVR32_GPIO_212_H_INCLUDED)
  gpio_port->pderc = 1 << (pin & 0x1F);
#endif
}


void gpio_disable_pin_pull_up(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->puerc = 1 << (pin & 0x1F);
}

#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) || defined(AVR32_GPIO_212_H_INCLUDED)
// Added support of Pull-up Resistor, Pull-down Resistor and Buskeeper Control.

/*! \brief Enables the pull-down resistor of a pin.
 *
 * \param pin The pin number.
 */
void gpio_enable_pin_pull_down(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->puerc = 1 << (pin & 0x1F);
  gpio_port->pders = 1 << (pin & 0x1F);
}

/*! \brief Disables the pull-down resistor of a pin.
 *
 * \param pin The pin number.
 */
void gpio_disable_pin_pull_down(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->pderc = 1 << (pin & 0x1F);
}

/*! \brief Enables the buskeeper functionality on a pin.
 *
 * \param pin The pin number.
 */
void gpio_enable_pin_buskeeper(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->puers = 1 << (pin & 0x1F);
  gpio_port->pders = 1 << (pin & 0x1F);
}

/*! \brief Disables the buskeeper functionality on a pin.
 *
 * \param pin The pin number.
 */
void gpio_disable_pin_buskeeper(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->puerc = 1 << (pin & 0x1F);
  gpio_port->pderc = 1 << (pin & 0x1F);
}

#endif

void gpio_configure_pin(uint32_t pin, uint32_t flags)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];

  /* Both pull-up and pull-down set means buskeeper */
#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) || defined(AVR32_GPIO_212_H_INCLUDED)
    if (flags & GPIO_PULL_DOWN)
            gpio_port->pders = 1 << (pin & 0x1F);
    else
            gpio_port->pderc = 1 << (pin & 0x1F);
#endif
    if (flags & GPIO_PULL_UP)
            gpio_port->puers = 1 << (pin & 0x1F);
    else
            gpio_port->puerc = 1 << (pin & 0x1F);

    /* Enable open-drain mode if requested */
#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) || defined(AVR32_GPIO_212_H_INCLUDED)
            if (flags & GPIO_OPEN_DRAIN)
                    gpio_port->odmers = 1 << (pin & 0x1F);
            else
                    gpio_port->odmerc = 1 << (pin & 0x1F);

            if (flags & GPIO_OPEN_DRAIN)
                    gpio_port->pders = 1 << (pin & 0x1F);
            else
                    gpio_port->pderc = 1 << (pin & 0x1F);
#endif

#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) || defined(AVR32_GPIO_212_H_INCLUDED)
            /* Select drive strength */
            if (flags & GPIO_DRIVE_LOW)
                    gpio_port->odcr0s = 1 << (pin & 0x1F);
            else
                    gpio_port->odcr0c = 1 << (pin & 0x1F);
            if (flags & GPIO_DRIVE_HIGH)
                    gpio_port->odcr1s = 1 << (pin & 0x1F);
            else
                    gpio_port->odcr1c = 1 << (pin & 0x1F);
#endif

    /* Select interrupt level for group */
    if (flags & GPIO_INTERRUPT) {
            if (flags & GPIO_BOTHEDGES)
            {
                   gpio_port->imr0c = 1 << (pin & 0x1F);
                   gpio_port->imr1c = 1 << (pin & 0x1F);
            }
            else if (flags & GPIO_RISING)
            {
                   gpio_port->imr0s = 1 << (pin & 0x1F);
                   gpio_port->imr1c = 1 << (pin & 0x1F);
            }
            else if (flags & GPIO_FALLING)
            {
                   gpio_port->imr0c = 1 << (pin & 0x1F);
                   gpio_port->imr1s = 1 << (pin & 0x1F);
            }
    }

    /* Select direction and initial pin state */
    if (flags & GPIO_DIR_OUTPUT) {
            if (flags & GPIO_INIT_HIGH)
                    gpio_port->ovrs = 1 << (pin & 0x1F);
            else
                    gpio_port->ovrc = 1 << (pin & 0x1F);
            gpio_port->oders = 1 << (pin & 0x1F);
    } else {
            gpio_port->oderc = 1 << (pin & 0x1F);
    }

    /* Enable GPIO */
    gpio_port->gpers = 1 << (pin & 0x1F);
}

void gpio_configure_group(uint32_t port, uint32_t mask, uint32_t flags)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[port];

  /* Both pull-up and pull-down set means buskeeper */
#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) || defined(AVR32_GPIO_212_H_INCLUDED)
    if (flags & GPIO_PULL_DOWN)
            gpio_port->pders = mask;
    else
            gpio_port->pderc = mask;
#endif
    if (flags & GPIO_PULL_UP)
            gpio_port->puers = mask;
    else
            gpio_port->puerc = mask;

    /* Enable open-drain mode if requested */
#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) || defined(AVR32_GPIO_212_H_INCLUDED)
            if (flags & GPIO_OPEN_DRAIN)
                    gpio_port->odmers = mask;
            else
                    gpio_port->odmerc = mask;

            if (flags & GPIO_OPEN_DRAIN)
                    gpio_port->pders = mask;
            else
                    gpio_port->pderc = mask;
#endif

#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) || defined(AVR32_GPIO_212_H_INCLUDED)
            /* Select drive strength */
            if (flags & GPIO_DRIVE_LOW)
                    gpio_port->odcr0s = mask;
            else
                    gpio_port->odcr0c = mask;
            if (flags & GPIO_DRIVE_HIGH)
                    gpio_port->odcr1s = mask;
            else
                    gpio_port->odcr1c = mask;
#endif

    /* Select interrupt level for group */
    if (flags & GPIO_INTERRUPT) {
            if (flags & GPIO_BOTHEDGES)
            {
                   gpio_port->imr0c = mask;
                   gpio_port->imr1c = mask;
            }
            else if (flags & GPIO_RISING)
            {
                   gpio_port->imr0s = mask;
                   gpio_port->imr1c = mask;
            }
            else if (flags & GPIO_FALLING)
            {
                   gpio_port->imr0c = mask;
                   gpio_port->imr1s = mask;
            }
    }

    /* Select direction and initial pin state */
    if (flags & GPIO_DIR_OUTPUT) {
            if (flags & GPIO_INIT_HIGH)
                    gpio_port->ovrs = mask;
            else
                    gpio_port->ovrc = mask;
            gpio_port->oders = mask;
    } else {
            gpio_port->oderc = mask;
    }

    /* Enable GPIO */
    gpio_port->gpers = mask;
}

int gpio_get_pin_value(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  return (gpio_port->pvr >> (pin & 0x1F)) & 1;
}


int gpio_get_gpio_pin_output_value(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  return (gpio_port->ovr >> (pin & 0x1F)) & 1;
}


int gpio_get_gpio_open_drain_pin_output_value(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  return ((gpio_port->oder >> (pin & 0x1F)) & 1) ^ 1;
}


void gpio_set_gpio_pin(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->ovrs  = 1 << (pin & 0x1F); // Value to be driven on the I/O line: 1.
  gpio_port->oders = 1 << (pin & 0x1F); // The GPIO output driver is enabled for that pin.
  gpio_port->gpers = 1 << (pin & 0x1F); // The GPIO module controls that pin.
}

void gpio_set_pin_high(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->ovrs  = 1 << (pin & 0x1F); // Value to be driven on the I/O line: 1.
}

void gpio_set_group_high(uint32_t port, uint32_t mask)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[port];
  gpio_port->ovrs  = mask; // Value to be driven on the I/O group: 1.
}


void gpio_set_pin_low(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->ovrc  = 1 << (pin & 0x1F); // Value to be driven on the I/O line: 0.
}

void gpio_clr_gpio_pin(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->ovrc  = 1 << (pin & 0x1F); // Value to be driven on the I/O line: 0.
  gpio_port->oders = 1 << (pin & 0x1F); // The GPIO output driver is enabled for that pin.
  gpio_port->gpers = 1 << (pin & 0x1F); // The GPIO module controls that pin.
}

void gpio_set_group_low(uint32_t port, uint32_t mask)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[port];
  gpio_port->ovrc  = mask; // Value to be driven on the I/O group: 0.
}

void gpio_tgl_gpio_pin(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->ovrt  = 1 << (pin & 0x1F); // Toggle the I/O line.
  gpio_port->oders = 1 << (pin & 0x1F); // The GPIO output driver is enabled for that pin.
  gpio_port->gpers = 1 << (pin & 0x1F); // The GPIO module controls that pin.
}

void gpio_toggle_pin(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->ovrt  = 1 << (pin & 0x1F); // Toggle the I/O line.
}

void gpio_toggle_group(uint32_t port, uint32_t mask)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[port];
  gpio_port->ovrt  = mask; // Toggle the I/O port.
}

void gpio_set_gpio_open_drain_pin(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];

  gpio_port->oderc = 1 << (pin & 0x1F); // The GPIO output driver is disabled for that pin.
  gpio_port->gpers = 1 << (pin & 0x1F); // The GPIO module controls that pin.
}


void gpio_clr_gpio_open_drain_pin(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];

  gpio_port->ovrc  = 1 << (pin & 0x1F); // Value to be driven on the I/O line: 0.
  gpio_port->oders = 1 << (pin & 0x1F); // The GPIO output driver is enabled for that pin.
  gpio_port->gpers = 1 << (pin & 0x1F); // The GPIO module controls that pin.
}


void gpio_tgl_gpio_open_drain_pin(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];

  gpio_port->ovrc  = 1 << (pin & 0x1F); // Value to be driven on the I/O line if the GPIO output driver is enabled: 0.
  gpio_port->odert = 1 << (pin & 0x1F); // The GPIO output driver is toggled for that pin.
  gpio_port->gpers = 1 << (pin & 0x1F); // The GPIO module controls that pin.
}


void gpio_enable_pin_glitch_filter(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->gfers = 1 << (pin & 0x1F);
}


void gpio_disable_pin_glitch_filter(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->gferc = 1 << (pin & 0x1F);
}

/*! \brief Configure the edge detector of an input pin
 *
 * \param pin The pin number.
 * \param mode The edge detection mode (\ref GPIO_PIN_CHANGE, \ref GPIO_RISING_EDGE
 *             or \ref GPIO_FALLING_EDGE).
 *
 * \return \ref GPIO_SUCCESS or \ref GPIO_INVALID_ARGUMENT.
 */
static int gpio_configure_edge_detector(uint32_t pin, uint32_t mode)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];

  // Configure the edge detector.
  switch (mode)
  {
  case GPIO_PIN_CHANGE:
    gpio_port->imr0c = 1 << (pin & 0x1F);
    gpio_port->imr1c = 1 << (pin & 0x1F);
    break;

  case GPIO_RISING_EDGE:
    gpio_port->imr0s = 1 << (pin & 0x1F);
    gpio_port->imr1c = 1 << (pin & 0x1F);
    break;

  case GPIO_FALLING_EDGE:
    gpio_port->imr0c = 1 << (pin & 0x1F);
    gpio_port->imr1s = 1 << (pin & 0x1F);
    break;

  default:
    return GPIO_INVALID_ARGUMENT;
  }

  return GPIO_SUCCESS;
}


int gpio_enable_pin_interrupt(uint32_t pin, uint32_t mode)
{
  volatile avr32_gpio_port_t  *gpio_port = &GPIO.port[pin >> 5];

  // Enable the glitch filter.
  gpio_port->gfers = 1 << (pin & 0x1F);

  // Configure the edge detector.
  if(GPIO_INVALID_ARGUMENT == gpio_configure_edge_detector(pin, mode))
    return(GPIO_INVALID_ARGUMENT);

  // Enable interrupt.
  gpio_port->iers = 1 << (pin & 0x1F);

  return GPIO_SUCCESS;
}


void gpio_disable_pin_interrupt(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  gpio_port->ierc = 1 << (pin & 0x1F);
}


int gpio_get_pin_interrupt_flag(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];
  return (gpio_port->ifr >> (pin & 0x1F)) & 1;
}


void gpio_clear_pin_interrupt_flag(uint32_t pin)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];

#if (AVR32_GPIO_H_VERSION == 211)
  //GPIO erratum - Writing a one to the GPIO.IFRC register
  //to clear an interrupt will be ignored if interrupt is enabled for the
  //corresponding port.
  //Work around for the erratum - Disable the interrupt, clear it by writing
  //a one to GPIO.IFRC, then enable the interrupt.

  // Save interrupt enable register.
  uint32_t const gpio_ier = gpio_port->ier;

  // Disable interrupt.
  gpio_port->ierc = gpio_ier;

  // Clear pin interrupt.
  gpio_port->ifrc = 1 << (pin & 0x1F);

  // Restore interrupt enable register.
  gpio_port->ier = gpio_ier;
#else
  gpio_port->ifrc = 1 << (pin & 0x1F);
#endif
}


//#
//# Peripheral Event System Support.
//#
#if UC3L
int gpio_configure_pin_periph_event_mode(uint32_t pin, uint32_t mode, uint32_t use_igf)
{
  volatile avr32_gpio_port_t *gpio_port = &GPIO.port[pin >> 5];

  if(true == use_igf)
  {
    // Enable the glitch filter.
    gpio_port->gfers = 1 << (pin & 0x1F);
  }
  else
  {
    // Disable the glitch filter.
    gpio_port->gferc = 1 << (pin & 0x1F);
  }

  // Configure the edge detector.
  return(gpio_configure_edge_detector(pin, mode));
}

#endif

//! @}
