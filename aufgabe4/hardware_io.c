/** ****************************************************************
 * @file    aufgabe4/hardware_io.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    06.11.2016
 * @brief   Implementation of the Hardware IO module
 ******************************************************************
 */
#include <stdbool.h>
#include "TI_Lib.h"
#include "errors.h"
#include "hardware_io.h"

#define PORT GPIOG

/**
 * Creates a mask for a pin, assuming 1 bit per pin.
 */
#define MASK_ONE_BIT_PIN(i)    (0x01U << (i))

// Pin Configuration ----------------------------------------------------------

// Functions ------------------------------------------------------------------
/**
 * @brief Reads a single input from the board
 *
 * @param[in] port the port to read from
 * @param[in] pin the pin number
 * 
 * @return whether the pin is high
 */
static bool is_pin_high(GPIO_TypeDef *port, int pin) {
    return (port->IDR & MASK_ONE_BIT_PIN(pin)) == MASK_ONE_BIT_PIN(pin);
}

void hwio_set_pin_opendrain(int pin){
	PORT->OTYPER |= MASK_ONE_BIT_PIN(pin);
}

void hwio_set_pin_pushpull(int pin){
    PORT->OTYPER &= ~MASK_ONE_BIT_PIN(pin);
}

void hwio_set_pin_low(int pin){
	PORT->BSRRH = MASK_ONE_BIT_PIN(pin);
}

void hwio_set_pin_high(int pin){
	PORT->BSRRL = MASK_ONE_BIT_PIN(pin);
}

int hwio_get_pin(int pin){
	return is_pin_high(PORT, pin) ? 1 : 0;
}
