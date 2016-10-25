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
 * couldn't open the file
 */
#define E_FAILED_TO_READ -1

/**
 * illegal VLA access
 */
#define E_INDEX_OUT_OF_BOUNDS -2

/**
 * bad bitmap
 */
#define E_BAD_BITMAP -3


#endif /* AUFGABE3_ERRORS_H_ */
