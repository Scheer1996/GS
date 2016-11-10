/** ****************************************************************
 * @file    aufgabe4/hardware_io.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    06.11.2016
 * @brief   Header for the Hardware IO module
 ******************************************************************
 */
#ifndef HARDWARE_IO_H
#define HARDWARE_IO_H

void hwio_set_pin_opendrain(int pin);

void hwio_set_pin_pushpull(int pin);

void hwio_set_pin_low(int pin);

void hwio_set_pin_high(int pin);

int hwio_get_pin(int pin);

#endif /* HARDWARE_IO_H */
