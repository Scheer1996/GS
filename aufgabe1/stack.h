/*
 * Stack
 *
 * Author: Moritz Höwer
 * Version: 1.1 - 01.10.2016
 */

#ifndef _STACK_H
#define _STACK_H

#include "errors.h"

/**
 * @brief Adds value to the top of the stack if there is space.
 *
 * @param value the value to add
 * @return error code
 */
int stack_push(int);

/**
 * @brief Retrieves and removes the first value from the stack and writes it to value,
 *        if method returns error code 0
 *
 * @param value pointer for returning the value
 * @return error code
 */
int stack_pop(int*);

/**
 * @brief Empties the stack.
 */
void stack_clear(void);

#endif /* _STACK_H */
