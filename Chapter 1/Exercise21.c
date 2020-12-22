#include <stdio.h>

#define TABSIZ 4

int main(void)
{
	int pos, k, i;
	int ch, temp, space;

	while ((ch = getchar()) != EOF)
	{
		if (ch == '\n') pos = 0;
		else if (ch == ' ') {
			for (space = 1; (temp = getchar()) == ' '; space++) {
				if ((pos + space) % 4 == 0) {
					putchar('\t');
					pos += space;
					space = 0;
				}
			}
		
			pos += space + 1;

			while (space-- > 0)
				putchar(' ');
		} else pos++;

		if (ch != ' ')
			putchar(ch);
		else
			putchar(temp);
	}
	return 0;
}


