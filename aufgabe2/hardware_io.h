/** ****************************************************************
 * @file    aufgabe2/hardware_io.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    14.10.2016
 * @brief   Header for the Hardware IO module
 ******************************************************************
 */
#ifndef HARDWARE_IO_H
#define HARDWARE_IO_H

#include <stdbool.h>
#include "rotary_encoder.h"

/**
 * @brief Reads channel A from encoder
 *
 * @retval true channel is high
 * @retval false channel is low
 */
bool hwio_get_encoder_channel_A(void);

/**
 * @brief Reads channel B from encoder
*
 * @retval true channel is high
 * @retval false channel is low
 */
bool hwio_get_encoder_channel_B(void);

/**
 * @brief Displays data on LEDs
 *
 * @param[in] number an 8 bit number to be displayed on LEDS D21-D28
 * @param[in] dir displays the direction on LEDS D20 / D19
 */
void hwio_display_data(char number, Direction dir);


/**
 * @brief Displays an error by illuminating D18
 */
void hwio_show_error(void);

/**
 * @brief Clears the error LED D18
 */
void hwio_clear_error(void);

/**
 * @brief Checks reset switches S7 and S6
 * 
 * @return true when either is pressed
 */
bool hwio_is_reset_pressed(void);

#endif /* HARDWARE_IO_H */
