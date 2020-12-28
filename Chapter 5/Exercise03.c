#include <stdio.h>

void Mstrcat(char *s, char *t);

int main(void)
{
	char str[1024] = "hello, ";

	Mstrcat(str, "world");
	puts(str);

	return 0;
}

void Mstrcat(char *s, char *t)
{
	while (*s != '\0') *s++;
	while (*t != '\0') *s++ = *t++;
	*s = '\0';
}
