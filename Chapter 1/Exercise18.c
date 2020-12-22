#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
	char line[MAXLINE];
	int len;

	while ((len = getline(line, MAXLINE)) >= 0)
		if (len > 0) printf("%s", line);

	return 0;
}
int getline(char s[], int lim)
{
	int c, i, state;

	i = 0;
	while ((i < lim - 1) && ((c = getchar()) != EOF) && c != '\n')
	{
		if (c == ' ' || c == '\t')
			state = 0;
		else
			state = 1;
		s[i++] = c;
	}

	if (c == EOF) return -1;
	if (i == 0) return 0;

	if (state == 0) {
		while (--i > 0 && (s[i] == ' ' || s[i] == '\t'));
		
		if (i == 0) return 0;
		i = i + 1;
	}

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i;
}

void copy(char to[], char from[])
{
	int i = 0;

	while ((to[i] = from[i]) != '\0')
		++i;
}
