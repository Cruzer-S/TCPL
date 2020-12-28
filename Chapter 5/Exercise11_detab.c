#include <stdio.h>


int main(int argc, char *argv[])
{
	int pos, k;
	int ch;
	int tabsiz;

	if (argc == 2)
		tabsiz = atoi(argv[1]);
	else
		tabsiz = 4;

	while ((ch = getchar()) != EOF)
	{
		if (ch == '\n') pos = 0;
		else if (ch == '\t') {
			k = tabsiz - pos % tabsiz;
			if (k == 0) k = tabsiz;

			pos += k;

			while (k-- > 0)
				putchar(' ');
		} else pos++;

		if (ch != '\t')
			putchar(ch);
	}

	return 0;
}
