#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa(int n, char s[], int p);
void reverse(char s[]);
unsigned uabs(int );

int main()
{
	char str[30];

	itoa(INT_MIN, str, 20);

	printf("itoa(INT_MIN, str, 20): %s \n", str);

	return 0;
}

void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

unsigned uabs(int k)
{
	return k < 0 ? -k : k;
}

void itoa(int n, char s[], int p)
{
	int i, j, sign;

	sign = (n > 0) ? +1 : -1;

	i = 0;
	do {
		/* printf("%d, %d, %u \n", n, n % 10, uabs(n % 10)); */

		s[i++] = uabs(n % 10) + '0';
	} while (((sign > 0) ? ((n /= 10) > 0)  : 
			               ((n /= 10) < 0)));

	if (sign < 0)
		s[i++] = '-';

	while (i < p)
		s[i++] = ' ';

	s[i] = '\0';

	reverse(s);
}
