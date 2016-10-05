/*
 * Stack
 *
 * Author: Moritz Höwer
 * Version: 1.1 - 01.10.2016
 */
#include "stack.h"

#define STACK_SIZE 100

static int stack[STACK_SIZE];
static int size = 0;

/**
 * @brief Adds value to the top of the stack if there is space.
 *
 * @param value the value to add
 * @return error code
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

/**
 * @brief Retrieves and removes the first value from the stack and writes it to value,
 *        if method returns error code 0
 *
 * @param value pointer for returning the value
 * @return error code
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

/**
 * @brief Empties the stack.
 */
void stack_clear(void){
	size = 0;
}
