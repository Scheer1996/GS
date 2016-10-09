/** ****************************************************************
 * @file    aufgabe1/tokens.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Header for the tokens
 ******************************************************************
 */
#ifndef _TOKEN_H
#define _TOKEN_H

#include <stdbool.h>

#define OP_ADD 1
#define OP_SUBTRACT 2
#define OP_MULTIPLY 3
#define OP_DIVIDE 4
#define OP_PRINT 5
#define OP_PRINT_ALL 6
#define OP_CLEAR 7
#define OP_DUPLICATE 8
#define OP_REVERSE 9

/**
 * A Token consists of a flag that decides whether it's an operator or a
 * number, accompanied by the value
 */
typedef struct {
    /**
     * is this an operator or a number?
     */
    bool isOperator;

    /**
     * the value associated with this (operator type or number)
     */
    int value;
} Token;

#endif /* _TOKEN_H */
