/** ****************************************************************
 * @file    aufgabe2/hardware_io.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Header for the Hardware IO module
 ******************************************************************
 */
#ifndef HARDWARE_IO_H
#define HARDWARE_IO_H

#include <stdbool.h>
#include "rotary_encoder.h"

/**
 * @brief Initializes the Hardware IO
 */
void hardware_io_init(void);

/**
 * @brief Reads channel A from encoder
 *
 * @retval true channel is high
 * @retval false channel is low
 */
bool hardware_io_get_encoder_channel_A(void);

/**
 * @brief Reads channel B from encoder
*
 * @retval true channel is high
 * @retval false channel is low
 */
bool hardware_io_get_encoder_channel_B(void);

/**
 * @brief Displays an 8 bit number on LEDS D21-D28
 */
void hardware_io_display_number(char number);

/**
 * @brief Displays the direction on LEDS D20 / D19
 */
void hardware_io_display_direction(Direction dir);

/**
 * @brief Displays an error by illuminating D18
 */
void hardware_io_display_error(void);

/**
 * @brief Clears the error LED D18
 */
void hardware_io_clear_error(void);

/**
 * @brief Checks reset switches S7 and S6
 * 
 * @return true when either is pressed
 */
bool hardware_io_is_reset_pressed(void);

#endif /* HARDWARE_IO_H */
