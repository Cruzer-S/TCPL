#include <stdio.h>
#include <string.h>
#include <ctype.h>

int hex_to_num(int );
int htoi(char s[]);

int main()
{
	char hex_str[20];
	scanf("%s", hex_str);

	printf("result: %d \n", htoi(hex_str));

	return 0;
}

int hex_to_num(int hex)
{
	char *lower = {
		"0123456789abcdef"
	},	 *upper = {
		"ABCDEF"
	},   *value;

	value = strchr(lower, hex);
	if (!value)
		value = strchr(upper, hex) + 10 - upper + lower;

	return (int)(value - lower);
}

int htoi(char s[])
{
	int r, i, sign;
	/* implementation must use ASCII code set */

	sign = 0;
	if (s[0] == '-')
		sign = -1;
	else if (s[0] == '+')
		sign = +1;

	if (sign != 0) {
		i = 1;
	} else {
		sign = +1;
		i = 0;
	}

	for (r = 0; s[i] != '\0'; i++)
		if (isxdigit(s[i]))
			r = r * 16 + hex_to_num(s[i]);

	return r * sign;
}
