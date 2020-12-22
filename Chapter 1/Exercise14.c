#include <stdio.h>

#define MAX_LENGTH 26
#define MAX_FREQNC 10

main()
{
	int length[MAX_LENGTH];
	int i, j, repeat;
	int ch;

	double max, step, k;

	for (i = 0; i < MAX_LENGTH; i++)
		length[i] = 0;

	while ((ch = getchar()) != EOF)
	{
		if ('a' <= ch && ch <= 'z')
			length[ch - 'a']++;
		else if ('A' <= ch && ch <= 'Z')
			length[ch - 'A']++;
	}

	max = length[0];
	for (i = 1; i < MAX_LENGTH; i++)
		if (max < length[i])
			max = length[i];
	step = max / MAX_FREQNC;

	printf("Alphabet length historgram \n");
	printf("Frequency");

	i = 0;
	for (k = step; i < MAX_FREQNC; k = k + step) {
		printf("%3d", (int)k);
		i++;
	} putchar('\n');

	printf("Alphabet\n");
	for (i = 0; i < MAX_LENGTH; i++)
	{
		printf("%3s%2c%6s", "", 'A' + i, "");

		repeat = (int)((length[i] / max) * MAX_FREQNC * 3.0);
		for (j = 0; j < repeat; j++)
			putchar('@');
		putchar('\n');
	}
}
