#include <stdio.h>
#include <string.h>

#define LIMIT 1000

int expand_string(char source_string[], char dest_string[]){
    int line_length = strlen(source_string);
    int i = 0;
    int k = 0;
    int start_pos = 0;
    int step = 0;
    int tail_check = 1;

    if (source_string[0] == '-'){
        i += 1;
        dest_string[k] = '-';
        k += 1;
        start_pos += 1;
    }
    if (source_string[line_length - 2] == '-'){
        source_string[line_length - 2] = ' ';
        source_string[line_length - 1] = '-';
        tail_check = -1;
    }
    for (; i < line_length - 1; i += step){
        if( source_string[i + 2] == '\n'){
            break;
        }
        if (source_string[i + 1] == '-'){
            step = 2;
        } else if (source_string[i + 1] != '-'){
            for (int j = source_string[start_pos]; j <= source_string[i]; j++, k++){
                dest_string[k] = j;
            }
            step = 1;
            start_pos = (i + 1);
        } else {
            return -1;
        }
    }
    if (tail_check == -1){
        dest_string[strlen(dest_string)] = '-';
    }

    return 0;
}

int main()
{
    char source_string[LIMIT] = {0};
    char dest_string[LIMIT] = {0};

    while (1){
        if (fgets(source_string, sizeof(source_string), stdin) == NULL){
            break;
        }
        if(expand_string(source_string, dest_string) == -1){
            printf("Invalid notation\n");
            break;
        }
        printf("%s\n", dest_string);
        
        memset(source_string, 0, sizeof(source_string));
        memset(dest_string, 0, sizeof(dest_string));
    }
    return 0;
}