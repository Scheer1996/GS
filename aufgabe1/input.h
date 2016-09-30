/*
 * Input
 *
 * Author: Moritz Höwer
 * Version: 1.0 - 29.09.2016
 */

#ifndef _INPUT_H
#define _INPUT_H

#include "tokens.h"
#include "errors.h"

/**
 * Initializes the input
 */
void input_init(void);

/**
 * Reads the next token from the keyboard
 *
 * @param token will be modified to represent the next token if
 *              method returns with error code 0
 * @return error code
 */
Token input_get_next_token(void);

#endif /* _INPUT_H */
