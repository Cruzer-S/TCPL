#include <stdio.h>
#include <stdlib.h>

#define PAGELINE 25
#define LINELEN 50
#define TABSIZE 4

void print_info(char *, int );

int main(int argc, char *argv[])
{
	FILE *fp;
	char *ptr;
	int ch;
	int page, count, line;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <file> ...\n", argv[0]);
		exit(1);
	}

	while (*++argv != NULL)
	{
		fp = fopen(*argv, "r");
		if (fp == NULL) {
			fprintf(stderr, "failed to open file %s\n", *argv);
			continue;
		}

		print_info(*argv, 1);
		for (page = count = line = 0; (ch = fgetc(fp)) != EOF; count++) {
			putchar(ch);

			if (ch == '\n') {
				line++;
				count = 0;
			} else if (ch == '\t') {
				count += TABSIZE;
			}

			if (count >= LINELEN) {
				count = 0;
				line++;
				putchar('\n');
			}

			if (line >= PAGELINE) {
				count = 0;
				line = 0; 

				print_info(*argv, ++page + 1);
			}
		}

		fclose(fp);
	}

	return 0;
}

#include <string.h>

void print_info(char *name, int page)
{
	int i, padding;
	char buffer[BUFSIZ];

	sprintf(buffer, "File name: %s - Page: %d",
			name, page);
	padding = (LINELEN - strlen(buffer)) / 2;

	putchar('\n');
	for (i = 0; i < LINELEN; i++)
		putchar('=');
	putchar('\n');

	printf("%*s%s%*s\n", 
			padding, "", 
			buffer,
			padding, "");

	for (i = 0; i < LINELEN; i++)
		putchar('=');
	putchar('\n');
}
