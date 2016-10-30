/** ****************************************************************
 * @file    aufgabe3/errors.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    24.10.2016
 * @brief   Header for the error codes
 ******************************************************************
 */


#ifndef _ERRORS_H_
#define _ERRORS_H_
/**
 * error when reading a file
 */
#define E_FAILED_TO_READ -1

/**
 * illegal VLA access
 */
#define E_INDEX_OUT_OF_BOUNDS -2

/**
 * bad bitmap (invalid)
 */
#define E_BAD_BITMAP -3

/**
 * not enough memory
 */
#define E_NO_MEMORY -4

/**
 * error when creating file for writing
 */
#define E_FAILED_TO_WRITE -5


#endif /* _ERRORS_H_ */
