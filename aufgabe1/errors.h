/** ****************************************************************
 * @file    errors.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Header for the error codes
 ******************************************************************
 */
#ifndef _ERRORS_H
#define _ERRORS_H

/**
 * The stack is full
 */
#define E_STACK_OVERFLOW -1

/**
 * The stack is empty
 */
#define E_STACK_EMPTY -2

/**
 * Integer domain overflow (or underflow)
 */
#define E_OVERFLOW -3

/**
 * Trying to divide by zero
 */
#define E_DIVIDE_0 -4

/**
 * There is an operand missing for evaluating the current operator
 */
#define E_MISSING_OPERAND -5

/**
 * The input was invalid
 */
#define E_INVALID_INPUT -6

#endif /* _ERRORS_H */
