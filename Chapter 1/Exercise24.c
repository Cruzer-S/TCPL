#include <stdio.h>

#define ENTER 1
#define LEAVE 0

int main()
{
	int state, seq1, seq2;
	int parentheses, braces, brackets;

	parentheses = braces = brackets = 0;
	state = LEAVE;
	while ((seq1 = getchar()) != EOF) {
		if (seq1 == '\"' && seq2 != '\\') {
			if (state == ENTER)
				state = LEAVE;
			else
				state = ENTER;
		} else if (state == LEAVE && seq2 != '\'') {
			if (seq1 == '(') parentheses++;
			else if (seq1 == ')') parentheses--;
			else if (seq1 == '{') braces++;
			else if (seq1 == '}') braces--;
			else if (seq1 == '[') brackets++;
			else if (seq1 == ']') brackets--;
		}

		seq2 = seq1;
	}

	if (parentheses == 0 && braces == 0 && brackets == 0)
		printf("clear \n");
	else
		printf("something wrong %d %d %d\n", parentheses, braces, brackets);

	return 0;
}
