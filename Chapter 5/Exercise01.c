#include <stdio.h>
#include <ctype.h>

#define PRINT(FMT, X) printf(#X " = %" #FMT "\n", X)

int getch(void);
void ungetch(int);

int getint(int *pn);

int main(void)
{
	int ret, x;

	PRINT(c, ret = getint(&x));

	if (ret) PRINT(d, x);
	else {
		while ((x = getch()) != '\n')
		putchar(x);
	}

	return 0;
}

int getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch())) ;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return '\0';
	}

	if (c == '+' || c == '-') {
		sign = getch();
		if (!isdigit(sign)) {
			ungetch(sign);
			ungetch(c);

			return '\0';
		}
		ungetch(sign);
		sign = c == '+' ? +1 : -1;
		c = getch();
	} else sign = +1;

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');

	*pn *= sign;

	if (c != EOF)
		ungetch(c);

	return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int  bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
