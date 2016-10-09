/** ****************************************************************
 * @file    aufgabe2/output.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Implmentation of the Output module
 ******************************************************************
 */
#include "output.h"
#include <string.h>
#include <stdio.h>
#include "tft.h"

#define MAX_LINE_LENGTH 35

#define AOR_X 4
#define AOR_Y 2
#define AOR_LINES 1

#define RS_X 4
#define RS_Y 3
#define RS_LINES 1

static void clear_angle_of_rotation_area(void);
static void clear_rotation_speed_area(void);

/* ****************************************************************
 * Displays the angle of rotation on the screen
 ******************************************************************
 */
void output_display_angle_of_rotation(double angle) {
    clear_angle_of_rotation_area();

    char buffer[MAX_LINE_LENGTH + 1] = { 0 };
    sprintf(buffer, "Angle of Rotation: %d Degree", angle);

    TFT_set_window(FONT6x8, AOR_X, AOR_Y, MAX_LINE_LENGTH, AOR_LINES);
    TFT_set_font_color(GREEN);
    TFT_puts(buffer);
}

/* ****************************************************************
 * Displays the speed of rotation on the screen
 ******************************************************************
 */
void output_display_rotation_speed(double speed) {
    clear_rotation_speed_area();

    char buffer[MAX_LINE_LENGTH + 1] = { 0 };
    sprintf(buffer, "Rotation Speed: %d Degrees per Second", speed);

    TFT_set_window(FONT6x8, RS_X, RS_Y, MAX_LINE_LENGTH, RS_LINES);
    TFT_set_font_color(GREEN);
    TFT_puts(buffer);
}

/** ****************************************************************
 * @brief   Clears the area where the angle is written to
 ******************************************************************
 */
static void clear_angle_of_rotation_area(void) {
    TFT_set_window(FONT6x8, AOR_X, AOR_Y, MAX_LINE_LENGTH, AOR_LINES);
    // TFT_cls is broken, so we print 35 spaces
    TFT_puts("                                   ");
}

/** ****************************************************************
 * @brief   Clears the area where the speed is written to
 ******************************************************************
 */
static void clear_rotation_speed_area(void) {
    TFT_set_window(FONT6x8, RS_X, RS_Y, MAX_LINE_LENGTH, RS_LINES);
    // TFT_cls is broken, so we print 35 spaces
    TFT_puts("                                   ");
}
