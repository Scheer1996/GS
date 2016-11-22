/** ****************************************************************
 * @file    aufgabe4/config.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    15.11.2016
 * @brief   Header for config
 ******************************************************************
 */

#ifndef CONFIG_H
#define CONFIG_H

/**
 * @brief Continuously read the romcode of an attached sensor and display it
 */
#define READ_SINGLE_ROM 1

/**
 * @brief Continuously measure and read the temperature of a specific sensor
 */
#define MEASURE_TEMP 2

/**
 * @brief Automatic mode - find all slaves and then continuously read their
 *        temperatures
 */
#define AUTO_MODE 3

/**
 * @brief Switch to select which mode the software should operate in
 */
#define MODE AUTO_MODE

#endif /* CONFIG_H */
