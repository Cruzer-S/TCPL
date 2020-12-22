#include <stdio.h>

#define MAXLINE 1000

void reverse(char line[], int len);
int getline(char s[], int lim);

int main()
{
	char line[MAXLINE];
	int len;

	while ((len = getline(line, MAXLINE)) > 0) {
		reverse(line, len - 1);
		printf("%s", line);
	}
	
	return 0;
}

int getline(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 
			&& (c = getchar()) != EOF 
			&& c != '\n'; ++i)
		s[i] = c;

	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;
}

void reverse(char line[], int len)
{
	char f, l, temp;

	for (f = 0, l = len - 1; f < l; f++, --l) {
		temp = line[f];
		line[f] = line[l];
		line[l] = temp;
	}
}
