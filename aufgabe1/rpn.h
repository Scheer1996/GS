/*
 * RPN
 *
 * Author: Moritz Höwer
 * Version: 1.0 - 29.09.2016
 */

#ifndef _RPN_H
#define _RPN_H

#include "tokens.h"
#include "errors.h"

/**
 * Performs the necessary action to handle the token passed to it if method
 * returns with error code 0
 *
 * @param token – the token to handle
 * @return error code
 *
 */
int rpn_process_token(Token);

#endif /* _RPN_H */
