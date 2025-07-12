#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define MAX_LINE_LEN 1000
#define MAX_LINE_NUM_LEN 1000
#define NOISE_WORDS_NUM 9

int curr_line = 1;

char *noise_words[NOISE_WORDS_NUM] = {
	"the",
	"a",
	"for",
	"this",
	"of",
	"and",
	"are",
	"but",
	"then",
};

int getword(char *word);
int skip_noise_word(char *word);
struct t_node *talloc(void);
char *string_dup(char *s);
struct t_node *addtree(struct t_node *root, char *word);
void treeprint(struct t_node *root);
void freetree(struct t_node *root);

struct t_node {
	char *word;
	int line_occur[MAX_LINE_NUM_LEN];
	int line_occur_p;
	struct t_node *left;
	struct t_node *right;
};

int main()
{
	struct t_node *root;
	char word[MAX_WORD_LEN];
	root = NULL;
	int c = 0;

	while (1){
		c = getword(word);
		if (isalpha(word[0])){
			if (skip_noise_word(word) == 0){
				root = addtree(root, word);
			}
		}
		if (c == '\n'){
			curr_line += 1;
		}
		if (c == EOF){
			break;
		}
	}
	treeprint(root);
	freetree(root);
	return 0;
}

struct t_node *addtree(struct t_node *root, char *word)
{
	int cond = 0;

	if (root == NULL){
		root = talloc();
		root->word = string_dup(word);
		root->line_occur_p = 0;
		root->line_occur[root->line_occur_p] =  curr_line;
		root->left = NULL;
		root->right = NULL;
	} else if (strcmp(word, root->word) == 0){
		for (int i = 0; i <= root->line_occur_p; i++){
			if (root->line_occur[i] == curr_line){
				cond = 1;
				break;
			}
		}
		if (cond == 0){
			root->line_occur_p += 1;
			root->line_occur[root->line_occur_p] = curr_line;
		}
	} else if (strcmp(word, root->word) < 0){

		root->left = addtree(root->left, word);
	} else if (strcmp(word, root->word) > 0){

		root->right = addtree(root->right, word);
	}

	return root;
}

void treeprint(struct t_node *root)
{
	if (root != NULL){
		treeprint(root->left);
		printf("word %s occurs in ", root->word);
		for (int i = 0; i <= root->line_occur_p; i++){
			if (i < root->line_occur_p){
				printf("%d, ", root->line_occur[i]);
			} else {
				printf("%d", root->line_occur[i]);
			}
			
		}
		printf("\n");
		treeprint(root->right);
	}
}

void freetree(struct t_node *root)
{
	if (root != NULL){
		freetree(root->left);
		freetree(root->right);
		free(root->word);
		free(root);
	}
}

int skip_noise_word(char *word)
{
	char buffer_string[strlen(word) + 1];
	strcpy(buffer_string, word); 
	for(int i = 0; (size_t)i < strlen(word); i++){
		word[i] = tolower(word[i]);
	}
	for (int i = 0; i < NOISE_WORDS_NUM; i++){
		if (strcmp(word, noise_words[i]) == 0){
			strcpy(word, buffer_string);
			return -1;
		}
	}
	strcpy(word, buffer_string);
	return 0;
}

int getword(char *word)
{
	word[0] = '\0';
	int c = getchar();
	while(c == ' '){
		c = getchar();
	}
	if (!isalpha(c) && c != '\''){
		return c;
	}
	*word++ = c;
	for(; ; word++){
		c = getchar();
		if(!isalpha(c) && c != '\''){
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