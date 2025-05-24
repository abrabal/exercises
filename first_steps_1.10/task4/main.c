#include <stdio.h>

#define CODE 0
#define STRCONST 1
#define SEMICOMM 2
#define LINECOMM 3
#define COMM 4
#define SEMIEXIT 5
#define CHARCONST 6
#define EXIT 7
//i am comment

/*
me
too
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
            case CHARCONST:
            case STRCONST:
                putchar(c);
                break;
            case CODE:
                if (prevstate != SEMIEXIT){
                    putchar(c);
                }
                break;    
        }
        prevstate = newstate;
        
    }

    return 0;
}
