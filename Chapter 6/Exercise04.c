#include <stdio.h>

#define WORDSIZ 128

struct list {
	char *word;
	int count;

	struct list *next;
};

struct list *add_list(struct list *, char []);
void print_list(struct list *);
int getword(char [], int );

int main(void)
{
	char word[WORDSIZ];
	struct list *first = NULL;

	while (getword(word, WORDSIZ) != EOF)
		first = add_list(first, word);

	print_list(first);

	return 0;
}

#include <ctype.h>

int getword(char word[], int maxlen)
{
	int c;
	char *w = word;

	while (!isalpha(c = getchar()))
		if (c == EOF) return EOF;

	for (*w++ = c; --maxlen > 0; w++)
		if (!isalpha(*w = getchar())) {
			ungetc(*w, stdin);
			break;
		}

	*w = '\0';

	return word[0];
}

#include <stdlib.h>
#include <string.h>

struct list *add_list(struct list *first, char word[])
{
	struct list *cur, *prev, *new_node;
	int comp;
	char *strdup(const char *);

	new_node = malloc(sizeof(struct list));
	if (new_node == NULL)
		return NULL;

	for (prev = NULL, cur = first;
		 cur != NULL && (comp = strcmp(cur->word, word)) > 0;
		 prev = cur, cur = cur->next) ;

	if (cur == NULL) {
		new_node->word = strdup(word);
		new_node->count = 1;
		new_node->next = NULL;

		if (prev == NULL)
			first = new_node;
		else
			prev->next = new_node;
	} else {
		if (comp == 0) {
			cur->count++;
			return first;
		}

		new_node->word = strdup(word);
		new_node->count = 1;
		new_node->next = cur;

		if (prev)
			prev->next = new_node;
		else
			first = new_node;
	}
	
	return first;
}

void print_list(struct list *first)
{
	while (first != NULL) {
		printf("%4d\t%s\n", first->count, first->word);
		first = first->next;
	}
}
