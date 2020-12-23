#include <stdio.h>

int lower(int c);

int main()
{
	printf("%c%c%c%c\n", lower('a'), lower('B'), lower('c'), lower('d'));

	return 0;
}



int lower(int c)
{
	return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : (c);
}
