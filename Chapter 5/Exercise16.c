#include <stdio.h>
#include <string.h> 
#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void mqsort(void *lineptr[], int left, int right, int reverse,
		   int (*comp)(const void *, const void *));

int numcmp(const char *, const char *);

int stricmp(const char *, const char *);

int stridcmp(const char *, const char *);
int strdcmp(const char *, const char *);

int main(int argc, char *argv[])
{
	int nlines, c;
	int numeric, reverse, cases, dorder;
	int (*comp)(const char *, const char *);

	dorder = cases = numeric = reverse = 0;

	while (--argc > 0 && (*++argv)[0] == '-')
	{
		while (c = *++argv[0]) {
			switch (c) {
			case 'n':
				numeric = 1;
				break;
			case 'r':
				reverse = 1;
				break;
			case 'f':
				cases   = 1;
				break;
			case 'd':
				dorder  = 1;
				break;
			default:
				printf("%s: illegal option %c\n", argv[0], c);
				break;
			}
		}
	}

	if (numeric) {
		comp = numcmp; 
	} else {
		if (dorder) {
			if (cases) comp = stridcmp;
			else       comp = strdcmp;
		} else {
			if (cases) comp = stricmp;
			else       comp = strcmp;
		}
	}

	printf("comp: %p\n", comp);

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		mqsort((void **) lineptr, 0, nlines - 1, reverse, 
			   (int (*)(const void *, const void *))comp);

		writelines(lineptr, nlines);

		return 0;
	} else {
		printf("input too big to sort\n");

		return 1;
	}
}

void mqsort(void *v[], int left, int right, int reverse,
		    int (*comp)(const void *, const void *))
{
	int i, last;
	void swap(void *v[], int, int );

	if (left >= right)
		return ;

	swap(v, left, (left + right) / 2);
	last = left;

	for (i = left + 1; i <= right; i++) {
		if (reverse) {
			if ((*comp)(v[i], v[left]) > 0)
				swap(v, ++last, i);
		} else {
			if ((*comp)(v[i], v[left]) < 0)
				swap(v, ++last, i);
		}
	}

	swap(v, left, last);
	mqsort(v, left, last - 1, reverse, comp);
	mqsort(v, last + 1, right, reverse, comp);
}

#define MAXLEN 1000

int getline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}

	return nlines;
}

int getline(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i;
}

void writelines(char *lineptr[], int nlines)
{
	int i;

	for (i = 0; i < nlines; i++)
		puts(lineptr[i]);
}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	} else {
		return 0;
	}
}

void afree(char *p)
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

#include <stdlib.h>

int stricmp(const char *s1, const char *s2)
{
	while(*s1 != '\0' && *s2 != '\0' && toupper(*s1) == toupper(*s2))
			s1++, s2++;

	return toupper(*s1) - toupper(*s2);
}

int numcmp(const char *s1, const char *s2) 
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);

	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}


void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

#include <ctype.h>

int stridcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0') 
	{
		if (!isalnum(*s1) && !isspace(*s1)) {
			s1++; 
			continue;
		}
		if (!isalnum(*s2) && !isspace(*s2)) {
			s2++; 
			continue;
		}

		if (toupper(*s1) != toupper(*s2))
			break;

		s1++, ++s2;
	}

	return toupper(*s1) - toupper(*s2);
}

int strdcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0') 
	{
		if (!isalnum(*s1) && !isspace(*s1)) {
			s1++;
			continue;
		}
		if (!isalnum(*s2) && !isspace(*s2)) {
			s2++; 
			continue;
		}

		if (*s1 != *s2)
			break;

		s1++, ++s2;
	}

	return *s1 - *s2;

}
