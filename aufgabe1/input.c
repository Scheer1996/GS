#include "input.h"
#include "keypad.h"

#define FAKTOR 10

void input_init(void){
    Make_Touch_Pad();
}

char get_char(void){
    int code = Get_Touch_Pad_Input();
    return (char)code;
}

Token get_operator_token(char ch){
    Token t;
    t.isOperator = 1;
    switch(ch){
        case '+':
            t.value = OP_ADD;
            break;
        case '-':
            t.value = OP_SUBTRACT;
            break;
    }
    
    return t;    
}

Token input_get_next_token(void){
    static int isTokenQueued;
    static char ch;
    
    if(isTokenQueued){
        isTokenQueued = 0;
        return get_operator_token(ch);
    } else {
        Token token;
        int isReadingNumber = 0;
        int number = 0;
        
        while(1){
            ch = get_char();
            if(ch >= '0' && ch <= '9'){
                isReadingNumber = 1;
                number *= FAKTOR;
                number += (ch - '0');
            } else {
                if(!isReadingNumber){
                    token = get_operator_token(ch);
                } else {
                    isTokenQueued = (ch != ' ');
                }
                break;
            }
        }
        
        if(isReadingNumber){
            token.isOperator = 0;
            token.value = number;
        }
        
        return token;
    }
    
}
