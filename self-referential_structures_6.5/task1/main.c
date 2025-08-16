#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_LEN 1000
#define MAX_VAR_NAMES 100
#define VAR_TYPE 100
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

char *variable_types[2] = {
    "int",
    "char",
};
int type_occur_flag = 0;

struct t_node {
    char *var_type;
    char *var_names[MAX_VAR_NAMES];
    int var_names_p;
    struct t_node *left;
    struct t_node *right;
};

int parse_input(char *var_type, char *curr_var_names[], int *p);
int getch(void);
void ungetch(int c);
int getword(char *word);
void skip_parent(int c);
struct t_node *talloc(void);
struct t_node *addtree(struct t_node *root, char *curr_var_names[], char *var_type, int curr_var_names_size);
void treeprint(struct t_node *root, int n, char *comp_arr);
char *string_duplicate(char *);
void freetree(struct t_node *root);
void sorttree(struct t_node *root);
int string_compare(const void *str1, const void *str2);

int main()
{
    int n = 2;
    struct t_node *root;
    char *curr_var_names[MAX_VAR_NAMES];
    char var_type[VAR_TYPE] = {0};
    int pointer = 0;
    char comp_arr[MAX_WORD_LEN];

    root = NULL;

    while (1){
        if (parse_input(var_type, curr_var_names, &pointer) == EOF){
            break;
        }
        root = addtree(root, curr_var_names, var_type, pointer);
        for (int i = 0; i < pointer; i++) {
            free(curr_var_names[i]);
        }
        //printf("\ntype = %s : ", var_type);
        /*for (int i = 0; i < pointer; i++){
            printf("%s,", curr_var_names[i]);
            free(curr_var_names[i]);
        }*/
    }
    strncpy(comp_arr, root->var_names[0], n);
    printf("arr for comp = %s\n", comp_arr);
    sorttree(root);
    treeprint(root, n, comp_arr);
    freetree(root);

    return 0;
}

int parse_input(char *var_type, char *curr_var_names[], int *p)
{
    char word[MAX_WORD_LEN] = {0};
    int curr_var_names_point = 0;
    type_occur_flag = 0;
    int *point = p;
    while (1){
        int state = getword(word);
        if (state == ';' && type_occur_flag == 1){
            break;
        }
        if (state == EOF){
            return EOF;
        }
        if (type_occur_flag == 1 && word[0] != '\0'){
            curr_var_names[curr_var_names_point] = malloc(strlen(word) + 1);
            strcpy(curr_var_names[curr_var_names_point], word);
            curr_var_names_point += 1;
            word[0] = '\0';
        }
        if (type_occur_flag == 0){
            for (int i = 0; i < 2; i++){
                if(strcmp(word, variable_types[i]) == 0){
                    type_occur_flag = 1;
                    strcpy(var_type, word);
                    word[0] = '\0';
                    break;
                }
            }
        }
    }
    *point = curr_var_names_point;
    return 0;
}

int getword(char *word){
    int c = getch();
    while(isspace(c) || c == ','){
        c = getch();
    }
    if (c == '[' || c == '('){
        skip_parent(c);
        c = getch();
    }
    if (!isalpha(c) && c != '*' && c != '_'){
        return c;
    }
    *word++ = c;
    for (; ; word++){
        *word = getch();
        if (*word == EOF){
            break;
        }
        if (!isalpha(*word) && *word != '*' && *word != '_'){
            ungetch(*word);
            *word = '\0';
            return *word;
        }
    }
    return 0;
}

void skip_parent(int c){
    int square = 0;
    int round = 0;

    if (c == '[')
        square = 1;
    if (c == '(')
        round = 1;
    
    while (1){
        c = getch();
        if (square == 1){
            if (c == ']')
                return;
        }
        if (round == 1){
            if (c == ')')
                return;
        }
    }
}

struct t_node *addtree(struct t_node *root, char *curr_var_names[], char *var_type, int current_var_names_size){
    if (root == NULL){
        root = talloc();
        root->var_names_p = 0;
        root->var_type = string_duplicate(var_type);
        for (int i = 0; i < current_var_names_size; i++, root->var_names_p++){
            root->var_names[root->var_names_p] = string_duplicate(curr_var_names[i]);
        }
        root->left = root->right = NULL;
    } else if (strcmp(root->var_type, var_type) == 0){
        for(int i = 0; i < current_var_names_size; i++, root->var_names_p++){
            root->var_names[root->var_names_p] = string_duplicate(curr_var_names[i]);
        }
    } else if (strcmp(root->var_type, var_type) < 0){
        root->left = addtree(root->left, curr_var_names, var_type, current_var_names_size);
    } else {
        root->right = addtree(root->right, curr_var_names, var_type, current_var_names_size);
    }
    return root;
}

void treeprint(struct t_node *root, int n, char *comp_arr)
{
    if (root != NULL)
    {
        treeprint(root->left, n, comp_arr);
        printf("type = %s : ", root->var_type);
        for(int i = 0; i < root->var_names_p; i++){
            if (strncmp(comp_arr, root->var_names[i], n) == 0){
                printf("%s, ", root->var_names[i]);
            }
        }
        printf("\n----------------\n");
        treeprint(root->right, n, comp_arr);
    }
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)

{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters volatile \n");
    else
        buf[bufp++] = c;
}

struct t_node *talloc(void)
{
    return (struct t_node *) malloc(sizeof(struct t_node));
}
char *string_duplicate(char *s)
{
    char *p;

    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

void freetree(struct t_node *root)
{
    if (root != NULL)
    {
        freetree(root->left);
        freetree(root->right);

        for (int i = 0; i < root->var_names_p; i++) {
            free(root->var_names[i]);
        }

        free(root->var_type);
        free(root);
    }
}

void sorttree (struct t_node *root)
{
    if (root != NULL){
        sorttree(root->left);
        qsort(root->var_names, root->var_names_p, sizeof(char *), string_compare);
        sorttree(root->right);
    }

}

int string_compare(const void *str1, const void *str2)
{
    char *string1 = *(char **)str1;
    char *string2 = *(char **)str2;

    return strcmp(string1, string2);
}

