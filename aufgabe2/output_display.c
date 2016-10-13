/** ****************************************************************
 * @file    aufgabe2/output_display.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Implementation of the Output Display module
 ******************************************************************
 */
#include "output_display.h"

#include <string.h>
#include <stdio.h>
#include "tft.h"

#define BUFFER_SIZE 40

#define OUT_X 2
#define OUT_Y 2

/* ****************************************************************
 * Displays the angle of rotation on the screen and the speed of roation on the screen
 ******************************************************************
 */
void output_display_data(double angle, double speed) {
    char buffer[BUFFER_SIZE + 1] = { 0 };
    sprintf(buffer, "Winkel: %6.1f Grad bei %6.2f Grad/s", angle, speed);

    TFT_gotoxy(OUT_X, OUT_Y);
    TFT_puts(buffer);
}
