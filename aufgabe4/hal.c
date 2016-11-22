/** ****************************************************************
 * @file    aufgabe4/hal.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    15.11.2016
 * @brief   Implementation of the Hardware Abstraction module
 ******************************************************************
 */
#include "hal.h"

#include <stdbool.h>
#include "TI_Lib.h"
#include "errors.h"

/**
 * @brief The Port to use
 */
#define PORT GPIOG

/**
 * @brief Creates a mask for a pin, assuming 1 bit per pin.
 */
#define MASK_ONE_BIT_PIN(i)    (1 << (i))

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

/*
 * Sets the pin to open-drain mode
 */
void hal_set_pin_opendrain(int pin){
	PORT->OTYPER |= MASK_ONE_BIT_PIN(pin);
}

/*
 * Sets the pin to push-pull mode
 */
void hal_set_pin_pushpull(int pin){
    PORT->OTYPER &= ~MASK_ONE_BIT_PIN(pin);
}

/*
 * Sets the pin to low
 */
void hal_set_pin_low(int pin){
	PORT->BSRRH = MASK_ONE_BIT_PIN(pin);
}

/*
 * Sets the pin to high
 */
void hal_set_pin_high(int pin){
	PORT->BSRRL = MASK_ONE_BIT_PIN(pin);
}

/*
 * Reads the pin
 */
int hal_get_pin(int pin){
	return is_pin_high(PORT, pin) ? 1 : 0;
}
