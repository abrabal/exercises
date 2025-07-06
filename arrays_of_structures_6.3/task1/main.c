#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 100
#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0]))

size_t test = 0;

char buf[BUFSIZE];
int bufp = 0;
/* buffer for ungetch */
/* next free position in buf */

int getch(void) /* get a (possibly pushed-back) character size_t */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
/* push character back on input volatile */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters volatile \n");
    else
        buf[bufp++] = c;
}

struct key
{
    char *word;
    int count;
} keytab[] = {
    {"#define", 0},
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"comment", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"int", 0},
    {"size_t", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

int getword(char *, int);
int binsearch(char *, struct key *, int);
/* count C keywords */

void comment_handler(void){
    int c = 0;
    c = getch();
    switch(c){
        case '/':
            while(c != '\n'){
                c = getch();
            }
            break;
        case '*':
            while(1){
                c = getch();
                if (c == '*'){
                    c = getch();
                    if (c == '/'){
                        break;
                    }
                }
            }
            break;
        default:
            ungetch(c);
            break;
    }
}

void str_sym_cnsts_handler(void){
    int c = 0;
    while(1){
        c = getch();
        if (c == '\\'){
        c = getch();
        continue;
        }
        if (c == '\'' || c == '\"'){
            break;
        }
    }
}

int main()
{
    int n;
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF){
        word[strcspn(word, ";")] = '\0';
        if ((n = binsearch(word, keytab, NKEYS)) >= 0)
            keytab[n].count++;
    }

    for (n = 0; n < (int)NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n",
                   keytab[n].count, keytab[n].word);
    return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key *tab, int n)
{
    int cond;
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    c = getch();

    while (isspace(c)){
        c = getch();
    }

    if (c == EOF){
        return EOF;
    }

    if (c == '/'){
        comment_handler();
        c = getch();
    }
    if (c == '\"' || c == '\''){
        str_sym_cnsts_handler();
        c = getch();
    }
    while (isspace(c)){
        c = getch();
    }

    if (!isalnum(c) && c != '#' && c != '_'){
        *w = '\0';
        return c;
    }

    *w++ = c;
    for (; --lim > 0; w++){
        *w = getch();
        if (*w == EOF){
            return EOF;
        }
        if (!isalnum(*w) && *w != '_')
        {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}