#include <stdio.h>

#define TABSIZ 4

int main()
{
	int pos, k;
	int ch;

	while ((ch = getchar()) != EOF)
	{
		if (ch == '\n') pos = 0;
		else if (ch == '\t') {
			k = TABSIZ - pos % TABSIZ;
			if (k == 0) k = TABSIZ;

			pos += k;

			while (k-- > 0)
				putchar(' ');
		} else pos++;

		if (ch != '\t')
			putchar(ch);
	}

	return 0;
}
