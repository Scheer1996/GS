/**
 ******************************************************************************
 * @file    	io.c
 * @author  	Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 *              Philip Scheer (Philip.Scheer@haw-hamburg.de)
 *
 * @version 1.0
 * @date    07.10.2016
 * @brief   io
 *******************************************************************
 */
#include 
"io.h"

// Bit masks for the GPIO Register
#define MODER_MASK_PIN_I(i)     (0x03U << (2* (i)));
#define OUTPUT_MASK_PIN_I(i)    (0x01U << (2* (i)));


#define BSRRH_MASK_PIN_I(i)     (0x01U << (i));
#define BSRRL_MASK_PIN_I(i)     (0x01U << (i));

#define NO_OF_PINS_OF_PORT      (16)

// constants for configuration of Ports and Pins
#define PORT        GPIOE
#define LED_D18     5       //PORT 18 - PG5
#define LED_D19     6       //PORT 19 - PG6
#define LED_D20     7       //PORT 20 - PG7


void configureOutput(unsigned int pin) {
    PORT->MODER = (PORT->MODER & ~MODER_MASK_PIN_I(pin))
                | (0xFFFFFFFF & OUTPUT_MASK_PIN_I(pin));
}


void configureInput(unsigned int pin) {
    PORT->MODER = PORT->MODER & ~MODER_MASK_PIN_I(pin);
}


void setPort(unsigned int port, bool setToOne) {
    if (port >= NO_OF_PINS_OF_PORT) {
        // error handling pending
        // copied from Korf :D
        return ;
    }
    
    if(setToOne) {
        PORT->BSRRL = BSRRL_MASK_PIN_I(port);
    } else {
        PORT_>BSRRH = BSRRH_MASK_PIN_I(port);
    }
}
