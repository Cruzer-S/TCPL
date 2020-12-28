#include <stdio.h>

#define DEFAULT_TAB_START 0
#define DEFAULT_TAB_STOP 4

int main(int argc, char *argv[])
{
	int pos, k;
	int ch;
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
		else if (ch == '\t') {
			if (pos < tab_start) 
				k = tab_start - pos;
			else 
				k %= tab_stop;

			if (k == 0) 
				k = tab_stop;
			else
				k = tab_stop - k;

			pos += k;

			while (k-- > 0)
				putchar(' ');
		} else pos++;

		if (ch != '\t')
			putchar(ch);
	}

	return 0;
}
