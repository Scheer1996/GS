/** ****************************************************************
 * @file    aufgabe4/sensor.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    15.11.2016
 * @brief   Header for the Sensor module
 ******************************************************************
 */
#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

#define S1 0xd1000001e66da728
#define S2 0xB0000001e67fe228 // alte sensoren
#define S3 0xBF000001e66e8e28
#define S4 0x25000001e676ac28

/**
 * @brief Mesasure and read temperature with a sensor
 *
 * @param[in] romcode the romcode for addressing a sensor
 * @param[out] temp pointer to where to store the temperature in degrees celsius
 * @return error code
 * @retval 0           no error
 * @retval E_NO_SENSOR there is no sensor connected
 */
int sensor_measure(uint64_t romcode, double *temp);

#endif /* SENSOR_H */
