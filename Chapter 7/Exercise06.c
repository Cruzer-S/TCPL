#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1024

int getlines(FILE *, char [], int );

int main(int argc, char *argv[])
{
	FILE *first, *second;
	char buf1[MAXLEN], buf2[MAXLEN];
	int lines;

	if (argc != 3) {
		fprintf(stderr, "usage: %s <file1> <file2>\n", argv[0]);
		exit(1);
	}

	first = fopen(argv[1], "r");
	if (!first) {
		fprintf(stderr, "Faile to open file %s\n", argv[1]);
		exit(1);
	}

	second = fopen(argv[2], "r");
	if (!second) {
		fprintf(stderr, "Failed to open file %s\n", argv[2]);
		exit(1);
	}

	for (lines = 1;
	     getlines( first, buf1, MAXLEN) != EOF 
	  && getlines(second, buf2, MAXLEN) != EOF;
	     lines++) 
		if (strcmp(buf1, buf2)) 
		{
			printf("diffent line: %d\n", lines);
			printf("%s\n%s\n", buf1, buf2);
			break;
		}

	fclose(first);
	fclose(second);

	return 0;
}

int getlines(FILE *fp, char line[], int maxlen)
{
	char *ptr;
	int ch;

	if ((ch = fgetc(fp)) == EOF)
		return EOF;

	for (ptr = line; (ptr - line) < maxlen && ch != '\n'; 
		 *ptr++ = ch, ch = fgetc(fp));
	*ptr = '\0';

	return line[0];
}
