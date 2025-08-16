#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NKEYS (sizeof keytab / sizeof(keytab[0]))

/*struct key {
    char *word;
    int count;
};*/

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
    {"size_t", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

int string_comp(const void *struct1, const void *struct2){
    const struct key *k1 = (const struct key *)struct1;
    const struct key *k2 = (const struct key *)struct2;
    return strcmp(k1->word, k2->word) * -1;
}

/*struct key keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0},
    {"#define", 0},
    {"comment", 0},
};*/

int main()
{
    qsort(keytab, NKEYS, sizeof(struct key), string_comp);

    for (int i = 0; i < (int)NKEYS; i++){
        printf("{\"%s\", %d},\n", keytab[i].word, keytab[i].count);
    }

    return 0;
}
