/** ****************************************************************
 * @file    aufgabe2/hardware_io.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    14.10.2016
 * @brief   Implementation of the Hardware IO module
 ******************************************************************
 */
#include "TI_Lib.h"
#include "errors.h"
#include "hardware_io.h"

/**
 * Creates a mask for a pin, assuming 1 bit per pin.
 */
#define MASK_ONE_BIT_PIN(i)    (0x01U << (i))

// Pin Configuration ----------------------------------------------------------
/**
 * the pin number where encoder channel A is connected to
 */
#define ENCODER_CHANNEL_A 0

/**
 * the pin number where encoder channel B is connected to
 */
#define ENCODER_CHANNEL_B 1

/**
 * the pin number of the LED used to indicate an error
 */
#define ERROR_LED 5

/**
 * the pin number of the LED used to indicate forward turning
 */
#define FORWARD_LED 6

/**
 * the pin number of the LED used to indicate backward turning
 */
#define BACKWARD_LED 7

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

/* ******************************************************************
 * Reads channel A from encoder
 * ******************************************************************
 */
bool hwio_get_encoder_channel_A(void) {
    return is_pin_high(GPIOE, ENCODER_CHANNEL_A);
}

/* ******************************************************************
 * Reads channel B from encoder
 * ******************************************************************
 */
bool hwio_get_encoder_channel_B(void) {
    return is_pin_high(GPIOE, ENCODER_CHANNEL_B);
}

/* ******************************************************************
 * Displays data on LEDs
 * ******************************************************************
 */
void hwio_display_data(char number, Direction dir) {
    // create reset mask
    int reset_mask = 0xFF00; // upper 8 bits get reset
    reset_mask |= MASK_ONE_BIT_PIN(FORWARD_LED); // forward LED gets reset
    reset_mask |= MASK_ONE_BIT_PIN(BACKWARD_LED); // backwards LED gets reset

    // reset our pins to 0
    GPIOG->BSRRH = reset_mask;

    // display number on upper 8 bits
    GPIOG->BSRRL = number << 8;

    // display direction
    if (dir == FORWARD) {
        GPIOG->BSRRL = MASK_ONE_BIT_PIN(FORWARD_LED);
    } else if (dir == BACKWARD) {
        GPIOG->BSRRL = MASK_ONE_BIT_PIN(BACKWARD_LED);
    }
}

/* ******************************************************************
 * Checks reset switches S6 + S7
 * ******************************************************************
 */
bool hwio_is_reset_pressed(void) {
    return !is_pin_high(GPIOE, 6) || !is_pin_high(GPIOE, 7);
}

/* ******************************************************************
 * Displays an error by illuminating D18
 * ******************************************************************
 */
void hwio_show_error(void) {
    GPIOG->BSRRL = MASK_ONE_BIT_PIN(ERROR_LED);
}

/* ******************************************************************
 * Clears the error LED D18
 * ******************************************************************
 */
void hwio_clear_error(void) {
    GPIOG->BSRRH = MASK_ONE_BIT_PIN(ERROR_LED);
}
