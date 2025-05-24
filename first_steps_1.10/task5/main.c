#include <stdio.h>

#define CODE 0
#define STRCONST 1
#define SEMICOMM 2
#define LINECOMM 3
#define COMM 4
#define SEMIEXIT 5
#define CHARCONST 6
#define EXIT 7

int square_brackets = 0;
int round_brackets = 0;
int curly_brackets = 0;
//i am comment}}{":":L(()())}

/*
me[[[[]]]]
too{{}}
comment
*/

int code(int c){
    switch (c){
        case '/':
            return SEMICOMM;
        case '\'':
            return CHARCONST;
        case '\"':
            return STRCONST;
        default:
            return CODE;
    }
}

int strconst(int c){
    switch (c){
        case '\"':
            return CODE;
        default:
            return STRCONST;
    }
}

int charconst(int c){
    switch (c){
        case '\'':
            return CODE;
        default:
            return CHARCONST;
    }
}

int semicomment(int c){
    switch (c){
        case '/':
            return LINECOMM;
        case '*':
            return COMM;
        default:
            return CODE;
    }
}

int linecomment(int c){
    switch (c){
        case '\n':
            return CODE;
        default:
            return LINECOMM;
    }
}

int comment(int c){
    switch (c){
        case '*':
            return SEMIEXIT; 
        default:    
            return COMM;
    }
}

int semiexit(int c){
    switch (c){
        case '/':
            return CODE;
        default:
            return COMM;
    }
}

int transition (int state, int c){
    switch (state){
        case CODE:
            return code(c);
        case SEMICOMM:
            return semicomment(c);
        case CHARCONST:
            return charconst(c);
        case STRCONST:
            return strconst(c);
        case LINECOMM:
            return linecomment(c);
        case COMM:
            return comment(c);
        case SEMIEXIT:
            return semiexit(c);
        default:
            printf("ERROR?ERROR?");
            return -1;
    }
}

void count_bracket(int c){
    switch (c){
        case '[':
            square_brackets++;
            break;
        case '{':
            curly_brackets++;
            break;
        case '(':
            round_brackets++;
            break;
        case ']':
            square_brackets--;
            break;
        case '}':
            curly_brackets--;
            break;
        case ')':
            round_brackets--;   
            break;  
        default:
            break;
    }
}

char check (void){
    char result = 0;

    if (round_brackets != 0){
        printf("uneven ( \n");
        result++;
    }
    if (square_brackets != 0){
        printf("uneven [ \n");
        result++;
    }
    if (curly_brackets != 0){
        printf("uneven { \n");
        result++;
    }
    return result;
}

int main()
{   
    int c;
    int newstate, prevstate;
    
    newstate = prevstate = CODE;

    while (1){
        c = getchar();
        if (c == EOF){
            break;
        }
        newstate = transition(prevstate, c);
        switch (newstate){
            case CODE:
                if(prevstate != SEMIEXIT){
                    count_bracket(c);
                }
                break;
        }
        prevstate = newstate;
        
    }
    if (check() == 0){
        printf("Correct\n");
    }

    return 0;
}
