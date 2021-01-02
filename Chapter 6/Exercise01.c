#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(struct key))

struct key {
	char *word;
	int count;
};

struct key keytab[] = {
	{ "auto", 0 }, { "break", 0 }, { "case", 0 },
	{ "char", 0 }, { "const", 0 }, { "continue", 0 },
	{ "default", 0 }, { "void", 0 }, { "volatile", 0 },
	{ "while", 0 }
};

int getword(char *, int );
int binsearch(char *, struct key *, int );

int main(void)
{
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;

	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n",
					keytab[n].count, keytab[n].word);

	return 0;
}

int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
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

int getword(char *word, int lim)
{
	static int is_comment = 0,
			   is_preprocessor = 0, 
			   is_string = 0;
	
	int f, l, getch(void);
	void ungetch(int);

	char *w = word;

	for ( l = -1; isspace(f = getch()); l = f)
		if (f == '\n' && is_preprocessor)
			is_preprocessor = 0;

	if (f == '#') is_preprocessor = 1;
	else if (f == '/') {
		l = getch();
		if (l == '*') is_comment = 1;
		else          ungetch(l);
	} else if (f == '*') {
		l = getch();
		if (l == '/') is_comment = 0;
		else          ungetch(l);
	} else if (l != '\\') {
		if (f == '\"') is_string = !is_string;
		else           ungetch(l);
	}

	if (f != EOF)
		*w++ = f;
	if (!isalpha(f)) {
		*w = '\0';
		return f;
	}

	for (; --lim > 0; w++)
	{
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	}

	*w = '\0';

	return word[0];
}

#define BUFSIZE 1024

char buffer[BUFSIZE];
char *bp = buffer;

int getch(void)
{
	return (bp == buffer) ? getchar() : *--bp;
}

void ungetch(int ch)
{
	*bp++ = ch;
}
