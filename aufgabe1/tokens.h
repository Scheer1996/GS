/*
 * Tokens
 *
 * Author: Moritz Höwer
 * Version: 1.0 - 29.09.2016
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

typedef struct {
    bool isOperator;
    int value;
} Token;

#endif /* _TOKEN_H */
