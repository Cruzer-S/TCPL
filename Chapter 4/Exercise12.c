#include <stdio.h>

int itoa(char s[], int i, int result)
{
	if (s[i] == '\0')
		return result;

	result = result * 10 + s[i] - '0';
	itoa(s, i + 1, result);
}

int main(void)
{
	printf("itoa(10024): %d \n", itoa("10024", 0, 0));

	return 0;
}
