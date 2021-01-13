#include <stdio.h>

void minprintf(char *, ...);

int main(void)
{
	const char *string = "hello, world";

	minprintf(":%s:\n", string);
	minprintf(":%10s:\n", string);
	minprintf(":%.10s:\n", string);
	minprintf(":%-10s:\n", string);
	minprintf(":%.15s:\n", string);
	minprintf(":%-15s:\n", string);
	minprintf(":%15.10s:\n", string);
	minprintf(":%-15.10s:\n", string);

	return 0;
}

#include <stdarg.h>
#include <ctype.h>

#define BUFSIZE 1024 

void minprintf(char *fmt, ...)
{
	va_list ap;

	char *p, *sval, ch;
	int ival;
	double dval;

	int adjust, precision, 
		sign, length;
	int k;

	char buffer[BUFSIZE];

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}

		sign = +1;
		if (*++p == '-') {
			sign = -1;
			p++;
		}

		adjust = 0;
		for (k = 0; isdigit(*p); k++, p++)
			adjust = adjust * 10 + (*p - '0');

		precision = 0; 
		if (*p == '.') {
			for (k = 0; isdigit(*++p); k++)
				precision = precision * 10 + (*p - '0');
		} else {
			precision = -1;
		}
		
		switch (*p) {
		case 'd':
			ival = va_arg(ap, int);
			length = sprintf(buffer, "%d", ival);
			break;

		case 'f':
			dval = va_arg(ap, double);
			length = sprintf(buffer, "%f", dval);
			break;

		case 's':
			for (sval = va_arg(ap, char *), length = 0; 
				 *sval; 
				 sval++, length++) buffer[length] = *sval;
			buffer[length] = '\0';
			break;

		default:
			putchar(*p);
			continue;
		}

		/*
		printf("sign: %d\tadjust:%d\tprecision: %d\tlength:%d\n",
				sign, adjust, precision, length);
		*/

		if (precision == -1)
			precision = length;

		printf("%*.*s", adjust * sign, precision, buffer);
	}

	va_end(ap);
}
