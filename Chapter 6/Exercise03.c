#include <stdio.h>

#define MAXWORDS 1024

struct list {
	char word[MAXWORDS];
	int line_number;
	struct list *next;
};

int main(void)
{
	struct list *head = NULL;

	return 0;
}

struct list *add_data(struct list *ls, char word[], int line)
{
	if (ls == NULL) {
		ls = lalloc();

		ls->next = NULL;
		ls->line_number = line;
		strcpy(ls->word, word);
	} else {
		while (ls != NULL && ls->line_number > line)
			ls = ls->next;

	}
}

struct list *lalloc(void)
{
	return (struct list *) malloc(sizeof(struct list));
}
