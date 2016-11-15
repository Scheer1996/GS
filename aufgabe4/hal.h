/** ****************************************************************
 * @file    aufgabe4/hal.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    15.11.2016
 * @brief   Header for the Hardware Abstraction module
 ******************************************************************
 */
#ifndef HAL_H
#define HAL_H

/**
 * @brief Sets the pin to open-drain mode
 *
 * @param pin the pin to set
 */
void hal_set_pin_opendrain(int pin);

/**
 * @brief Sets the pin to push-pull mode
 *
 * @param pin the pin to set
 */
void hal_set_pin_pushpull(int pin);

/**
 * @brief Sets the pin to low (0V)
 *
 * @param pin the pin to set
 */
void hal_set_pin_low(int pin);

/**
 * @brief Sets the pin to high (3,3V)
 *
 * @param pin the pin to set
 */
void hal_set_pin_high(int pin);

/**
 * @brief Reads the pin
 *
 * @param pin the pin to read
 * @retval 0 pin is low
 * @retval 1 pin is high
 */
int hal_get_pin(int pin);

#endif /* HARDWARE_IO_H */
