/** ****************************************************************
 * @file    input.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Header for the Input module
 ******************************************************************
 */
#ifndef _INPUT_H
#define _INPUT_H

#include "tokens.h"
#include "errors.h"

/** ****************************************************************
 * @brief   Initializes the Input module
 ******************************************************************
 */
void input_init(void);

/** ****************************************************************
 * @brief   Generates the next Token from user input
 *
 * @param[out] token pointer where the generated Token is to be written to
 *
 * @return error code
 * @retval 0 no error
 * @retval E_INVALID_INPUT user input could not be parsed into a valid Token
 ******************************************************************
 */
int input_get_next_token(Token* token);

#endif /* _INPUT_H */
