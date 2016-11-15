/** ****************************************************************
 * @file    aufgabe4/sensor.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    10.11.2016
 * @brief   Header for the Sensor module
 ******************************************************************
 */
#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

// Board 701/2
#define S1 0xB8000001e6713028
#define S2 0xB0000001e67fe228
#define S3 0xBF000001e66e8e28
#define S4 0x25000001e676ac28

int sensor_measure(uint64_t romcode, double *temp);

#endif /* SENSOR_H */
