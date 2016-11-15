/** ****************************************************************
 * @file    aufgabe4/output.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    15.11.2016
 * @brief   Header for the Output Display module
 ******************************************************************
 */
#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdint.h>

/**
 * @brief Initializes the output (writing explanatory text)
 *
 * Will display in line 1
 */
void output_init(void);

/**
 * @brief Displays a romcode (8 bytes, hex) on the screen
 *
 * Will display in line 2
 *
 * @param[in] romcode the romcode to print
 */
void output_display_romcode(uint64_t romcode);

/**
 * @brief Display an error message
 *
 * Will display in line 2
 *
 * @param[in] message the message to print
 */
void output_display_error(char *message);

/**
 * @brief Displays a temperature on the screen
 *
 * Will display in line 2
 *
 * @param[in] temp the temperature
 */
void output_display_temp(double temp);

#endif /* _OUTPUT_H */
