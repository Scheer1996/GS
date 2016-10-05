/**
 ******************************************************************************
 * @file    	output.c
 * @author  	Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 *              Philip Scheer (Philip.Scheer@haw-hamburg.de)
 *
 * @version 1.0
 * @date    04.10.2016
 * @brief   Output
 *******************************************************************
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




/*
 * @Brief: puts out the angle of rotation in Degree
 */
void output_display_angle_of_rotation(double number){
    clear_angle_of_rotation_area();
    
    char buffer[MAX_LINE_LENGTH + 1] = {0};
	sprintf(buffer, "Angle of Rotation: %d Degree", number);
    
    TFT_set_window(FONT6x8, AOR_X, AOR_Y, MAX_LINE_LENGTH, AOR_LINES);
    TFT_set_font_color(GREEN);
    TFT_puts(buffer);
}

/*
 * @Brief: puts out the rotation in Degrees per Second
 */
void output_display_rotation_speed(double number){
    clear_rotation_speed_area();
    
    char buffer[MAX_LINE_LENGTH + 1] = {0};
    sprintf(buffer, "Rotation Speed: %d Degrees per Second", number);
    
    TFT_set_window(FONT6x8, RS_X, RS_Y, MAX_LINE_LENGTH, RS_LINES);
    TFT_set_font_color(GREEN);
    TFT_puts(buffer);
}

static void clear_angle_of_rotation_area(void){
    TFT_set_window(FONT6x8, AOR_X, AOR_Y, MAX_LINE_LENGTH, AOR_LINES);
    // TFT_cls is broken, so we print 35 spaces
    TFT_puts("                                   ");
}
static void clear_rotation_speed_area(void){
    TFT_set_window(FONT6x8, RS_X, RS_Y, MAX_LINE_LENGTH, RS_LINES);
    // TFT_cls is broken, so we print 35 spaces
    TFT_puts("                                   ");
}

/*
void output_display_error(char* message){
    output_clear_error();
    clear_number_area();
    
    TFT_set_window(FONT6x8, ERROR_X, ERROR_Y, MAX_LINE_LENGTH, ERROR_LINES);
    TFT_set_font_color(RED);
    TFT_puts(message);
}

void output_clear_error(void){
    TFT_set_window(FONT6x8, ERROR_X, ERROR_Y, MAX_LINE_LENGTH, ERROR_LINES);
    // TFT_cls is broken, so we print 35 spaces
    TFT_puts("                                   ");
}*/
