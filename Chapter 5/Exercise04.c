#include <stdio.h>

int strend(char *, char *);

int main(void)
{
	printf("%d \n", strend("hello, world", "world"));

	return 0;
}

int strend(char *s, char *t)
{
	char *save;

	for (save = s; *s != '\0'; save = ++s) {
		while (*s == *t) {
			if (*t == '\0')
				return 1;
			s++, t++;
		}

		s = save;
	}

	return 0;
}
