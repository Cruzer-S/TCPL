#include <stdio.h>

void error(const char *, ...);

int main(int argc, char *argv[])
{
	FILE *fp;
	int ch;
	int i, j;

	if (argc < 2)
		error("usage: %s <file> \n", *argv);

	fp = fopen(argv[1], "r");
	if (fp == NULL)
		error("failed to open file %s\n", argv[1]);

	printf("BUFSIZ: %d\n", 1024);

	for (i = 1; (ch = fgetc(fp)) != EOF; i++) {
		fseek(fp, 1, SEEK_CUR);
		fputc(ch, stderr);
	}

	fclose(stdout);

	return 0;
}

#include <stdlib.h>
#include <stdarg.h>

void error(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);

	exit(1);
}
