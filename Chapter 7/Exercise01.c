#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE(X) (sizeof(X) / sizeof(X[0]))

int main(int argc, char *argv[])
{
	const char *type_name[] = {
		"lower", "upper"
	};
	int i, ch;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <type>\n", argv[0]);
		exit(1);
	}

	for (i = 0; i < SIZE(type_name); i++)
		if (!strcmp(argv[1], type_name[i]))
			break;

	if (i == SIZE(type_name)) {
		fprintf(stderr, "wrong type name: %s\n", argv[1]);
		exit(1);
	}

	switch (i) {
	case 0: /* lower-case */
		while ((ch = getchar()) != EOF)
			putchar(tolower(ch));
		break;

	case 1: /* upper-cae */
		while ((ch = getchar()) != EOF)
			putchar(toupper(ch));
		break;

	default: /* error */
		fprintf(stderr, "something wrong\n");
		exit(1);
		break;
	}

	return 0;
}
