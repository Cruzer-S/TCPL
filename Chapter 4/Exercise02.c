#include <stdio.h>

#define PRTg(X) printf(#X " = %g \n", X);

double atof(char s[]);

int main(void)
{
	PRTg(atof("123.45e+0"));
	putchar('\n');

	PRTg(atof("123.45e-1"));
	PRTg(atof("123.45e-3"));
	PRTg(atof("123.45e-5"));
	putchar('\n');

	PRTg(atof("123.45e+1"));
	PRTg(atof("123.45e+3"));
	PRTg(atof("123.45e+5"));
	putchar('\n');

	return 0;
}

double atof(char s[])
{
	double val, power;
	int i, sign, exp, exp_sign;

	for (i = 0; isspace(s[i]); i++) ;

	sign = (s[i] == '-') ? -1 : +1;
	if (s[i] == '+' || s[i] == '-')
		i++;

	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	
	if (s[i] == '.')
		i++;

	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	if (s[i] == 'e' || s[i] == 'E') {
		if (s[++i] == '-') exp_sign = -1;
		else exp_sign = +1;

		for (exp = 0, i++; isdigit(s[i]); i++)
			exp = 10 * exp + (s[i] - '0');
	}
	
	for (i = 0; i < exp; i++) {
		if (exp_sign > 0)
			power /= 10.0;
		else
			power *= 10.0;
	}

	return sign * val / power;
}
