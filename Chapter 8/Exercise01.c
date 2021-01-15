#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define STDIN  0
#define STDOUT 1
#define STDERR 2

#define PERMS 0666

int filecopy(int , int );
void error(char *fmt, ...);

int main(int argc, char *argv[])
{
	const char *origin = *argv;

	if (argc == 1) {
		if (filecopy(STDIN, STDOUT) != 0)
			error("%s: failed to filecopy \n", *argv);
	} else {
		int fd;

		while (*++argv != NULL)
		{
			fd = open(*argv, O_RDONLY, 0);
			if (fd == -1)
				error("%s: failed to open file %s\n", origin, *argv);

			if (filecopy(fd, STDOUT) != 0)
				error("%s: failed to filecopy \n", origin);

			close(fd);
		}
	}
	
	return 0;
}

int filecopy(int in, int out)
{
	int len;
	char buffer[BUFSIZ];

	if ((len = read(in, buffer, BUFSIZ)) > 0)
		if (write(out, buffer, len) != len)
			return len;

	return 0;
}

void error(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");

	va_end(args);

	exit(1);
}
