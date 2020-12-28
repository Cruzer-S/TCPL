#include <stdio.h>
#include <stdlib.h>

#if defined(DDEBUG)
	#define DEBUG(C, X) printf(#X " = %" #C "\n", X)
#else
	#define DEBUG(C, X) 
#endif

#define elif(X) if (!(X))

int push(double );
int pop(double *);

int main(int argc, char *argv[])
{
	double op1, op2;
	while (*++argv) 
	{
		if (isdigit(**argv)) {
			DEBUG(s, *argv);
			DEBUG(g, atof(*argv));

			elif (push(atof(*argv)))
				return 1;
		} else {
			DEBUG(c, **argv);
			switch(**argv) {
			case '*':
				elif (pop(&op1) && pop(&op2))
					return 1;

				elif (push(op1 * op2))
					return 1;
				break;

			case '+':
				elif (pop(&op1) && pop(&op2))
					return 1;

				elif (push(op1 + op2))
					return 1;
				break;

			case '/':
				elif (pop(&op1)) 
					return 1;
				elif (pop(&op2)) 
					return 1;

				elif (push(op2 / op1)) 
					return 1;
				break;

			case '-':
				elif (pop(&op1)) 
					return 1;
				elif (pop(&op2)) 
					return 1;

				elif (push(op2 - op1)) 
					return 1;
				break;
			}
		}
	}

	elif (pop(&op1))
		return 1;

	printf("result: %g \n", op1);

	return 0;
}

#define STACK_SIZE 128

static double stack[STACK_SIZE];
static double *sp = stack;

int push(double val)
{
	if (sp - stack >= STACK_SIZE) {
		printf("stack is full. failed to push %g\n", val);
		return 0;
	}

	*sp++ = val;
	
	return 1;
}

int pop(double *pval)
{
	if (sp - stack <= 0) {
		printf("stack is empty. failed to pop data\n");
		return 0;
	}

	*pval = *--sp;

	return 1;
}
