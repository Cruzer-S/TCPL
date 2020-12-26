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
void clear(void);

main()
{
	int type;
	double op1, op2;
	double var[VALSIZ], recently;
	char s[MAXOP], seq = 0;

	while ((type = getop(s)) != EOF) {
		/* printf("%c[%d]: %s \n", type, seq, s); */
		switch (type) {
		case '=':
			seq = 1;
			break;
		case '$':
			printf("most recently printed value: %g\n", recently);
			seq = 3;
			break;
		case VARIABLE:
			if (seq == 2) {
				printf("\t%g\n", var[s[0] - 'a']);
			} else if (seq == 1) {
				var[s[0] - 'a'] = pop();
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
		case 'P': /* print top of the stack element */
			seq = 2;
			break;
		case 'D': /* duplicate top of the stack element, then add it */
			push(peek());
			break;
		case 'S': /* swap first two element of the stack */
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
			if (seq == 0) {
				printf("\t%g\n", recently = pop());
			} else {
				seq = 0;
			}
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

void clear(void)
{
	sp = 0;
}
#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[])
{
	int i, c, n = 0;

	while ((s[0] = c = getch()) == ' ' || c == '\t') ;
	s[1] = '\0';

	if (islower(c))
		return VARIABLE;

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

char buf[BUFSIZE];
int bufp = 0;

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
