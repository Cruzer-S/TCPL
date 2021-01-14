#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE(X) (sizeof(X) / sizeof(X[0]))
#define TOKSIZ 128

int getop(char []);
void push(double );
double pop(void);

double addd(double, double);
double subd(double, double);
double divd(double, double);
double muld(double, double);

int main(void)
{
	int ch, i;
	double op1, op2;

	double (* const func[])(double, double) = {
		addd, subd, divd, muld
	};

	const char operator[] = "+-/*";

	while (1) {
		scanf(" %c", (char*)&ch);
		for (i = 0; i < SIZE(func); i++)
			if (ch == operator[i]) 
				break;

		/* printf("ch: %c\ti: %d\n", ch, i); */
		if (i == SIZE(func)) {
			ungetc(ch, stdin);
			if (scanf("%lf", &op1) != 1)
				break;

			/* printf("push: %g\n", op1); */
			push(op1);
		} else {
			op2 = pop(); op1 = pop();

			/* printf("op1: %g\top2: %g\n", op1, op2); */
			push(func[i](op1, op2));
		}
	}

	printf("\t%g\n", pop());

	return 0;
}

double addd(double a, double b) 
{
	return a + b;
}

double subd(double a, double b)
{
	return a - b;
}

double muld(double a, double b)
{
	return a * b;
}

double divd(double a, double b)
{
	return a / b;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g \n", f);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty \n");
		return 0.0;
	}
}
