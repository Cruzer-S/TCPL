#include <stdio.h>
#include <ctype.h>

#define MAXCHAR 50
#define TABSIZE 4

int main(void)
{
	int ch, count = 0;

	while ((ch = getchar()) != EOF) 
	{
		if (isprint(ch) || isspace(ch)) {
			if (ch == '\n') {
				count = 0;
			} else if (ch == '\t') {
				count += TABSIZE;
			} else {
				count++;
			}

			putchar(ch);
		} else {
			char temp[12];
			int i = 0, k = 0;

			k += sprintf(temp, "0x%x ", ch);
			while (i < k) {
				if (count++ >= MAXCHAR) {
					count = 0; 
					putchar('\n');
					continue;
				}
				
				putchar(temp[i++]);
			}
		}

		if (count >= MAXCHAR) {
			count = 0; 
			putchar('\n');
			continue;
		}
	}

	return 0;
}
