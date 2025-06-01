#include <stdio.h>
#include <string.h>

#define LIMIT 1000

void convert_whitespace_to_char(char source_str[], char dest_str[]){
    int line_length = strlen(source_str);
    int j = 0;
    
    for(int i = 0; i < line_length; i++){
        switch (source_str[i]){
            case '\n':
                dest_str[j] = '\\';
                dest_str[j + 1] = 'n';
                j += 2;
                break;
            case ' ':
                dest_str[j] = '\\';
                dest_str[j + 1] = 's';
                j += 2;
                break;
            default:
                dest_str[j] = source_str[i];
                j++;
                break;

        }
    }
}

int main()
{
    char string1[LIMIT] = {0};
    char string2[LIMIT] = {0};

    while(1){
        if (fgets(string1, sizeof(string1), stdin) == NULL){
            break;
        }
        convert_whitespace_to_char(string1, string2);
        printf("formated string = %s\n", string2);
    }

    return 0;
}