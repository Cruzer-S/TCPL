#include <stdio.h>
#include <ctype.h>

void expand(char s1[], char s2[]);

int main()
{
	char shortcut[] = "A-Z and 0-9\n\t\t"
		              "d-f and 4-6\n";

	char longterm[100];

	expand(shortcut, longterm);

	printf("shortcut: %s", shortcut);
	printf("longterm: %s", longterm);

	return 0;
}

void expand(char s1[], char s2[])
{
	int i, j, k;

	for (i = j = 0; s1[i] != '\0'; i++, j++) {	
		if (isalnum(s1[i]) && s1[i + 1] == '-' && isalnum(s1[i + 2])) {
			for (k = s1[i]; k <= s1[i + 2]; k++)
				s2[j++] = k;

			i += 2, j--;
		} else {
			s2[j] = s1[i];
		}
	}

	s2[j] = '\0';
}

