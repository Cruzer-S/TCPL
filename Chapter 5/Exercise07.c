#include <stdio.h>
#include <string.h>

#define MAXLINES 1024
#define MAXWORDS 128

int readlines(char (*lineptr)[MAXWORDS], int nlines);
void writelines(char (*lineptr)[MAXWORDS], int nlines);

void qsort(char (*lineptr)[MAXWORDS], int left, int right);

int main(void)
{
	int nlines;
	char lineptr[MAXLINES][MAXWORDS];

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);

		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

int getline(char *, int);

int readlines(char (*lineptr)[MAXWORDS], int maxlines)
{
	int len, nlines;

	nlines = 0;
	while ((len = getline(lineptr[nlines++], MAXLINES)) > 0) {
		if (nlines >= maxlines)
			return -1;
		else
			lineptr[nlines - 1][len - 1] = '\0';
	}

	return nlines;
}

void writelines(char (*lineptr)[MAXWORDS], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

void qsort(char (*v)[MAXWORDS], int left, int right)
{
	int i, last;
	void swap(char (*v)[MAXWORDS], int i, int j);

	if (left >= right)
		return ;

	swap(v, left, (left + right) / 2);
	last = left;

	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);

	swap(v, left, last);

	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

void swap(char (*v)[MAXWORDS], int i, int j)
{
	char temp[MAXWORDS];

	strcpy(temp, v[i]);
	strcpy(v[i], v[j]);
	strcpy(v[j], temp);
}

int getline(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;

	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;
}
