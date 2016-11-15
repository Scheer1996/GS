/** ****************************************************************
 * @file    aufgabe4/output.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    06.11.2016
 * @brief   Implementation of the Output Display module
 ******************************************************************
 */
#include <string.h>
#include <stdio.h>
#include "tft.h"
#include "output.h"
#include "config.h"

#define BUFFER_SIZE 40

#define TEXT_X 2
#define DATA_X 19

#define LINE_1_Y 2
#define LINE_2_Y 3

/* ****************************************************************
 * Updates the angle and speed of rotation on the screen.
 ******************************************************************
 */
void output_update_data(double angle, double speed) {
    char buffer[BUFFER_SIZE + 1] = { 0 };

    // write angle to string
    sprintf(buffer, "%6.1f", angle);
    TFT_gotoxy(DATA_X, LINE_1_Y);
    TFT_puts(buffer);

    //write speed to string
    sprintf(buffer, "%6.2f", speed);
    TFT_gotoxy(DATA_X, LINE_2_Y);
    TFT_puts(buffer);
}

/* ****************************************************************
 * Initializes the output (writing explanatory text)
 ******************************************************************
 */
void output_init() {
    TFT_cursor_off();
    
#if MODE == READ_SINGLE_ROM
    TFT_gotoxy(TEXT_X, LINE_1_Y);
    TFT_puts("Modus: Lesen des ROM");
#elif MODE == MEASURE_TEMP
    TFT_gotoxy(TEXT_X, LINE_1_Y);
    TFT_puts("Modus: Temperaturmessung (einzeln)");
#endif
}

void output_display_romcode(uint64_t romcode){
    char buffer[BUFFER_SIZE + 1] = { 0 };
    sprintf(buffer, "Romcode: %llx", romcode);
    
    TFT_gotoxy(TEXT_X, LINE_2_Y);
    TFT_puts(buffer);
}

void output_display_temp(double temp){
    char buffer[BUFFER_SIZE + 1] = { 0 };
    sprintf(buffer, "Temperatur: %.2f", temp);
    
    TFT_gotoxy(TEXT_X, LINE_2_Y);
    TFT_puts(buffer);
    for(int i = strlen(buffer); i < BUFFER_SIZE; i++){
        TFT_putc(' ');
    }
}

void output_display_error(char *message){
    TFT_gotoxy(TEXT_X, LINE_2_Y);
    TFT_puts(message);
    for(int i = strlen(message); i < BUFFER_SIZE; i++){
        TFT_putc(' ');
    }
}
