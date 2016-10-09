/** ****************************************************************
 * @file    aufgabe1/rpn.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Implementation for the RPN module
 ******************************************************************
 */
#include "rpn.h"
#include "stack.h"
#include <limits.h>
#include <math.h>

/** ****************************************************************
 * @brief   Retrieves two operands from the stack
 *
 * @param [out] op1 pointer to where the first operand should be written
 * @param [out] op2 pointer to where the second operand should be written
 *
 * @return error code
 * @retval 0 no error
 * @retval E_MISSING_OPERAND could not retrieve two operands
 ******************************************************************
 */
static int get_two_operands(int* op1, int* op2){
	// get first operand
	if(stack_pop(op1)){
		return E_MISSING_OPERAND;
	}
	// get seccond operand
	if(stack_pop(op2)){
		// restore stack
		stack_push(*op1);
		return E_MISSING_OPERAND;
	}
	return 0;
}

/** ****************************************************************
 * @brief   Adds the top two elements of the stack
 *
 * @return error code
 * @retval 0 no error
 * @retval E_MISSING_OPERAND less than two operands on the stack
 * @retval E_OVERFLOW        the addition over- or underflowed the underlying
 *                           @c int.
 ******************************************************************
 */
static int add(void){
	int op1, op2;
	int res;
	
	if(get_two_operands(&op1, &op2)){
		return E_MISSING_OPERAND;
	}
	
	res = op1 + op2;
	// check for overflow
	if( (res < 0 && op1 > 0 && op2 > 0) || (res > 0 && op1 < 0 && op2 < 0) ){
		// restore stack
		stack_push(op2);
		stack_push(op1);
		return E_OVERFLOW;
	}
	
	// add result to stack
	// this can't fail because stack had 2 more elements at the start 
	// of this function
	stack_push(res);
	return 0;
}

/** ****************************************************************
 * @brief   Subtracts the top element of the stack from the one below it.
 *
 * @return error code
 * @retval 0 no error
 * @retval E_MISSING_OPERAND less than two operands on the stack
 * @retval E_OVERFLOW        the subtraction over- or underflowed the
 *                           underlying @c int.
 ******************************************************************
 */
static int subtract(void){
	int op1, op2;
	int res;
	
	if(get_two_operands(&op1, &op2)){
		return E_MISSING_OPERAND;
	}
	
	res = op2 - op1;
	// check for overflow
	if( (op2 < 0 && op1 > 0 && res > 0) || (op2 > 0 && op1 < 0 && res < 0) ){
		// restore stack
		stack_push(op2);
		stack_push(op1);
		return E_OVERFLOW;
	}
	
	// add result to stack
	// this can't fail because stack had 2 more elements at the start 
	// of this function
	stack_push(res);
	return 0;
}

/** ****************************************************************
 * @brief   Multiplies the top two elements of the stack.
 *
 * @return error code
 * @retval 0 no error
 * @retval E_MISSING_OPERAND less than two operands on the stack
 * @retval E_OVERFLOW        the multiplication over- or underflowed the
 *                           underlying @c int.
 ******************************************************************
 */
static int multiply(void){
	int op1, op2;
	int res;
	
	if(get_two_operands(&op1, &op2)){
		return E_MISSING_OPERAND;
	}
	
	res = op1 * op2;
	// check for overflow
	if( fabs(op1) > (LONG_MAX / fabs(op2)) ){
		// restore stack
		stack_push(op2);
		stack_push(op1);
		return E_OVERFLOW;
	}
	
	// add result to stack
	// this can't fail because stack had 2 more elements at the start 
	// of this function
	stack_push(res);
	return 0;
}

/** ****************************************************************
 * @brief   Divides the second element of the stack by the top one.
 *
 * @return error code
 * @retval 0 no error
 * @retval E_MISSING_OPERAND less than two operands on the stack
 * @retval E_DIVIDE_0        the top value was 0, and we don't want to
 *                           divide by 0...
 ******************************************************************
 */
static int divide(void){
	int op1, op2;
	int res;
	
	if(get_two_operands(&op1, &op2)){
		return E_MISSING_OPERAND;
	}
	if(op1 == 0){
		// restore stack
		stack_push(op2);
		stack_push(op1);
		return E_DIVIDE_0;
	}
	
	res = op2 / op1;
	
	// add result to stack
	// this can't fail because stack had 2 more elements at the start 
	// of this function
	stack_push(res);
	return 0;
}

/** ****************************************************************
 * @brief   Reverses the top two elements of the stack.
 *
 * @return error code
 * @retval 0 no error
 * @retval E_MISSING_OPERAND less than two operands on the stack
 ******************************************************************
 */
static int reverse(void){
	int op1, op2;
	
	if(get_two_operands(&op1, &op2)){
		return E_MISSING_OPERAND;
	}
	
	// add op1 and op2 back onto the stack in reverse order
	// this can't fail because stack had both of them at the start of
	// this function
	stack_push(op1);
	stack_push(op2);
	return 0;
}

/** ****************************************************************
 * @brief   Duplicates the top entry of the stack.
 *
 * @return error code
 * @retval 0 no error
 * @retval E_MISSING_OPERAND nothing on the stack
 * @retval E_STACK_OVERFLOW  the stack is full and thus we can't add another
 *                           element to it.
 ******************************************************************
 */
static int duplicate(void){
	int op;
	// get operand
	if(stack_pop(&op)){
		return E_MISSING_OPERAND;
	}
	
	// add first back onto the stack
	stack_push(op);
	
	//try to add seccond
	return stack_push(op);
}

/* ****************************************************************
 * Processes the Token that is passed to it
 ******************************************************************
 */
int rpn_process_token(Token token){
	if(!token.isOperator){
		return stack_push(token.value);
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
				stack_clear();
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
