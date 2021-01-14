#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int getline(FILE *, char *line, int max);

int main(int argc, char *argv[])
{
	char line[MAXLINE], *comp;
	long lineno = 0;
	int c, except = 0, number = 0, found = 0;
	FILE *fp;

	while (--argc > 0 && (*++argv)[0] == '-')
		while ((c = *++argv[0])) {
			switch (c) 
			{
			case 'x':
				except = 1;
				break;

			case 'n':
				number = 1;
				break;

			default:
				fprintf(stderr, "%s: illegal option %c\n", argv[0], c);
				argc = 0;
				found = -1;
				break;
			}
		}

	if (argc < 1) {
		fprintf(stderr, "usage: %s -x -n <file or stdin> <pattern>\n", argv[0]);
		exit(1);
	} else if (argc == 2) {
		fp = fopen(argv[0], "r");
		if (fp == NULL) {
			fprintf(stderr, "failed to open file %s\n", argv[0]);
			exit(1);
		}

		comp = argv[1];
	} else {
		fp = stdin;
		comp = argv[0];
	}

	printf("argv[0]: %s\tarvg[1]: %s\n", argv[0], argv[1]);
	while (getline(fp, line, MAXLINE) > 0) 
	{
		lineno++;
		if ((strstr(line, comp) != NULL) != except) {
			if (fp != stdin)
				printf("%s ", argv[0]);
			if (number)
				printf("%3ld\t", lineno);
			printf("%s", line);
			found++;
		}
	}

	return found;
}

int getline(FILE *fp, char *line, int max)
{
	if (fgets(line, max, fp) == NULL)
		return 0;
	else
		return strlen(line);
}
