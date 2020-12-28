#include <stdio.h>

#define DEFAULT_TAB_START 0
#define DEFAULT_TAB_STOP  4

int main(int argc, char *argv[])
{
	int pos, k, i;
	int ch, temp, space;
	int tab_start, tab_stop;

	if (argc == 2) {
		tab_stop  = atoi(argv[1]);
		tab_start = atoi(argv[2]);
	} else {
		tab_start = DEFAULT_TAB_START;
		tab_stop  = DEFAULT_TAB_STOP;
	}

	while ((ch = getchar()) != EOF)
	{
		if (ch == '\n') pos = 0;
		else if (ch == ' ') {
			for (space = 1; (temp = getchar()) == ' '; space++) {
				if ((pos + space) == tab_start)
					break;

				if ((pos + space) % tab_stop == 0) {
					putchar('\t');
					pos += space;
					space = 0;
				}
			}

			if ((pos + space) == tab_start) {
				putchar('\t');
				pos = tab_start + 1;
			} else {
				pos += space + 1;

				while (space-- > 0)
					putchar(' ');
			}
		} else pos++;

		if (ch != ' ')
			putchar(ch);
		else
			putchar(temp);
	}
	return 0;
}


