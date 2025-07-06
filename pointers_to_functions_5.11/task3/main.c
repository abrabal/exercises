#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LIMIT 1000
#define CASE_SWAP 32
#define KEY_LIM 20
#define FLAGS_NUM 5

#define FIELD_NUMBER 0
#define NUMBER_SORT 1
#define REVERSE_SORT 2
#define CASE_NSENS_SORT 3
#define DIRECT_ORDER_SORT 4

int n = 1;

char *pointer_arr[LIMIT];
int pointer_num = 0;

int *flags_arr[KEY_LIM];
int flags_arr_num = 0;

int reverse_flag = 0;
int basic_sort = 0;
int case_sens = 0;
int direct_order_flag = 0;
int field_num = 0;
int field_sort_flag = 0;

void adjust_keys(int n);
int comparator(char *str1, char *str2);

void set_keys_structure(){
    for (int i = 0; i < KEY_LIM; i++){
        flags_arr[i] = malloc(FLAGS_NUM * sizeof(int));
        for (int j = 0; j < FLAGS_NUM; j++){
            flags_arr[i][j] = 0;
        }
    }
}

void format_string(char *str){
    char buf_str[LIMIT] = {0};
    int str_len = strlen(str);
    for (int i = 0, j = 0; i < str_len; i++){
        if (str[i] >= 'a' && str[i] <= 'z'){
            buf_str[j] = str[i];
            j++;
            continue;
        }
        if (str[i] >= 'A' && str[i] <= 'Z'){
            buf_str[j] = str[i];
            j++;
            continue;
        }
        if (str[i] >= '0' && str[i] <= '9'){
            buf_str[j] = str[i];
            j++;
            continue;
        }
        if (str[i] == ' '){
            buf_str[j] = str[i];
            j++;
            continue;
        }
    }
    strcpy(str, buf_str);
}

void get_field(char *str){
    int act_field = 0;
    unsigned i;
    char buf_str[strlen(str) + 1];
    for (i = 0; i < strlen(str); i++){
        if (str[i] == '\0'){
            break;
        }
        if (str[i] != ' '){
            act_field += 1;
            if (act_field >= field_num){
                break;
            }
            while (str[i] != ' '){
                if (str[i] == '\0'){
                    break;
                }
                i++;
            }
        }
    }
    if (i > strlen(str)){
        printf("ERROR: string has only %d fields\n", act_field);
        exit(0);
    }
    int j;
    for (j = 0; str[i] != ' '; j++, i++){
        if (str[i] == '\0'){
            break;
        }
        buf_str[j] = str[i];
    }
    buf_str[j] = '\0';
    strcpy(str, buf_str);
}

int string_compare_ncase (char *str1, char *str2){
    char buf_str1[strlen(str1) + 1];
    char buf_str2[strlen(str2) + 1];

    strcpy(buf_str1, str1);
    strcpy(buf_str2, str2);

    if (direct_order_flag == 1){

        format_string(str1);
        format_string(str2);
    }
    int state = 0;
    int str_len = strlen(str1);
    for (int i = 0; i < str_len; i++){
        char str1_char = str1[i];
        char str2_char = str2[i];
        if (str1[i] >= 'A' && str1[i] <= 'Z'){
            str1_char = str1[i] + CASE_SWAP;
        }
        if (str2[i] >= 'A' && str2[i] <= 'Z'){
            str2_char = str2[i] + CASE_SWAP;
        }
        state = str1_char - str2_char;
        if (state != 0){
            break;
        }
    }

    if (direct_order_flag == 1 || field_sort_flag == 1){
        strcpy(str1, buf_str1);
        strcpy(str2, buf_str2);
    }

    if (state < 0){
        return -1;
    }
    if (state > 0){
        return 1;
    }

    return 0;
    
}

int numcmp(const void *str1_p, const void *str2_p){
    char *str1 = *(char **)str1_p;
    char *str2 = *(char **)str2_p;

    int sort_res = 0;

    char buf_str1[strlen(str1) + 1];
    char buf_str2[strlen(str2) + 1];

    strcpy(buf_str1, str1);
    strcpy(buf_str2, str2);

    if (field_sort_flag == 1){
        get_field(str1);
        get_field(str2);
    }

    if (direct_order_flag == 1){

        format_string(str1);
        format_string(str2);
    }

    double v1 = atof(str1);
    double v2 = atof(str2);

    if (direct_order_flag == 1 || field_sort_flag == 1){
        strcpy(str1, buf_str1);
        strcpy(str2, buf_str2);
    }

    if (v1 < v2){
        sort_res = -1;
    }
    if (v1 > v2){
        sort_res = 1;
    }
    if (v1 == v2){
        sort_res = 0;
    }
    sort_res *= (reverse_flag == 0) ? sort_res : -1;

    if (sort_res == 0 && flags_arr_num > 0){
        n += 1;
        sort_res = comparator(str1, str2);
    }

    return sort_res;
}

