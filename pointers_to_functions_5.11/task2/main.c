#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LIMIT 1000
#define FLAG_LIM 10
#define FLAG_COUNT 4

int f1 = 0;
int f2 = 0;
int f3 = 0;
int f4 = 0;

int *arr[FLAG_LIM];
int arr_num = 0;

void parser(char *str, int i){

    if (isdigit(str[0])){
        arr[i][0] += atoi(str);
    }
    if (strcmp(str, "-n") == 0){
        arr[i][1] += 1;
    }
    if (strcmp(str, "-r") == 0){
        arr[i][2] += 1;
    }
    if (strcmp(str, "-d") == 0){
        arr[i][3] += 1;
    }
}

int comp_fun(const void *el1, const void *el2){
    int *elem1 = *(int **)el1;
    int *elem2 = *(int **)el2;

    if (*elem1 < *elem2){
        return -1;
    }
    if (*elem1 > *elem2){
        return 1;
    }
    return 0;

}

int main(int argc, char *argv[])
{
    for (int i = 0; i < FLAG_LIM; i++){
        arr[i] = malloc(FLAG_COUNT * sizeof(int));
        for (int j = 0; j < FLAG_COUNT; j++){
            arr[i][j] = 0;
        }
    }
    
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-f") == 0){
            arr_num += 1;
            continue;
        }
        parser(argv[i], arr_num);
    }
    qsort(arr, arr_num, sizeof(int *), comp_fun);

    for (int i = 0; i < FLAG_LIM; i++){
        for (int j = 0; j < FLAG_COUNT; j++){
            printf("%d ", arr[i][j]);
            if (j == (FLAG_COUNT - 1)){
                printf("\n");
            }
        }
        free(arr[i]);
    }

    }