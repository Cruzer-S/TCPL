#include <fcntl.h>
#include <unistd.h>

#if !defined(NULL)
#define NULL		0
#endif
#define EOF			(-1)
#define BUFSIZ		1024
#define OPEN_MAX	20

typedef struct _iobuf {
	int		cnt;
	char	*ptr;
	char	*base;
	char	flag[5];
	int		fd;
} FILE;

FILE _iob[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0, { 1, 0, 0, 0, 0 }, 0 },
	{ 0, (char *) 0, (char *) 0, { 0, 1, 0, 0, 0 }, 1 },
	{ 0, (char *) 0, (char *) 0, { 0, 1, 1, 0, 0 }, 2 }
};

#define stdin		(&_iob[0])
#define stdout		(&_iob[1])
#define stderr		(&_iob[2])

enum _flags {
	_READ,
	_WRITE,
	_UNBUF,
	_EOF,
	_ERR
};

int _fillbuf(FILE *);
int _flushbuf(int , FILE *);
FILE *fopen(char *, char *);

#define getc(p)		(--(p)->cnt >= 0 \
				?	(unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p)	(--(p)->cnt >= 0 \
				?	*(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()	getc(stdin)
#define putchar(x)	putc((x), stdout)

#define PERMS 0666

void error(char *fmt, ...);

int main(int argc, char *argv[])
{
	FILE *fp;
	int ch;

	if (argc < 2)
		error("usage: %s <file> \n", *argv);

	fp = fopen(argv[1], "r");
	if (fp == NULL)
		error("failed to open file %s\n", argv[1]);

	while ((ch = getc(fp)) != EOF)
		putc(ch, stdout);

	return 0;
}

FILE *fopen(char *name, char *mode)
{
	FILE *fp;
	int fd;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;

	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ( ((fp->flag[_READ] + fp->flag[_WRITE])) == 0 )
			break;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else fd = open(name, O_RDONLY, 0);

	if (fd == -1)
		return NULL;

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag[(*mode == 'r') ? _READ : _WRITE]++;
	
	return fp;
}

#include <stdlib.h>

int _fillbuf(FILE *fp)
{
	int bufsize;

	if (!fp->flag[_READ]
	||  (fp->flag[_EOF] + fp->flag[_WRITE]) != 0)
		return EOF;

	bufsize = fp->flag[_UNBUF] ? 1 : BUFSIZ;
	if (fp->base == NULL)
		if ((fp->base = (char *)malloc(bufsize)) == NULL)
			return EOF;

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag[_EOF]++;
		else
			fp->flag[_ERR]++;

		fp->cnt = 0;
		return EOF;
	}

	return (unsigned char)*fp->ptr++;
}

int _flushbuf(int ch, FILE *fp)
{
	int bufsize;

	if (!fp->flag[_WRITE]
	||  (fp->flag[_EOF] + fp->flag[_READ]) != 0)
		return EOF;

	bufsize = fp->flag[_UNBUF] ? 1 : BUFSIZ;
	if (fp->base == NULL) {
		if ((fp->base = (char *)malloc(bufsize)) == NULL)
			return EOF;

		fp->ptr = fp->base;
		fp->cnt = bufsize - 1;
	}
	*fp->ptr = ch;

	if (--fp->cnt <= 0) {
		if (write(fp->fd, fp->base, bufsize) != bufsize) {
			fp->flag[_ERR]++;
			return EOF;
		}

		fp->ptr = fp->base - 1;
		fp->cnt = bufsize - 1;
	}

	return (unsigned char)*fp->ptr++;
}

#include <stdarg.h>

void error(char *fmt, ...)
{
	va_list args;

	int fprintf(FILE *, const char *, ...);
	int vfprintf(FILE *, const char *, va_list );

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");

	va_end(args);

	exit(1);
}
