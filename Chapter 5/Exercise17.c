#include <stdio.h>
#include <string.h> 

#define ABS(X) ((X) < 0 ? -(X) : X)
#define IS_MINUS(X) ((X) < 0 ? 1 : 0)
#define NEGMUL(X) ((X) < 0 ? -1 : +1)

#define MAXLINES 5000

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void mqsort(void *lineptr[], int left, int right, int reverse,
		   int (*comp)(const void *, const void *));

int parse_tag(char *);
void alignline(char *line, int reverse, int (*comp)(const void *, const void *));

int numcmp(const char *, const char *);
int stricmp(const char *, const char *);
int stridcmp(const char *, const char *);
int strdcmp(const char *, const char *);


void alignline(char *line, int reverse, int (*comp)(const void *, const void *))
{
	int i, j, k, enter;
	char token[1024][1024];
	char temp[1024];

	for (i = 0, j = 0, enter = 0; line[i] != '\0'; i++) {
		if (!isspace(line[i]) & !enter) {
			enter = 1;
			k = 0;
		}

		if (enter) {
			if (isspace(line[i])) {
				token[j++][k] = '\0';
				enter = 0;
				continue;
			}

			token[j][k++] = line[i];
		}
	} token[j++][k] = '\0';

	for (i = j - 1; i > 0; i--) {
		for (k = 0; k < i; k++) {
			if (reverse) {
				if (comp(token[k], token[k + 1]) > 0)
				{
					strcpy(temp, token[k]);
					strcpy(token[k], token[k + 1]);
					strcpy(token[k + 1], temp);
				}
			} else {
				if (comp(token[k], token[k + 1]) < 0)
				{
					strcpy(temp, token[k]);
					strcpy(token[k], token[k + 1]);
					strcpy(token[k + 1], temp);
				}
			}
		}
	}

	for (i = 0; i < j; i++)
		printf("%s ", token[i]);
	printf("\n");
}

int parse_tag(char *tag)
{
	int itag = 0x00;

	while (*tag != '\0') {
		switch (*tag++) {
		case 'r':
			itag |= 0x08;
			break;
		case 'f':
			itag |= 0x01;
			break;
		case 'd':
			itag |= 0x02;
			break;
		case 'n':
			itag |= 0x04;
			break;
		}
	}

	return itag;
}

int main(int argc, char *argv[])
{
	int nlines, i;
	int linetag, fieldtag;
	char *lineptr[MAXLINES];

	int (*comp[])(const char *, const char *) = {
		strcmp, stricmp, strdcmp, stridcmp, numcmp
	};

	if (argc > 1) linetag = parse_tag(argv[1] + 1);
	else          linetag = 0;

	if (argc > 2) fieldtag = parse_tag(argv[2] + 1);
	else          fieldtag = -1;

	
	if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
		printf("input too big to sort\n");
		return 1;
	}

	mqsort((void **) lineptr, 0, nlines - 1, linetag & 0x08,
		   (int (*)(const void *, const void *))comp[linetag % 0x08]);

	if (fieldtag < 0) {
		writelines(lineptr, nlines);
	} else {
		for (i = 0; i < nlines; i++)
			alignline(lineptr[i], fieldtag & 0x08,
			(int (*)(const void *, const void *))comp[fieldtag % 0x08]);
	}

	return 0;
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
	const char *t;
	double v1, v2;

	for (t = s1; *t != '\0'; t++)
		if (!isdigit(*t) && *t != '.')
			return 0;

	for (t = s2; *t != '\0'; t++)
		if (!isdigit(*t) && *t != '.')
			return 0;

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
