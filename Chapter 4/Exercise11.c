#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER '0'
#define VARIABLE 'a'
#define VALSIZ 26
#define NUMSIZ 30
#define MAXLINE 1024

int getop(char [], char []);

void push(double );
double pop(void);
double peek(void);
void clear(void);

main()
{
	int type;
	double op1, op2;
	double var[VALSIZ], recently;

	char s[NUMSIZ], seq = 0;
	char line[MAXLINE];

	while (getline(line, MAXLINE) > 1)
	{
		while ((type = getop(line, s)), 1) {
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
				/* printf("error: unkown commad %s\n", s); */
				break;
			}

			if (type == '\n') break;
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

int getop(char line[], char operand[])
{
	int s = 0, i = 0, n = 0, check = 0;

	while (line[i] == EOF) s = ++i;

	while (line[i] == ' ' || line[i] == '\t') i++;

	if (islower(line[i])) {
		while (s <= i) line[s++] = EOF;
		return VARIABLE;
	}

	if (!isdigit(line[i]) && line[i] != '.') {
		if (line[i] != '-') {
			check = line[i];
			while (s <= i) line[s++] = EOF;
			return check;
		}

		check = 1;
	}

	operand[n++] = line[i++];

	while (isdigit(line[i]))
		operand[n++] = line[i++];

	if (line[i] == '.') {
		operand[n++] = line[i++];
		while (isdigit(line[i]))
			operand[n++] = line[i++];
	}

	if (check && n == 1) {
		while (s <= i) line[s++] = EOF;
		return '-';
	}

	operand[n] = '\0';

	while (s <= i) line[s++] = EOF;

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

int getline(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i;
}

