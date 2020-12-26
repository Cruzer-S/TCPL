#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define VARIABLE 'a'
#define VALSIZ 26

int getop(char []);

void push(double );
double pop(void);
double peek(void);

main()
{
	int type;
	double op1, op2;
	double var[VALSIZ], recently;
	char s[MAXOP], seq;

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case '=':
			seq = 1;
			break;
		case '$':
			printf("most recently printed value: %d \n", recently);
			break;
		case VARIABLE:
			if (seq) {
				var[s[0] - 'a'] = pop();
				seq = 0;
			} else push(var[s[0] - 'a']);
			break;
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case 'p': /* print top of the stack element */
			printf("top of the stack: %g \n", recently = peek());
			break;
		case 'd': /* duplicate top of the stack element, then add it */
			push(peek());
			break;
		case 's': /* swap first two element of the stack */
			op1 = pop(), op2 = pop();
			push(op1), push(op2);
			break;
		case '%':
			op2 = pop(), op1 = pop();
			if (op2 == 0.0) {
				printf("error: zero divisor\n");
				break;
			}
			if (op1 * op2 < 0) {
				printf("error: invalid operand\n");
				break;
			}
			push(fmod(op1, op2));
			break;
		case '\n':
			printf("\t%.8g\n", recently = pop());
			break;
		default:
			printf("error: unkown commad %s\n", s);
			break;
		}
	}

	return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double peek(void)
{
	return val[sp - 1];
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

#include <ctype.h>

int getch(void);
void ungetch(int);
void ungets(char []);

int getop(char s[])
{
	int i, c, n = 0;

	if (isalpha(s[0])) return VARIABLE;
	while ((s[0] = c = getch()) == ' ' || c == '\t') ;

	s[1] = '\0';

	i = 0;
	if (!isdigit(c) && c != '.') {
		if (c != '-')
			return c;

		n = 1;
		s[++i] = c = getch();
	}

	if (isdigit(c))
		while (isdigit(s[++i] = c = getch())) ;

	if (c == '.')
		while (isdigit(s[++i] = c = getch())) ;

	if (n == 1 && i == 1) {
		if (c != EOF)
			ungetch(c);

		return '-';
	}

	s[i] = '\0';
	if (c != EOF)
		ungetch(c);

	return NUMBER;
}

#define BUFSIZE 100

#if (BUFSIZE <= 0)
	int ch;
#else
	#define USING_BUFFER

	char buf[BUFSIZE];
	int bufp = 0;
#endif

int getch(void)
{
#if defined(USING_BUFFER)
	return (bufp > 0) ? buf[--bufp] : getchar();
#else
	if (ch != EOF) {
		int save = ch;
		ch = EOF;
		return save;
	} else {
		return getchar();
	}
#endif
}

void ungetch(int c)
{
	if (c == EOF) {
		printf("ungetch: EOF can't be pushed back\n");
		return ;
	}
#if defined(USING_BUFFER)
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
#else
	if (ch == EOF) {
		ch = c;
	} else {
		printf("ungetch: only one character should be saved\n");
	}
#endif
}

void ungets(char s[])
{
#if defined(USING_BUFFER)
	int i;

	for (i = 0; s[i] != '\0'; i++)
		ungetch(s[i]);
#else
	printf("ungets: only one character should be saved\n");
#endif
}
