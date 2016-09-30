/*
 * RPN
 *
 * Author: Moritz Höwer
 * Version: 1.0 - 30.09.2016
 */
#include "rpn.h"
#include "stack.h"

int get_two_operands(int* op1, int* op2){
	// get first operand
	if(pop(op1)){
		return E_MISSING_OPERAND;
	}
	// get seccond operand
	if(pop(op2)){
		// restore stack
		push(*op1);
		return E_MISSING_OPERAND;
	}
	return 0;
}

int add(void){
	int op1, op2;
	int res;
	
	if(get_two_operands(&op1, &op2)){
		return E_MISSING_OPERAND;
	}
	
	res = op1 + op2;
	// sollte nochmal durchdacht werden
	/*// check for overflow
	if(res < 0 && op1 > 0 && op2 > 0){
		// restore stack
		push(op2);
		push(op1);
		return E_OVERFLOW;
	}*/
	
	// add result to stack
	// this can't fail because stack had 2 more elements at the start 
	// of this function
	push(res);
	return 0;
}

int subtract(void){
	int op1, op2;
	int res;
	
	if(get_two_operands(&op1, &op2)){
		return E_MISSING_OPERAND;
	}
	
	res = op2 - op1;
	// sollte nochmal durchdacht werden
	/*// check for overflow
	if(res > 0){
		// restore stack
		push(op2);
		push(op1);
		return E_OVERFLOW;
	}*/
	
	// add result to stack
	// this can't fail because stack had 2 more elements at the start 
	// of this function
	push(res);
	return 0;
}

int multiply(void){
	int op1, op2;
	int res;
	
	if(get_two_operands(&op1, &op2)){
		return E_MISSING_OPERAND;
	}
	
	res = op1 * op2;
	// sollte nochmal durchdacht werden
	/*// check for overflow
	if(res > 0){
		// restore stack
		push(op2);
		push(op1);
		return E_OVERFLOW;
	}*/
	
	// add result to stack
	// this can't fail because stack had 2 more elements at the start 
	// of this function
	push(res);
	return 0;
}

int divide(void){
	int op1, op2;
	int res;
	
	if(get_two_operands(&op1, &op2)){
		return E_MISSING_OPERAND;
	}
	if(op1 == 0){
		// restore stack
		push(op2);
		push(op1);
		return E_DIVIDE_0;
	}
	
	res = op2 / op1;
	// sollte nochmal durchdacht werden
	/*// check for overflow
	if(res > 0){
		// restore stack
		push(op2);
		push(op1);
		return E_OVERFLOW;
	}*/
	
	// add result to stack
	// this can't fail because stack had 2 more elements at the start 
	// of this function
	push(res);
	return 0;
}

int reverse(void){
	int op1, op2;
	
	if(get_two_operands(&op1, &op2)){
		return E_MISSING_OPERAND;
	}
	
	// add op1 and op2 back onto the stack in reverse order
	// this can't fail because stack had both of them at the start of
	// this function
	push(op1);
	push(op2);
	return 0;
}

int duplicate(void){
	int op;
	// get operand
	if(pop(&op)){
		return E_MISSING_OPERAND;
	}
	
	// add first back onto the stack
	push(op);
	
	//try to add seccond
	return push(op);
}

int rpn_process_token(Token token){
	if(!token.isOperator){
		return push(token.value);
	} else {
		int res;
		
		// convert operator to method
		switch(token.value){
			case OP_ADD:
				res = add();
				break;
			case OP_SUBTRACT:
				res = subtract();
				break;
			case OP_MULTIPLY:
				res = multiply();
				break;
			case OP_DIVIDE:
				res = divide();
				break;
			/*case OP_PRINT: 	//NEEDS TO BE IMPLEMENTED!
				res = print();
				break;
			case OP_PRINT_ALL:
				res = print_all();
				break;*/
			case OP_CLEAR:
				clear();
				res = 0;
				break;
			case OP_REVERSE:
				res = reverse();
				break;
			case OP_DUPLICATE:
				res = duplicate();
				break;
		}
		
		return res;
	}
}
