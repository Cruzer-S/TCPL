#include <stdio.h>

void reverse(char s[], int i)
{
	if (s[i] == '\0') return ;

	reverse(s, i + 1);
	putchar(s[i]);
}

int main(void)
{
	reverse("hello, world!", 0);

	return 0;
}
