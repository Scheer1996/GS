/** ****************************************************************
 * @file    aufgabe1/main.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Main logic for the program
 ******************************************************************
 */
#include "main.h"
#include "TI_Lib.h"
#include "input.h"
#include "rpn.h"
#include "output.h"
#include "tokens.h"

/** ****************************************************************
 * @brief   Program entry point
 ******************************************************************
 */
int main(void) {
    // Initialization
    Init_TI_Board();
    input_init();

    while (1) {
        Token t;
        int res;

        // read next token
        res = input_get_next_token(&t);

        // clear previous error
        output_clear_error();

        // check for errors during input
        if (res == E_INVALID_INPUT) {
            output_display_error("That is not a valid input!");
            continue;
        } else if (res == E_OVERFLOW) {
            output_display_error("The number entered is too big!");
            continue;
        }

        // process token
        res = rpn_process_token(t);

        // check for errors during processing
        if (res == E_MISSING_OPERAND) {
            output_display_error("You are missing an operand here!");
            continue;
        } else if (res == E_OVERFLOW) {
            output_display_error("The number calculated is too big!");
            continue;
        } else if (res == E_DIVIDE_0) {
            output_display_error("You don't want to divide by zero...");
            continue;
        } else if (res == E_STACK_OVERFLOW) {
            output_display_error("The stack is full!");
            continue;
        }

        // display the stack
        output_display_stack();
    }

    return 0;

}

