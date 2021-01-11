#include <stdio.h>

#define WRDLEN 128
#define LINLEN 64 

struct list {
	char *word;
	short line[LINLEN];
	char usage;

	struct list *next;
};

int getword(char word[], int maxlen);

struct list *add_list(struct list *, char *, int );
void show_list(struct list *);

int main(void)
{
	struct list *head = NULL;
	char word[WRDLEN];
	int lines = 0, type;

	while ((type = getword(word, WRDLEN)) != EOF) 
	{
		if (type == '\n') {
			lines++;
			continue;
		}

		head = add_list(head, word, lines + 1);
	}

	show_list(head);
	
	return 0;
}

#include <string.h>
#include <stdlib.h>

struct list *add_list(struct list *head, char *word, int line) 
{
	struct list *prev, *cur, *new_node;
	int comp;
	char *strdup(const char * );

	new_node = malloc(sizeof(struct list));
	if (new_node == NULL)
		return NULL;

	for (prev = NULL, cur = head;
		 cur != NULL && (comp = strcmp(cur->word, word)) < 0;
		 prev = cur, cur = cur->next) ;

	if (cur == NULL) {
		new_node->word = strdup(word);
		new_node->line[0] = line;
		new_node->usage = 1;	
		new_node->next = NULL;

		if (prev)
			prev->next = new_node;
		else
			head = new_node;
	} else {
		if (comp == 0) {
			if (cur->line[cur->usage - 1] != line)
				cur->line[cur->usage++] = line;
		} else {
			new_node->word = strdup(word);
			new_node->line[0] = line;
			new_node->usage = 1;
			new_node->next = cur;

			if (prev)
				prev->next = new_node;
			else
				head = new_node;
		}
	}

	return head;
}

void show_list(struct list *ls) 
{
	int i;

	for (; ls != NULL; ls = ls->next) {
		printf("%s: %d", ls->word, ls->line[0]);

		for (i = 1; i < ls->usage; i++)
			printf(", %d", ls->line[i]);

		printf("\n");
	}
}

#include <ctype.h>

int getword(char word[], int maxlen)
{
	int c;
	char *w = word;

	while (!isalpha(c = getchar())) {
		if (c == EOF) return EOF;
		if (c == '\n') return '\n';
	}

	for (*w++ = c; --maxlen > 0; w++)
		if (!isalpha(*w = getchar())) {
			ungetc(*w, stdin);
			break;
		}

	*w = '\0';

	return word[0];
}
