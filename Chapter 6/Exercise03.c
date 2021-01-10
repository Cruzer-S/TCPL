#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define WORDSIZ 128
#define NLINES 1

struct list {
	char *word;
	int line_number;

	struct list *next;
};

struct list *add_list(struct list *, char [], int );
void print_list(struct list * );
int getword(char [], int );

int main(void)
{
	struct list *head;
	char word[WORDSIZ];
	int type, line_number;

	for (head = NULL, line_number = 0;
		 (type = getword(word, WORDSIZ)) != EOF; )
	{
		if (type == NLINES) {
			line_number++;
			continue;
		} else {
			head = add_list(head, word, line_number);
		}
	}

	print_list(head);

	return 0;
}

int getword(char word[], int lim)
{
	int c;
	char *w = word;

	while (isspace(c = getchar()))
		if (c == '\n') return NLINES;

	if (c != EOF)
		*w++ = c;

	if (!isalpha(c) || c == '_') {
		*w = '\0';
		return c;
	}

	for (; --lim > 0; w++)
	{
		if (!isalnum(*w = getchar()) && *w != '_') {
			ungetc(*w, stdin);
			break;
		}
	}

	*w = '\0';

	return word[0];
}

#include <string.h>

struct list *lalloc(void);

struct list *add_list(struct list *ls, char word[], int line)
{
	struct list *new_node = lalloc();
	int comp;

	if (ls == NULL) {
		new_node->word = strdup(word);
		new_node->line_number = line;
		new_node->next = NULL;

		ls = new_node;
	} else {
		struct list *cur, *prev;

		for (prev = NULL, cur = ls;
			 cur != NULL && (comp = strcmp(ls->word, word)) >= 0;
			 prev = cur, cur = cur->next) ;

		if (prev == NULL) {
			if (comp == 0) {
				for (;;);
			} else {

			}
		} else {
			new_node->next = cur;
			prev->next = new_node;
		}
	}

	return ls;
}

struct list *lalloc(void)
{
	return (struct list *) malloc(sizeof(struct list));
}

void print_list(struct list *ls)
{
	while (ls != NULL) {
		printf("%s: %d", ls->word, ls->line_number);
	}
}
