#include <stdio.h>

int any(char s1[], char s2[])
{
	int i, j, pos = -1;

	for (i = 0; s1[i] != '\0' && pos == -1; i++)
		for (j = 0; s2[j] != '\0' && pos == -1; j++)
			if (s1[i] == s2[j])
				pos = i;

	return pos;
}


int main()
{
	char first[] = "hello, world",
		 second[] = "bax";

	printf("any(first, second): %d \n", any(first, second));

	return 0;
}
