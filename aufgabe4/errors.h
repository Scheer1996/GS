/** ****************************************************************
 * @file    aufgabe4/errors.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    15.11.2016
 * @brief   Header for the error codes
 ******************************************************************
 */

#ifndef ERRORS_H
#define ERRORS_H

/**
 * @brief The CRC check failed
 */
#define E_CRC_FAILED -1

/**
 * @brief There was no sensor connected to the system
 */
#define E_NO_SENSOR -2

#define E_LIST_NULL -3

#define E_NO_MEMORY -4

#define E_INDEX_OUT_OF_BOUNDS -5

#define E_INVALID_STATE -6


#endif /* ERRORS_H */
