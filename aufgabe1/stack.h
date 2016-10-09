/** ****************************************************************
 * @file    aufgabe1/stack.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Header for the Stack module
 ******************************************************************
 */
#ifndef _STACK_H
#define _STACK_H

#include "errors.h"

/** ****************************************************************
 * @brief   Adds value to the top of the stack if there is space.
 *
 * @param [in] value the value to add
 *
 * @return error code
 * @retval 0 no error
 * @retval E_STACK_OVERFLOW could not add @c value because the stack is full.
 ******************************************************************
 */
int stack_push(int value);

/** ****************************************************************
 * @brief   Retrieves a value from the top of the stack if there is one.
 *
 * @param [out] value pointer to where the value should be stored
 *
 * @return error code
 * @retval 0 no error
 * @retval E_STACK_EMPTY could not retrieve @c value because the stack is empty.
 ******************************************************************
 */
int stack_pop(int* value);

/** ****************************************************************
 * @brief   Empties the stack
 ******************************************************************
 */
void stack_clear(void);

#endif /* _STACK_H */
