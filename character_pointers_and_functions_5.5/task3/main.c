#include <stdio.h>
#include <string.h>

#define LIMIT 1000

void copy_to_string (char *source, char *result, int n){
    char *src = source;

    while (n > 0){
        *(src++) = *(result++);
        n--;
    }

    printf("%s\n", source);
}

int compare_strings (char *source, char *result, int n){
    while (n > 0){
        if (*source > *result){
            return 1;
        } else if (*source < *result){
            return -1;
        }
        source++;
        result++;
        n--;
    }
    
    return 0;
}

void concat_strings(char *source, char *dest, int n)
{
    char *dst = dest;
    dst += strlen(dest);
    if (*(dst - 1) == '\n')
    {
        dst -= 1;
    }

    while (*source != '\0' && n > 0)
    {
        *(dst++) = *(source++);
        n--;
    }

    printf("%s\n", dest);
}

int main()
{
    char string1[LIMIT] = {0};
    char string2[LIMIT] = "string";
    int n = 3;

    while (fgets(string1, sizeof(string1), stdin)){
        //copy_to_string (string1, string2, n);

        //printf ("eq status = %d\n", compare_strings(string1, string2, n));

        //concat_strings(string1, string2, n);

    }

    return 0;
}