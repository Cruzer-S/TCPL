#include <stdio.h>

int minscanf(char *, ...);

int main(void)
{
	int age;
	double height;
	char name[100];

	printf("name: ");
	minscanf("%s", name);

	printf("age: ");
	minscanf("%d", &age);

	printf("height: ");
	minscanf("%f", &height);

	printf("[%s]: %d, %g\n", name, age, height);

	return 0;
}

#include <ctype.h>
#include <stdarg.h>

#define BUFSIZE 1024

int minscanf(char *fmt, ...)
{
	va_list ap;
	int ch, match, i;
	char buffer[BUFSIZE];

	va_start(ap, fmt);
	for (match = 0; *fmt; fmt++) 
	{
		if (*fmt == ' ') {
			while (isspace(ch = getchar())) ;
			ungetc(ch, stdin);
		} else if (*fmt != '%') {
			if (getchar() != *fmt)
				break;
		} else {
			int ival;
			double dval, power;
			char *str;

			while (isspace(ch = getchar())) ;
			ungetc(ch, stdin);

			switch(*++fmt) {
			case 'd':
				for (ival = 0; isdigit(ch = getchar()); fmt++)
					ival = ival * 10 + (ch - '0');
				ungetc(ch, stdin);

				*(va_arg(ap, int *)) = ival;
				break;

			case 'f':
				for (dval = 0.0; isdigit(ch = getchar()); fmt++)
					dval = dval * 10.0 + (double)(ch - '0');

				power = 1.0;
				if (ch == '.')
					for (; isdigit(ch = getchar()); power *= 10.0)
						dval = dval * 10.0 + (double)(ch - '0');
				ungetc(ch, stdin);

				*(va_arg(ap, double *)) = dval / power;
				break;

			case 's':
				str = va_arg(ap, char *);
				while (!isspace(ch = getchar())) *str++ = ch;
				ungetc(ch, stdin);
				break;
			}
		}
	}

	va_end(ap);
	
	return match;
}
