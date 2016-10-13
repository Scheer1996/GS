/** ****************************************************************
 * @file    aufgabe2/hardware_io.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Implementation of the Hardware IO module
 ******************************************************************
 */
#include "TI_Lib.h"
#include "errors.h"
#include "hardware_io.h"

// Bit masks for the GPIO Register
#define MODER_MASK_PIN(i)    (0x03U << (2*(i)))
#define OUTPUT_MASK_PIN(i)   (0x01U << (2*(i)))

#define MASK_ONE_BIT_PIN(i)    (0x01U << (i))

#define NO_OF_PINS_OF_PORT   (16)

#define LED_D18     5       //PORT 18 - PG5
#define LED_D19     6       //PORT 19 - PG6
#define LED_D20     7       //PORT 20 - PG7

/*void configureOutput(unsigned int pin) {
    PORT->MODER = (PORT->MODER & ~MODER_MASK_PIN_I(pin)) | (0xFFFFFFFF & OUTPUT_MASK_PIN_I(pin));
}

void configureInput(unsigned int pin) {
    PORT->MODER = PORT->MODER & ~MODER_MASK_PIN_I(pin);
}

int setPort(unsigned int port, bool set_to_one) {
    if (port >= NO_OF_PINS_OF_PORT) {
        return E_INVALID_PIN;
    }

    if (set_to_one) {
        PORT->BSRRL = BSRRL_MASK_PIN_I(port);
    } else {
        PORT->BSRRH = BSRRH_MASK_PIN_I(port);
    }
    return 0;
}


void init_hardware_io(){
    configureOutput(LED_D18);
    configureOutput(LED_D19);
    configureOutput(LED_D20);
}
*/

/**
 * @brief Reads a single input from the board
 *
 * @param[in] port the port to read from
 * @param[in] pin the pin number
 * 
 * @return whether the pin is high
 */
bool is_pin_high(GPIO_TypeDef *port, int pin){
	return (port->IDR & MASK_ONE_BIT_PIN(pin)) == MASK_ONE_BIT_PIN(pin);
}


/* ******************************************************************
 * Reads channel A from encoder
 * ******************************************************************
 */
bool hardware_io_get_encoder_channel_A(void){
	return is_pin_high(GPIOE, 0);
}

/* ******************************************************************
 * Reads channel B from encoder
 * ******************************************************************
 */
bool hardware_io_get_encoder_channel_B(void){
	return is_pin_high(GPIOE, 1);
}

/* ******************************************************************
 * Displays an 8bit number on LEDS D21-D28
 * ******************************************************************
 */
void hardware_io_display_number(char number){
	// a bit lazy...
	GPIOG->ODR &= 0xFF;
	GPIOG->ODR |= number << 8;
}

/* ******************************************************************
 * Displays the direction on LEDS D20 / D19
 * ******************************************************************
 */
void hardware_io_display_direction(Direction dir){
	int mask = 0;
	if(dir == FORWARD){
		mask = 1;
	} else if(dir == BACKWARD){
		mask = 2;
	}
	
	GPIOG->ODR &= ~(3 << 6);
	GPIOG->ODR |= (mask << 6);
}

/* ******************************************************************
 * Checks reset switches S6 + S7
 * ******************************************************************
 */
bool hardware_io_is_reset_pressed(void){
	return !is_pin_high(GPIOE, 6) || !is_pin_high(GPIOE, 7);
}


/* ******************************************************************
 * Displays an error by illuminating D18
 * ******************************************************************
 */
void hardware_io_display_error(void){
	GPIOG->BSRRL = MASK_ONE_BIT_PIN(5);
}


/* ******************************************************************
 * Clears the error LED D18
 * ******************************************************************
 */
void hardware_io_clear_error(void){
	GPIOG->BSRRH = MASK_ONE_BIT_PIN(5);
}
