#include <stdio.h>
#include <string.h>

#define MAXLINES 1024
#define MAXLEN 1024

void *dalloc(int size);
void dfree(void *mem);
int dusgae(void);

int getlines(char *line[], int maxline);
int sortline(char *line[], int nlines, char *order);
void writelines(char *lines[], int nlines, char *token);

int main(int argc, char *argv[])
{
	char *line[MAXLINES];
	int nlines;
	char *order, *token;

	nlines = getlines(line, MAXLINES);

	order = token = NULL;
	if (argc > 1) order = argv[1] + 1;
	if (argc > 2) token = argv[2] + 1;

	writelines(line, nlines, token);
	if (!sortline(line, nlines, order))
		return 1;

	writelines(line, nlines, token);

	while (--nlines >= 0)
		dfree(line[nlines]);

	return 0;
}

#include <stdlib.h>
#include <ctype.h>

int reverse, fold, dorder, norder;

int mstrcmp(char *s1, char *s2)
{
	for (;*s1 != '\0' && *s2 != '\0'; s1++, s2++) {
		if (dorder) {
			if (!isalnum(*s1) && !isspace(*s1)) {
				s2--;
				continue;
			}
			if (!isalnum(*s2) && !isspace(*s2)) {
				s1--;
				continue;
			}
		}

		if (*s1 != *s2)
			return *s1 - *s2;
	}

	return 0;
}

int stricmp(char *s1, char *s2)
{
	for (;*s1 != '\0' && *s2 != '\0'; s1++, s2++) {
		if (dorder) {
			if (!isalnum(*s1) && !isspace(*s1)) {
				s2--;
				continue;
			}
			if (!isalnum(*s2) && !isspace(*s2)) {
				s1--;
				continue;
			}
		}

		if (toupper(*s1) != toupper(*s2))
			return toupper(*s1) - toupper(*s2);
	}

	return 0;
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

void swap(char *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}


void mqsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);
	char *s1, *s2;

	if (left >= right)
		return ;

	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (norder) {
			if (numcmp(v[left], v[i]) * 
				(reverse ? (-1) : (+1)) < 0) 
				swap(v, ++last, i);
		} else {
			if (fold) {
				if (stricmp(v[left], v[i]) *
					(reverse ? (-1) : (+1)) < 0)
					swap(v, ++last, i);
			} else {
				if (mstrcmp(v[left], v[i]) * 
					(reverse ? (-1) : (+1)) < 0)
					swap(v, ++last, i);
			}

		}
	}

	swap(v, left, last);
	mqsort(v, left, last - 1);
	mqsort(v, last + 1, right);
}

int sortline(char *line[], int nlines, char *order)
{
	void (*comp)(const void *, const void *);

	reverse = fold = dorder = norder = 0;

	if (order != NULL) {
		while (*order != '\0') {
			switch (*order++) {
			case 'r': reverse = 1;
					  break;
			case 'f': fold = 1;
					  break;
			case 'd': dorder = 1;
					  break;
			case 'n': norder = 1;
					  break;
			default: printf("wrong token\n");
					 return 0;
			}
		}
	}

	printf("reverse: %d\n"
		   "fold   : %d\n"
		   "dorder : %d\n"
		   "norder : %d\n", reverse, fold, dorder, norder);

	mqsort(line, 0, nlines - 1);

	return 1;
}

int getlines(char *lines[], int maxline)
{
	char line[MAXLEN]; 
	int i, j, ch;

	for (i = 0; i < maxline; i++) 
	{
		for (j = 0; j < MAXLEN - 1 && (ch = getchar()) != EOF && ch != '\n'; j++)
			line[j] = ch;
		line[j] = '\0';

		lines[i] = dalloc(strlen(line) + 1);
		strcpy(lines[i], line);

		if (ch == EOF) break;
	}

	return i;
}

void writelines(char *lines[], int nlines, char *token)
{
	int i;

	if (!token) {
		for (i = 0; i < nlines; i++)
			puts(lines[i]);
	} else {
	}
}

#define DALLOC_SIZE 1024 * 1024

static char dmem[DALLOC_SIZE];
static char *dptr = dmem;

int dusage(void)
{
	return dptr - dmem;
}

void *dalloc(int size)
{
	if (dptr + size >= dmem + DALLOC_SIZE)
		return NULL;

	dptr += size;

	return dptr - size;
}

void dfree(void *mem)
{
	if ((char *)mem < dmem || (char *)mem >= dmem + DALLOC_SIZE)
		return ;

	dptr = (void *)mem;
}
