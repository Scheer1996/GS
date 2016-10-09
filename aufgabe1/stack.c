/** ****************************************************************
 * @file    aufgabe1/stack.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Implementation for the Stack module
 ******************************************************************
 */
#include "stack.h"

/**
 * How many elements can be stored in the stack
 */
#define STACK_SIZE 100

/**
 * the stack data
 */
static int stack[STACK_SIZE];

/**
 * the stack pointer
 */
static int size = 0;

/* ****************************************************************
 * Adds value to the top of the stack if there is space.
 ******************************************************************
 */
int stack_push(int value){
	//check if stack is full
	if(size >= STACK_SIZE){
		return E_STACK_OVERFLOW;
	}
	stack[size] = value;
	size++;	
	return 0;
}

/* ****************************************************************
 * Retrieves a value from the top of the stack if there is one.
 ******************************************************************
 */
int stack_pop(int* value){
	//check if stack is empty
	if(size == 0){
		return E_STACK_EMPTY;
	}
	*value = stack[ size - 1 ];
	size--;	
	return 0;
}

/* ****************************************************************
 * Empties the stack
 ******************************************************************
 */
void stack_clear(void){
	size = 0;
}
