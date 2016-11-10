/** ****************************************************************
 * @file    aufgabe4/output.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    06.11.2016
 * @brief   Header for the Output Display module
 ******************************************************************
 */
#ifndef OUTPUT_H
#define OUTPUT_H

/**
 * @brief Initializes the output (writing explanatory text)
 */
void output_init(void);

void output_display_number(unsigned long long number);

#endif /* _OUTPUT_H */
