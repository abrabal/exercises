#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LIMITS 1000

int read_line(char *store[], char *arr){
    char line[LIMITS] = {0};
    //char *p;
    int i = 0;

    while(fgets(line, sizeof(line), stdin)){
        line[strcspn(line, "\n")] = '\0';
        //p = malloc(strlen(line) + 1);
        strcpy(arr, line);
        store[i] = arr;
        arr += strlen(line) + 1;
        i++;
    }

    return i;
}

int cmpstr(const void *a, const void *b) {
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;
    return strcmp(s1, s2);
}

void write_lines(char *pointers[], int num_lines){
    for (int i = 0; i < num_lines; i++){
        printf("%s\n", pointers[i]);
    }
}


int main()
{
    char *pointers[LIMITS] = {0};
    char arr[LIMITS] = {0};
    int num_lines = 0;

    num_lines = read_line(pointers, arr);
    qsort(pointers, num_lines, sizeof(char *), cmpstr);
    write_lines(pointers, num_lines);

    return 0;
}