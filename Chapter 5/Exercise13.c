#include <stdio.h>
#include <stdlib.h>

#define MAXLINES 1024
#define MAXLEN   1024

#define DEFAULT_N_LINES 10

int getlines(char (*line)[MAXLEN], int max_line);

int main(int argc, char *argv[])
{
	int i;
	int nlines;
	int readlines;

	char lines[MAXLINES][MAXLEN];

	if (argc != 2)
		nlines = DEFAULT_N_LINES;
	else
		nlines = atoi(argv[1]);

	readlines += getlines(lines, MAXLINES);

	for (i = readlines - nlines; i < readlines; i++)
		puts(lines[i]);

	return 0;
}

int getlines(char (*line)[MAXLEN], int max_line)
{
	int ch, i, j;
	char *lp;

	for (i = 0; i < max_line; i++)
	{
		for (lp = line[i]; 
		(ch = getchar()) != EOF && ch != '\n' && lp - line[i] < MAXLEN - 1;
			 *lp++ = ch) ;

		*++lp = '\0';

		if (ch == EOF) break;
	}

	return i;
}
