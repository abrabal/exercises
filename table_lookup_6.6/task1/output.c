#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASHSIZE 101
#define NOT_SUCH_EL 0
#define SUC_DELETE 1
#define MAX_WORD_LEN 100
#define MAX_DEFN_LEN 1000
#define BUFSIZE 100

char buf[100];
int bufp = 0;

struct n_list {
    struct n_list *next;
    char *name;
    char *defn;
};

struct n_list *hashtab[101];

unsigned hash (char *str);
struct n_list *lookup(char *str, struct n_list **prev_p); 
char *string_dup(char *s);
int undef(char *name);
void free_list(struct n_list *np);
int getword(char *word);
void getname(char *name);
void get_defn(char *defn);
struct n_list *install(char *name, char *defn);
int getch(void);
void ungetch(int c);

int main()
{
    char word[100];
    char name[100];
    char defn[1000];
    char *define = "define";
    int end_state = 0;
    struct n_list *np = NULL;

    while (1){
        end_state = getword(word);
        if (end_state == EOF){
            printf("%s", word);
            break;
        }
        if (strcmp(word, define) == 0){
            printf("%s", word);
            getname(name);
            printf("%s", name);
            get_defn(defn);
            np = install(name, defn);
            continue;
        }
        np = lookup(word, NULL);
        if (np == NULL){
            printf("%s", word);
        }else {
            printf("%s", np->defn);
        }

    }
    /*np = lookup("101", NULL);
    printf("\n\n\nname = %s\ndefn = %s\n", np->name, np->defn);*/

    for (int i = 0; i < 101; i++){
        free_list(hashtab[i]);
    }
    return 0;
}

unsigned hash (char *str)
{
    unsigned hashval = 0;

    for (; *str != '\0'; str++){
        hashval = *str + 31 * hashval;
    }
    return hashval % 101;
}

struct n_list *lookup(char *str, struct n_list **prev_p)
{
    struct n_list *prev_point = NULL;
    struct n_list *np;
    for (np = hashtab[hash(str)]; np != NULL; prev_point = np, np = np->next){
        if (strcmp(str, np->name) == 0){
            if (prev_p != NULL){
                *prev_p = prev_point;
                }
            return np;
        }
    }
    if (prev_p != NULL){
        *prev_p = NULL;
    }
    return NULL;
}

char *string_dup(char *s)
{
	char *p;
	p = (char *)malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

struct n_list *install(char *name, char *defn)
{
    struct n_list *np;
    unsigned hashval = 0;
    if ((np = lookup(name, NULL)) == NULL){
        np = (struct n_list *) malloc(sizeof(*np));
        if(np == NULL || (np->name = string_dup(name)) == NULL){
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }else {
        free((void *) np->defn);
    }
    if ((np->defn = string_dup(defn)) == NULL){
        return NULL;
    }
    return np;
}

int undef(char *name)
{
    struct n_list *np;
    struct n_list *prev_p;
    unsigned hashval = hash(name);
    np = lookup(name, &prev_p);
    if (np == NULL){
        return 0;
    }
    if (prev_p == NULL){
        hashtab[hashval] = np->next;
        free(np->name);
        free(np->defn);
        free(np);
        return 1;
    }
    prev_p->next = np->next;
    free(np->name);
    free(np->defn);
    free(np);
    return 1;
}

void free_list(struct n_list *np)
{
    struct n_list *curr_p;
    if (np != NULL){
        curr_p = np;
        np = np->next;
        free(curr_p->name);
        free(curr_p->defn);
        free(curr_p);
        free_list(np);
    }
}

int getword(char *word)
{
    word[0] = '\0';
    int c = 0;
    c = getch();
    while (isspace(c)){
        putchar(c);
        c = getch();
    }
    while (!isalpha(c) && c != '_'){
        if (c == EOF){
            *word = '\0';
            return EOF;
        }
        putchar(c);
        c = getch();
    }

    for (; isalpha(c) || c == '_'; ){
        if (c == EOF){
            *word = '\0';
            return c;
        }
        *word++ = c;
        c = getch();
    }
    ungetch(c);
    *word = '\0';
    return c;
}

void getname(char *name)
{
    int c = getch();
    while (isspace(c)){
        putchar(c);
        c = getch();
    }
    for (; !isspace(c); ){
        *name++ = c;
        c = getch();
    }
    *name = '\0';
    ungetch(c);
    return;
}

void get_defn(char *defn)
{
    int c = getch();
    int check_new_line = 0;
    while (isspace(c)){
        putchar(c);
        c = getch();
    }
    while (1){
        *defn++ = c;
        putchar(c);
        c = getch();
        if (c == '\n'){
            check_new_line = 0;
        }
        if (c == '\\'){
            putchar(c);
            check_new_line = c;
            c = getch();
            if (c != '\n'){
                *defn++ = check_new_line;
            }
        }
        if (c == '\n' && check_new_line != '\\'){
            *defn = '\0';
            ungetch(c);
            return;
        }
    }
    return;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)

{
    if (bufp >= 100)
        printf("ungetch: too many characters volatile \n");
    else
        buf[bufp++] = c;
}