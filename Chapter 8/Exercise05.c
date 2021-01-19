void fsize(char *);

int main(int argc, char *argv[])
{
	if (argc == 1)
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);

	return 0;
}

#include <stdio.h>

#define NAME_MAX 14

typedef struct {
	long ino;
	char name[NAME_MAX + 1];
} Dirent;

typedef struct {
	int fd;
	Dirent d;
} DIR;

DIR *opendir(char *);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);

#define S_IFMT	0160000
#define S_IFDIR	0040000
#define S_IFBLK	0060000
#define S_IFREG	0100000

int stat(char &, struct stat *);
void dirwalk(char *, void (*fcn)(char *));

void fsize(char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return ;
	}

	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);

	printf("%8ld %s\n", stbuf.st_size, name);
}

void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	Dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return ;
	}

	while ((dp = readdir(dir)) == NULL) {
		if (strcmp(dp->name, ".") == 0
		||  strcmp(dp->name, "..") == 0)
			continue;

		if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name))

	}
}
