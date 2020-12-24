#include <stdio.h>

void escape(char s[], char v[]);

int main()
{
	char str[] = "hello\tworld!\n";
	char cvt[30];

	escape(str, cvt);

	printf("str: %s \n", str);
	printf("ctv: %s \n", cvt);

	return 0;
}

void escape(char s[], char v[])
{
	int i, j;

	for (i = 0, j = 0; s[i] != '\0'; i++, j++) {
		switch (s[i]) {
		case '\t':
			v[j++] = '\\';
			v[j] = 't';
			break;

		case '\n':
			v[j++] = '\\';
			v[j] = 'n';
			break;

		default: 
			v[j] = s[i];
			break;
		}
	}

	v[j] = '\0';
}
