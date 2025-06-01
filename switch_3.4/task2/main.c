#include <stdio.h>
#include <string.h>

#define LIMIT 1000

int convert_whitespace_to_char(char source_str[], char dest_str[]){
    int line_length = strlen(source_str);
    int j = 0;
    
    for(int i = 0; i < line_length; j++){
        switch (source_str[i]){
            case '\\':
                if (source_str[i + 1] == 't'){
                    dest_str[j] = '\t';
                    i += 2;
                    break;
                } else if (source_str[i + 1] == 'n'){
                    dest_str[j] = '\n';
                    return 0;
                    break;
                } else {
                    dest_str[j] = source_str[i];
                    i++;
                    break;
                }
            default:
                dest_str[j] = source_str[i];
                i++;
                break;
                
        }
    }
    return 0;
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
        printf("formated string = %s", string2);
    }

    return 0;
}