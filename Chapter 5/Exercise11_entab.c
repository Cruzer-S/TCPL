#include <stdio.h>

int main(int argc, char *argv[])
{
	int pos, k, i;
	int ch, temp, space;
	int tabsiz;

	if (argc == 2)
		tabsiz = atoi(argv[1]);
	else
		tabsiz = 4;

	while ((ch = getchar()) != EOF)
	{
		if (ch == '\n') pos = 0;
		else if (ch == ' ') {
			for (space = 1; (temp = getchar()) == ' '; space++) {
				if ((pos + space) % tabsiz == 0) {
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


