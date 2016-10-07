/** ****************************************************************
 * @file    input.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Implementation of the Input module
 *
 * Provides methods to read user inputs from the touchscreen and converts them
 * into Tokens to be handled by the RPN module.
 ******************************************************************
 */
#include "input.h"
#include "keypad.h"
#include "output.h"
#include <stdbool.h>

/**
 * The factor to increase @c number by when parsing
 */
#define FAKTOR 10

/* ****************************************************************
 * Initializes the input module
 ******************************************************************
 */
void input_init(void){
    Make_Touch_Pad();
}

/** ****************************************************************
 * @brief   Reads a character from the on screen keyboard
 *
 * @return the character that was read
 ******************************************************************
 */
static char get_char(void){
    int code = Get_Touch_Pad_Input();
    return (char)code;
}

/** ****************************************************************
 * @brief   Converts a character to it's corresponding Token
 *
 * @param[in] ch the character to convert
 * @param[out] t pointer where the generated Token is to be written to
 *
 * @return error code
 * @retval 0 no error
 * @retval E_INVALID_INPUT the character @c ch did not represent a valid Token
 ******************************************************************
 */
static int get_operator_token(char ch, Token* t){
    t->isOperator = true;
    switch(ch){
        case '+':
            t->value = OP_ADD;
            break;
        case '-':
            t->value = OP_SUBTRACT;
            break;
        case '*':
            t->value = OP_MULTIPLY;
            break;
        case '/':
            t->value = OP_DIVIDE;
            break;
        case 'p':
            t->value = OP_PRINT;
            break;
        case 'f':
            t->value = OP_PRINT_ALL;
            break;
        case 'c':
            t->value = OP_CLEAR;
            break;
        case 'd':
            t->value = OP_DUPLICATE;
            break;
        case 'r':
            t->value = OP_REVERSE;
            break;
        default:
            return E_INVALID_INPUT;
    }
    
    return 0;    
}

/* ****************************************************************
 * Generates the next Token from user input
 ******************************************************************
 */
int input_get_next_token(Token* token){
    // remember the following two between function calls
    static bool isTokenQueued;
    static char ch;
    
    // check if we have a token left to deal with
    if(isTokenQueued){
        isTokenQueued = false;
        return get_operator_token(ch, token);
    } else {
        // variables for converting characters to number
        bool isReadingNumber = false;
        int number = 0;
        
        while(1){
            // read a character
            ch = get_char();
            
            // check if we read a number
            if(ch >= '0' && ch <= '9'){
                isReadingNumber = true;
                number *= FAKTOR;
                number += (ch - '0');
                
                // check if we had an overflow
                if(number < 0){
                    return E_OVERFLOW;
                }
                
                output_display_number(number);
                
            } else {
                // we are no longer getting numbers
                if(!isReadingNumber){
                    // we weren't reading a number anyways
                    // so we call helper method to convert input to token
                    return get_operator_token(ch, token);
                } else {
                    // we were reading a number, so we need to queue he next token if
                    // the character is not ' ' (SPACE)
                    isTokenQueued = (ch != ' ');
                }
                break;
            }
        }
        // convert number to token
        if(isReadingNumber){
            token->isOperator = 0;
            token->value = number;
        }
        
        return 0;
    }
    
}
