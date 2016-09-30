/*
 * Stack
 *
 * Author: Moritz Höwer
 * Version: 1.0 - 30.09.2016
 */
#include "stack.h"

#define STACK_SIZE 3

static int stack[STACK_SIZE];
static int size = 0;

int push(int value){
	//check if stack is full
	if(size >= STACK_SIZE){
		return E_STACK_OVERFLOW;
	}
	stack[size] = value;
	size++;	
	return 0;
}

int pop(int* value){
	//check if stack is empty
	if(size == 0){
		return E_STACK_EMPTY;
	}
	*value = stack[ size - 1 ];
	size--;	
	return 0;
}

void clear(void){
	size = 0;
}
