#include <stdio.h>

#define FOLD_VAL 10

int main(void)
{
	int ch, pos;

	for (pos = 0, ch = (EOF + 1); pos >= 0; pos++)
	{
		if (pos == 0) {
			while ((ch = getchar()) == ' ' || ch == '\t' || ch == '\n');
			if (ch == EOF) pos = -2;
			else putchar(ch);
		} else {
			ch = getchar();
			if (ch == EOF) pos = -2;
			else putchar(ch);

			if (ch == '\n') 
				pos = -1;
			else if (pos >= FOLD_VAL) {
				pos = -1;
				putchar('\n');
			}
		}
	}

	return 0;
}
