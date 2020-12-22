/*****************************/
#include <stdio.h>

#define ENTER 1
#define LEAVE 0

int main()
{
	int state, seq1, seq2;
/************************/
	state = LEAVE;
	while ((seq1 = getchar()) != EOF) {
		if (seq1 == '\"'  && seq2 != '\\') {
			if (state == ENTER)
				state = LEAVE;
			else
				state = ENTER; /*
				/*******
			*/
			putchar(seq1);
		} else if (seq1 == '/' && state == LEAVE) {
			if ((seq2 = getchar()) == '*') {
				for (seq1 = getchar(), seq2 = getchar();
					 seq1 != '*' || seq2 != '/';
					 seq1 = seq2, seq2 = getchar());
			} else {
				putchar(seq1);
				putchar(seq2);
			}
		} else putchar(seq1);

		seq2 = seq1;
	}

	return 0;
}

/************************/
