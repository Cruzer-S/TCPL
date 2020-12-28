#include <stdio.h>

void strncpy(char *, char *, int );
void strncat(char *, char *, int );

int main(void)
{
	char str[1024];

	strncpy(str, "hello, world!", 6);
	puts(str);

	strncat(str, " world!", 4);

	puts(str);

	return 0;
}

void strncpy(char *s, char *t, int size)
{
	for (; size-- > 0 && *t != '\0'; *s++ = *t++) ;
	*s = '\0';
}

void strncat(char *s, char *t, int size)
{
	while (*s != '\0') s++;
	for (; size-- > 0 && *t != '\0'; *s++ = *t++) ;
	*s = '\0';
}
