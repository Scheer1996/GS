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

/**
 * @brief Size of the buffer for printing
 */
#define BUFFER_SIZE 40

/**
 * @brief start X position
 */
#define START_X 2

/**
 * @brief y position of the first line
 */
#define LINE_1_Y 2

/**
 * @brief y position of the second line
 */
#define LINE_2_Y 3

/*
 * Initializes the output (writing explanatory text)
 *
 * will display in line 1
 */
void output_init() {
    TFT_cursor_off();

#if MODE == READ_SINGLE_ROM
    TFT_gotoxy(START_X, LINE_1_Y);
    TFT_puts("Modus: Lesen des ROM");
#elif MODE == MEASURE_TEMP
    TFT_gotoxy(START_X, LINE_1_Y);
    TFT_puts("Modus: Temperaturmessung (einzeln)");
#endif
}

/*
 * display a romcode (8 btyes, hex)
 *
 * will display in line 2
 */
void output_display_romcode(uint64_t romcode) {
    char buffer[BUFFER_SIZE + 1] = { 0 };
    sprintf(buffer, "Romcode: %llx", romcode);

    TFT_gotoxy(START_X, LINE_2_Y);
    TFT_puts(buffer);

    // fill rest of line with spaces (to override potential leftovers)
    for (int i = strlen(buffer); i < BUFFER_SIZE; i++) {
        TFT_putc(' ');
    }
}

/*
 * displays a temperature
 *
 * will display in line 2
 */
void output_display_temp(double temp) {
    char buffer[BUFFER_SIZE + 1] = { 0 };
    sprintf(buffer, "Temperatur: %.2f °C", temp);

    TFT_gotoxy(START_X, LINE_2_Y);
    TFT_puts(buffer);

    // fill rest of line with spaces (to override potential leftovers)
    for (int i = strlen(buffer); i < BUFFER_SIZE; i++) {
        TFT_putc(' ');
    }
}

/*
 * display an error message
 *
 * will display in line 2
 */
void output_display_error(char *message) {
    TFT_gotoxy(START_X, LINE_2_Y);
    TFT_puts(message);

    // fill rest of line with spaces (to override potential leftovers)
    for (int i = strlen(message); i < BUFFER_SIZE; i++) {
        TFT_putc(' ');
    }
}
