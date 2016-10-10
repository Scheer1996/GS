/** ****************************************************************
 * @file    aufgabe2/output_display.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Header for the Output Display module
 ******************************************************************
 */
#ifndef OUTPUT_H
#define OUTPUT_H

/** ****************************************************************
 * @brief Displays the angle of rotation on the screen.
 *
 * @param[in] angle the angle in degrees
 ******************************************************************
 */
void output_display_angle_of_rotation(double angle);

/** ****************************************************************
 * @brief Displays the speed of rotation on the screen.
 *
 * @param[in] speed the speed in degrees per second
 ******************************************************************
 */
void output_display_rotation_speed(double speed);

#endif /* _OUTPUT_H */
