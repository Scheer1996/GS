/** ****************************************************************
 * @file    aufgabe1/rpn.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Header for the RPN modules
 ******************************************************************
 */
#ifndef _RPN_H
#define _RPN_H

#include "tokens.h"
#include "errors.h"

/** ****************************************************************
 * @brief   Processes the Token that is passed to it
 *
 * @param[in] token the Token to process
 *
 * @return error code
 * @retval 0 no error
 * @retval E_STACK_OVERFLOW  the stack is full
 * @retval E_MISSING_OPERAND the operation is missing one or more operands
 * @retval E_DIVIDE_0        the user tried to divide by zero
 * @retval E_OVERFLOW        the user tried to calculate something, but it caused
 *                           an overflow of the underlying @c int.
 ******************************************************************
 */
int rpn_process_token(Token token);

#endif /* _RPN_H */
