#include <stdio.h>

void squeeze(char s[], char d[])
{
	int i, j, end, check;

	for (i = end = 0; s[i] != '\0'; i++)
	{
		for (check = 0, j = 0; d[j] != '\0'; j++)
			if (s[i] == d[j])
				check = 1;

		if (!check)
			s[end++] = s[i];
	}

	s[end++] = '\0';
}

int main()
{
	char str[] = "Hello World!",
		 del[] = "hate world";

	squeeze(str, del);

	printf("str: %s \n", str);

	return 0;
}
