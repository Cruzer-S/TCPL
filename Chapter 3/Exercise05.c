#include <stdio.h>
#include <string.h>
#include <limits.h>

void itob(int n, char s[], int b);
void reverse(char s[]);
unsigned uabs(int );

int main()
{
	char str[30];


	itob(INT_MIN, str, 16);
	printf("itob(INT_MIN, str, 16): %s \n", str);

	itob(INT_MIN, str, 10);
	printf("itob(INT_MIN, str, 10): %s \n", str);

	itob(INT_MIN, str,  2);
	printf("itob(INT_MIN, str,  2): %s \n", str);

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

void itob(int n, char s[], int b)
{
	int i, j, sign;

	sign = (n > 0) ? +1 : -1;

	i = 0;
	do {
		if (b == 16)
			s[i++] = uabs(n % b) < 10           ?
					 uabs(n % b) % b + '0'      :
					 uabs(n % b) % b + 'a' - 10 ;
		else s[i++] = uabs(n % b) + '0';
	} while (((sign > 0) ? ((n /= b) > 0)  : 
			               ((n /= b) < 0)));

	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';

	reverse(s);
}
