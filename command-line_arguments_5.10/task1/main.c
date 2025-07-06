#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACKSIZE 100
#define ZERO_DIVIZOR -1
#define INVAL_ARG -2

double stack[STACKSIZE] = {0};
int stack_point = 0;

void push (double value){
    stack[stack_point] = value;
    stack_point += 1;
}

double pop (void){
    stack_point -= 1;

    return stack[stack_point];
}

double get_operand(char *string, int *exit){
    if (*string >= '0' && *string <= '9'){
        return atof(string);
    } else {
        *exit = INVAL_ARG;
        return 0;
    }
}

void clean_stack(void){
    stack_point = 0;
}

int main (int argc, char *argv[])
{
    double result = 0;
    double sec_op = 0;
    int exit_code = 0;

    for (int i = 1; i < argc; i++){
        switch(**(++argv)){
            case '+':
                push (pop() + pop());
                break;
            case '-':
                sec_op = pop();
                push (pop() - sec_op);
                break;
            case '*':
                push (pop() * pop());
                break;
            case '/':
                sec_op = pop();
                if (sec_op != 0){
                    push(pop() / sec_op);
                    break;
                } else {
                    exit_code = ZERO_DIVIZOR;
                    break;
                }
                break;
            default:
                push (get_operand(*argv, &exit_code));
                break;
        }
        if (exit_code == ZERO_DIVIZOR){
            break;
        }
        if (exit_code == INVAL_ARG){
            break;
        }
    }
    if (stack_point > 0){
        result = pop();
    }
    if(exit_code == ZERO_DIVIZOR){
        printf("ERROR: can not divide by zero\n");
        clean_stack();
    } else if (exit_code == INVAL_ARG){
        printf("ERROR: invalid argument\n");
        clean_stack();
    } else {
        printf("result = %f\n", result);
        clean_stack();
    }
    

    return 0;
}