/** ****************************************************************
 * @file    aufgabe1/output.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Implementation of the Output module
 ******************************************************************
 */
#include "stack.h"
#include "output.h"
#include <string.h>
#include <stdio.h>
#include "tft.h"

#define MAX_LINE_LENGTH 35
#define BUFFER_SIZE 20
#define SEPERATOR " | "
#define SEPERATOR_LENGTH 3

#define STACK_X 4
#define STACK_Y 1
#define STACK_LINES 1

#define ERROR_X 4
#define ERROR_Y 3
#define ERROR_LINES 1

#define NUMBER_X 4
#define NUMBER_Y 2
#define NUMBER_LINES 1

static void clear_stack_area(void);
static void clear_number_area(void);

/** ****************************************************************
 * @brief   Generates a @c char[] from the stack
 *
 * It contains as many elements as fit, starting at the top of the stack.
 * Elements are separated by "|"
 *
 * @param[in,out] output        the @c char[] to write to
 * @param[in]     sizeRemaining how many more chars can be added to @c output
 ******************************************************************
 */
static void generateStackLine(char* output, int sizeRemaining){
	char buffer[BUFFER_SIZE];
	int value;
	if(!stack_pop(&value)){
		int size;
		// write top value to buffer
		sprintf(buffer, "%d", value);
		
		size = strlen(buffer);
		if(sizeRemaining == MAX_LINE_LENGTH){
		    // this is the first element
		    if(size <= sizeRemaining){
				output = strcat(output, buffer);
				generateStackLine(output, sizeRemaining - size);
			}
		} else {
			// this is not the first element, we need a seperator
			if((size + SEPERATOR_LENGTH) <= sizeRemaining){
				output = strcat(output, SEPERATOR);
				output = strcat(output, buffer);
				generateStackLine(output, sizeRemaining - (size + SEPERATOR_LENGTH));
			}
		}
		stack_push(value);	
	} 
}

/* ****************************************************************
 * Displays the stack on screen
 ******************************************************************
 */
void output_display_stack(void){
    clear_stack_area();
    clear_number_area();
    char buffer[MAX_LINE_LENGTH + 1] = {0};
	generateStackLine(buffer, MAX_LINE_LENGTH);
    
    TFT_set_window(FONT6x8, STACK_X, STACK_Y, MAX_LINE_LENGTH, STACK_LINES);
    TFT_set_font_color(YELLOW);
    TFT_puts(buffer);
}

/* ****************************************************************
 * Displays a number on the screen
 ******************************************************************
 */
void output_display_number(int number){
    clear_number_area();
    
    char buffer[MAX_LINE_LENGTH + 1] = {0};
	sprintf(buffer, "Entering: %d", number);    
    
    TFT_set_window(FONT6x8, NUMBER_X, NUMBER_Y, MAX_LINE_LENGTH, NUMBER_LINES);
    TFT_set_font_color(GREEN);
    TFT_puts(buffer);
}

/** ****************************************************************
 * @brief Clears the screen space where numbers are written to
 ******************************************************************
 */
static void clear_number_area(void){
    TFT_set_window(FONT6x8, NUMBER_X, NUMBER_Y, MAX_LINE_LENGTH, NUMBER_LINES);
    // TFT_cls is broken, so we print 35 spaces
    TFT_puts("                                   ");
}

/** ****************************************************************
 * @brief Clears the screen space where the stack is written to
 ******************************************************************
 */
static void clear_stack_area(void){
    TFT_set_window(FONT6x8, STACK_X, STACK_Y, MAX_LINE_LENGTH, STACK_LINES);
    // TFT_cls is broken, so we print 35 spaces
    TFT_puts("                                   ");
}

/* ****************************************************************
 * Displays an error message on the screen
 ******************************************************************
 */
void output_display_error(char* message){
    output_clear_error();
    clear_number_area();
    
    TFT_set_window(FONT6x8, ERROR_X, ERROR_Y, MAX_LINE_LENGTH, ERROR_LINES);
    TFT_set_font_color(RED);
    TFT_puts(message);
}

/* ****************************************************************
 * Clears the error message
 ******************************************************************
 */
void output_clear_error(void){
    TFT_set_window(FONT6x8, ERROR_X, ERROR_Y, MAX_LINE_LENGTH, ERROR_LINES);
    // TFT_cls is broken, so we print 35 spaces
    TFT_puts("                                   ");
}