int string_compr (const void *str1_p, const void *str2_p){
    char *str1 = *(char **)str1_p;
    char *str2 = *(char **)str2_p; 

    char buf_str1[strlen(str1) + 1];
    char buf_str2[strlen(str2) + 1];

    strcpy(buf_str1, str1);
    strcpy(buf_str2, str2);

    if (field_sort_flag == 1){
        get_field(str1);
        get_field(str2);
    }

    if (direct_order_flag == 1){
        format_string(str1);
        format_string(str2);
    }

    int sort_res = (case_sens == 0) ? strcmp(str1, str2) : string_compare_ncase(str1, str2);
    sort_res = (reverse_flag == 0) ? sort_res : sort_res * -1; 

    if (direct_order_flag == 1 || field_sort_flag == 1){
        strcpy(str1, buf_str1);
        strcpy(str2, buf_str2);
    }

    if (sort_res == 0 && flags_arr_num > 0){
        n += 1;
        sort_res = comparator(str1, str2);
    }

    return sort_res;
}

int comparator(char *str1, char *str2){
    if (n > flags_arr_num){
        return 0;
    }
    int sort_res = 0;
    adjust_keys(n);
    if (basic_sort == 0){
        sort_res = string_compr(&str1, &str2);
    } else {
        sort_res = numcmp(&str1, &str2);
    }
    return sort_res;
}

void write_lines(char *lines){
    pointer_arr[pointer_num] = malloc(strlen(lines) + 1);
    strcpy(pointer_arr[pointer_num], lines);
    pointer_num += 1;
}

void parse_com_input(char *str, int field_num){
    if (isdigit(str[0])){
        flags_arr[field_num][0] += atoi(str);
    }
    if (strcmp(str, "--field") == 0){
        flags_arr[field_num][FIELD_NUMBER] += 1;
    }
    if (strcmp(str, "-n") == 0){
        flags_arr[field_num][NUMBER_SORT] += 1;
    }
    if (strcmp(str, "-r") == 0){
        flags_arr[field_num][REVERSE_SORT] += 1;
    }
    if (strcmp(str, "-f") == 0){
        flags_arr[field_num][CASE_NSENS_SORT] += 1;
    }
    if (strcmp(str, "-d") == 0){
        flags_arr[field_num][DIRECT_ORDER_SORT] += 1;
    }
}

int comp_fun_sorting_key_structure(const void *el1, const void *el2){
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

void sort_arr(){
    if (field_sort_flag == 0){
        if (basic_sort == 0){
            qsort(pointer_arr, pointer_num, sizeof(char *), string_compr);
        } else {
            qsort(pointer_arr, pointer_num, sizeof(char *), numcmp);
        }
        return;
    }
    if (field_sort_flag == 1){
        if (basic_sort == 0){
            qsort(pointer_arr, pointer_num, sizeof(char *), string_compr);
        } else {
            qsort(pointer_arr, pointer_num, sizeof(char *), numcmp);
        }
        return;
    }
}

void adjust_keys(int sorting_field){
    if (flags_arr_num == 0){
        field_num = flags_arr[0][FIELD_NUMBER];
        basic_sort = flags_arr[0][NUMBER_SORT];
        reverse_flag = flags_arr[0][REVERSE_SORT];
        case_sens = flags_arr[0][CASE_NSENS_SORT];
        direct_order_flag = flags_arr[0][DIRECT_ORDER_SORT];
        field_sort_flag = 0;
        sort_arr();
        return;
    }
    if (flags_arr_num > 0){
        field_sort_flag = 1;
        field_num = flags_arr[sorting_field][FIELD_NUMBER];
        basic_sort = flags_arr[sorting_field][NUMBER_SORT];
        reverse_flag = flags_arr[sorting_field][REVERSE_SORT];
        case_sens = flags_arr[sorting_field][CASE_NSENS_SORT];
        direct_order_flag = flags_arr[sorting_field][DIRECT_ORDER_SORT];
        sort_arr();
    }
}

int main(int argc, char *argv[])
{
    char line[LIMIT] = {0};

    set_keys_structure();
    
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "--field") == 0){
            flags_arr_num += 1;
            continue;
        }
        parse_com_input(argv[i], flags_arr_num);
    }

    qsort(flags_arr, flags_arr_num + 1, sizeof(int *), comp_fun_sorting_key_structure);

    for (int i = 0; i <= flags_arr_num; i++){
        for(int j = 0; j < FLAGS_NUM; j++){
            printf("%d ", flags_arr[i][j]);
        }
        printf("\n");
    }

    printf("_____________________________\n");

    while(1){
        if (fgets(line, sizeof(line), stdin) == NULL){
            break;
        }
        line[strcspn(line, "\n")] = '\0';
        write_lines(line);
    }

    adjust_keys(n);


    for(int i = 0; i < pointer_num; i++){
        printf("%s\n", pointer_arr[i]);
        free(pointer_arr[i]);
    }

    return 0;
}