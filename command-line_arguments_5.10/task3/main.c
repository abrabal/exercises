#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LIMIT 1000
#define DEFAULT_SETTINGS 1
#define VALID_KEYS_NUM 2
#define ERROR_CODE -1
#define WORKING_CODE 1

char *lines[LIMIT];
int num_lines = 0;

void store_lines(char *line)
{
    int line_length = 0;

    line_length = strlen(line);

    *(lines + num_lines) = malloc(line_length + 1);
    strcpy(*(lines + num_lines), line);
    num_lines += 1;
}

int main(int argc, char *argv[])
{
    char line[LIMIT] = {0};

    int lines_to_print = 0;
    int error_check = WORKING_CODE;

    while(1){
        if (fgets(line, sizeof(line), stdin) == NULL){
            break;
        }
        line[strcspn(line, "\n")] = '\0';
        store_lines(line);
    }

    if (argc == DEFAULT_SETTINGS){
        lines_to_print = num_lines;
    } else if (argc == VALID_KEYS_NUM){
        if (*argv[1] == '-'){
            int length = strlen(argv[1]);
            for (int i = 1; i < length; i++){
                if (*(argv[1] + i) < '0' || *(argv[1] + i) > '9'){
                    printf("ERROR: unallowed symbols in key, sets to default\n");
                    error_check = ERROR_CODE;
                    break;
                }
            }
            lines_to_print = (error_check == WORKING_CODE) ? atoi(argv[1] + 1) : num_lines;
            if (error_check == WORKING_CODE && lines_to_print > num_lines){
                printf("ERROR: too much lines too print, sets to default\n");
                lines_to_print = num_lines;
            }
        } else {
            printf("ERROR: invalid key, sets to default\n");
            lines_to_print = num_lines;
        }
    } else {
        printf("ERROR: too much keys, sets to default\n");
        lines_to_print = num_lines;
    }

    for (int i = lines_to_print, j = 1; i > 0; i--, j++){
        printf("%s\n", *(lines + (num_lines - j)));
    }

    for (int i = 0; i < num_lines; i++) {
        free(*(lines + i));
    }


    return 0;
}