#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(struct key))

#ifdef DEBUG
#define PRINT(X, F) printf(#X " = %" #F "\n", X);
#else
#define PRINT(X, F)
#endif

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
	clock_t start, tick = CLOCKS_PER_SEC / 5;

	while ((n = getword(word, MAXWORD)) != EOF) {
		PRINT(word, s);
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
	}

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
	int f, l, getch(void);
	void ungetch(int);

	char *w = word;

	*w = '\0';

	while (isspace(f = getch())) ;

	if (f == '\'') {
		if ((f = getch()) == '\\')
			getch();

		getchar();

		return 0;
	}

	if (f == '\"') {
		while ((f = getch()) != '\"')
			if (f == '\\') getch();

		return 0;
	}

	if (f == '/') {
		if ((f = getch()) == '*')
			while (!((f = getch()) == '*' && getch() == '/')) ;		
		else
			ungetch(f);

		return 0;
	}

	for (l = f; isalnum(f) || f == '_'; l = f, f = getch())
		*w++ = f;

	*w = '\0';

	if (f == EOF) return EOF;

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
