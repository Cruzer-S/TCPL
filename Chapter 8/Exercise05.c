#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#if !defined(S_IFMT)
	#define S_IFMT 0160000
#endif

#if !defined(S_IFDIR)
	#define S_IFDIR 0040000
#endif

void fsize(char *);

int main(int argc, char *argv[])
{
	printf("%8s %8s %8s %s\n", 
		    "link", "size", 
			"inode", "filename");

	if (argc == 1)
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}

void dirwalk(char *, void (*fcn)(char *));

void fsize(char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == 1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return ;
	}

	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);

	printf("%8ld %8ld %8ld %s\n", 
			stbuf.st_nlink, stbuf.st_size, 
			stbuf.st_ino, name);
}

#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];	
	struct dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return ;
	}

	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->d_name, ".")  == 0
		 || strcmp(dp->d_name, "..") == 0)
			continue;

		if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
			fprintf(stderr, "dirwalk: name %s/%s too long\n",
					         dir, dp->d_name);
		else {
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*fcn)(name);
		}
	}

	closedir(dfd);
}
