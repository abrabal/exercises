#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_LEN 100

int size_of_tree = 0;
int tree_arr_point = 0;

struct t_node {
	char *word;
    int freq_in_lines;
	struct t_node *left;
	struct t_node *right;
};

int getword(char *word);
struct t_node *addtree(struct t_node *root, char *word);
struct t_node *talloc(void);
char *string_dup(char *s);
void get_tree_size(struct t_node *root);
void freetree(struct t_node *root);
void tree_to_arr(struct t_node *root, struct t_node *flat_tree);
int freq_compare(const void *, const void *);

int main()
{
    struct t_node *root;
    char word[MAX_WORD_LEN];
    root = NULL;
    int c = 0;

    while (1){
        c = getword(word);
        if (isalpha(word[0])){
            root = addtree(root, word);
        }
        if (c == EOF){
            break;
        }
    }
    get_tree_size(root);
    struct t_node *flat_tree = malloc(sizeof(struct t_node) * size_of_tree);
    tree_to_arr(root, flat_tree);
    qsort(flat_tree, size_of_tree, sizeof(struct t_node), freq_compare);
    for (int i = 0; i < size_of_tree; i++){
        printf("word = %s, occurs %d times\n", flat_tree[i].word, flat_tree[i].freq_in_lines);
    }
    freetree(root);
    free(flat_tree);
    return 0;
}

int freq_compare(const void *struct1, const void *struct2)
{
    const struct t_node *first_node = (const struct t_node *)struct1;
    const struct t_node *second_node = (const struct t_node *)struct2;
    if (first_node->freq_in_lines > second_node->freq_in_lines){
        return 1;
    }
    if (first_node->freq_in_lines < second_node->freq_in_lines){
        return -1;
    }
    return 0;
}

void tree_to_arr(struct t_node *root, struct t_node *flat_tree)
{
    if (root != NULL){
        tree_to_arr(root->left, flat_tree);

        flat_tree[tree_arr_point] = *root;
        tree_arr_point += 1;
        tree_to_arr(root->right, flat_tree);
    }
}

struct t_node *addtree(struct t_node *root, char *word)
{
    if (root == NULL){
        root = talloc();
        root->word = string_dup(word);
        root->freq_in_lines = 1;
        root->left = NULL;
        root->right = NULL;
    } else if (strcmp(root->word, word) == 0){
        root->freq_in_lines += 1;
    } else if (strcmp(root->word, word) > 0){
        root->right = addtree(root->right, word);
    } else if (strcmp(root->word, word) < 0){
        root->left = addtree(root->left, word);
    }
    return root;
}

void freetree(struct t_node *root){
    if (root != NULL){
        freetree(root->left);
        freetree(root->right);
        free(root->word);
        free(root);
    }
}

void get_tree_size(struct t_node *root)
{
    if (root != NULL){
        get_tree_size(root->left);
        size_of_tree += 1;
        get_tree_size(root->right);
    }
}

int getword(char *word)
{
    int c = getchar();
    while (isspace(c)){
        c = getchar();
    }
    if (!isalpha(c) && c != '\''){
        return c;
    }
    *word++ = c;

    for (; ; word++){
        c = getchar();
        if (!isalpha(c) && c != '\''){
            *word = '\0';
            return c;
        }
        *word = c;
    }

}

struct t_node *talloc(void)
{
	return (struct t_node *)malloc(sizeof(struct t_node));
}

char *string_dup(char *s)
{
	char *p;
	p = (char *)malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}