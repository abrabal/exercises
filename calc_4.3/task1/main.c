#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER  '0'
#define MAXOP  100
#define MAXSTACKSIZE  100
#define POW 1
#define SQRT 2
#define SIN 3
#define EXIT -2
#define VAR 4
#define LAST_RESULT 5
#define EXIT_VAR -3


int stack_pointer = 0;
double stack[MAXSTACKSIZE] = {0};
int ins_point = 0;
double top_stack_el[MAXOP] = {0};
double varriables_arr[26] = {0};
int variable = 0;
double lres = 0;

void push(double number){
    stack[stack_pointer] = number;
    stack_pointer += 1;
}

double pop(void){
    stack_pointer -= 1;
    return stack[stack_pointer];
}

void clean_stack (void){
    stack_pointer = 0;
    memset(stack, 0, sizeof(stack));
    memset(top_stack_el, 0, sizeof(top_stack_el));
}

void load_from_stack (int n){
    for (int i = 1; i <= n; i++){
        top_stack_el[i - 1] = stack[stack_pointer - i];
    }
}

void reverse_top_stack_el(void){
    double n = 0;
    n = stack[stack_pointer - 1];
    stack[stack_pointer - 1] = stack[stack_pointer - 2];
    stack[stack_pointer - 2] = n;
}

void skip_whspc(char instruction[]){
    while (instruction[ins_point] == ' '){
        ins_point += 1;
    }
}

int get_operation_type(char instruction[]){
    int j = 0;
    int operation = 0;
    char match[MAXOP] = {0};
    
    while (instruction[ins_point] != ' ' && instruction[ins_point] != '\n'){
        match[j] = instruction[ins_point];
        j += 1;
        ins_point += 1;
    }
    operation = ((strcmp("pow", match)) == 0) ? POW : operation;
    operation = ((strcmp("sqrt", match)) == 0) ? SQRT : operation;
    operation = ((strcmp("sin", match)) == 0) ? SIN : operation;
    operation = ((strcmp("lres", match)) == 0) ? LAST_RESULT : operation;

    if (operation == 0){
        operation = match[j - 1];
    }
    return operation;
}

int getop(char instruction[], char number[]){
    int i = 0;
    
    skip_whspc(instruction);

    if(instruction[ins_point] == '\n'){
        return 0;
    }

    if (instruction[ins_point] == '-' && instruction[ins_point + 1] != ' '){
        number[i] = instruction[ins_point];
        ins_point += 1;
        i += 1;
    }

    if(!isdigit(instruction[ins_point]) && instruction[ins_point] != '.'){
        if (instruction[ins_point] >= 'A' && instruction[ins_point] <= 'Z'){
            push(varriables_arr[instruction[ins_point] - 'A']);
            variable = instruction[ins_point];
            return VAR;
        }else if (instruction[ins_point] == '='){
            pop();
            double var = pop();
            varriables_arr[variable - 'A'] = var;
            return EXIT_VAR;
            
        }else {
            return get_operation_type(instruction);
        }
    }
    while (isdigit(instruction[ins_point])){
        number[i] = instruction[ins_point];
        i += 1;
        ins_point += 1;
    }
    if (instruction[ins_point] == '.'){
        number[i] = instruction[ins_point];
        ins_point += 1;
        i += 1;
        while (isdigit(instruction[ins_point])){
            number[i] = instruction[ins_point];
            ins_point += 1;
            i += 1;
        }
    }
    return NUMBER;

}

int main()
{
    char instruction[MAXOP] = {0};
    char number[MAXOP] = {0};
    int type = 0;
    double op2 = 0;
    int ins_length = 0;

    while ((fgets(instruction, sizeof(instruction), stdin)) != NULL){
        ins_length = strlen(instruction);
        while (ins_point < ins_length){
            if(type == -1 || type == EXIT || type == EXIT_VAR){
                break;
            }
            type = getop(instruction, number);
            switch(type){
                case NUMBER:
                    push(atof(number));
                    memset(number, 0, sizeof(number));
                    break;
                case '+':
                    push (pop() + pop());
                    break;
                case '*':
                    push (pop() * pop());
                    break;
                case '-':
                    op2 = pop();
                    push (pop() - op2);
                    break;
                case '/':
                    op2 = pop();
                    if (op2 == 0){
                        type = -1;
                        clean_stack();
                        break;
                    }
                    push (pop() / op2);
                    break;
                case '%':
                    op2 = pop();
                    if(op2 == 0){
                        type = -1;
                        clean_stack();
                        break;
                    }
                    push (fmod (pop(), op2));
                    break;
                case POW:
                    op2 = pop();
                    push(pow(pop(), op2));
                    break;
                case SQRT:
                    push (sqrt(pop()));
                    break;
                case SIN:
                    push (sin(pop()));
                    break;
                case VAR:
                    ins_point += 1;
                    break;
                case LAST_RESULT:
                    push (lres);
                    break;
                case EXIT:
                    break;
                case EXIT_VAR:
                    type = EXIT_VAR;
                    break;
                default:
                    lres = pop();
                    printf("%f\n", lres);
                    clean_stack();
                    type = EXIT;
                    break;
            }
        }
        ins_point = 0;
        if (type == EXIT_VAR){
            type = 0;
            continue;
        }
        if(type == -1){
            printf("zero divisiors\n");
        }
        type = 0;
    }


    return 0;
}
