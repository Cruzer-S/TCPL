#include <stdio.h>

#define PRINT(FMT, X) printf(#X " = %" #FMT "\n", X)

int getch(void);
void ungetch(int);

int getfloat(double *);

int main(void)
{
	double flt;

	PRINT(c, getfloat(&flt));
	PRINT(g, flt);

	return 0;
}

int getfloat(double *val)
{
	double power, sign;
	int c, dot;

	while (isspace(c = getch())) ;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return '\0';
	}

	sign = (c == '-') ? -1.0 : +1.0;
	if (c == '+' || c == '-')
		c = getch();

	for (dot = 0, *val = 0.0, power = 1.0; 
		 isdigit(c) || c == '.'; c = getch()) 
	{
		if (c == '.') {
			dot = 1;
			continue;
		}

		*val = *val * 10 + (c - '0');

		if (dot) power /= 10.0;
	}

	*val = *val * sign * power;

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
