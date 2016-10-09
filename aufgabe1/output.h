/** ****************************************************************
 * @file    aufgabe1/output.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Header for the Output module
 ******************************************************************
 */

#ifndef _OUTPUT_H
#define _OUTPUT_H

/** ****************************************************************
 * @brief   Displays an error message on the screen
 *
 * The error message appears directly above the keypad in red font.
 *
 * @param[in] message the message to display
 ******************************************************************
 */
void output_display_error(char* message);

/** ****************************************************************
 * @brief   Displays a number on the screen
 *
 * The number appears between the stack and the error message in green font.
 * It is prefixed with "Entering: ".
 *
 * @param[in] number the number to display
 ******************************************************************
 */
void output_display_number(int number);

/** ****************************************************************
 * @brief   Displays the stack on screen
 *
 * The stack appears at the top of the screen in yellow font.
 * It contains as many elements as fit, starting at the top of the stack.
 * Elements are separated by "|"
 ******************************************************************
 */
void output_display_stack(void);

/** ****************************************************************
 * @brief   Clears the error message
 ******************************************************************
 */
void output_clear_error(void);

#endif /* _OUTPUT_H */
