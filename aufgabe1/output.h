/*
 * Output
 *
 * Author: Moritz Höwer
 * Version: 1.0 - 29.09.2016
 */

#ifndef _OUTPUT_H
#define _OUTPUT_H

/**
 * Displays an error in the designated error area.
 */
void output_display_error(char*);

/**
 * Displays a line in the message area.
 */
void output_display_line(char*);

/**
 * Sets up the window for the error area.
 */
void setup_error_area(void);

/**
 * Sets up the windows for the message area.
 */
void setup_message_area(void);

#endif /* _OUTPUT_H */
