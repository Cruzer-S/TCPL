#include <stdio.h>

#define MAX_LENGTH 10
#define MAX_FREQNC 10
#define PRGRS_BAR '#'

main()
{
	int length[MAX_LENGTH];
	int i, j, repeat;
	int ch, state;

	double max, step, k;

	for (i = 0; i < MAX_LENGTH; i++)
		length[i] = 0;

	for (state = 0; (ch = getchar()) != EOF; state++)
	{
		if (ch == '\n' || ch == ' ' || ch == '\t') {
			if (state > 0) {
				if (state > MAX_LENGTH - 1) state = MAX_LENGTH;
				length[state - 1]++;
			}
			state = -1;
		}
	}

	max = length[0];
	for (i = 1; i < MAX_LENGTH; i++)
		if (max < length[i])
			max = length[i];
	step = max / MAX_FREQNC;

	printf("Word length historgram \n");
	printf("Frequency");

	i = 0;
	for (k = step; i < MAX_LENGTH; k = k + step) {
		printf("%3d", (int)k);
		i++;
	} putchar('\n');

	printf("Length\n");
	for (i = 0; i < MAX_LENGTH; i++)
	{
		if (i == MAX_LENGTH - 1)
			printf("%2s", "+");
		else
			printf("%2s", "");
		printf("%2d%6s", i + 1, "");

		repeat = (int)((length[i] / max) * MAX_FREQNC * 3.0);
		for (j = 0; j < repeat; j++)
			putchar(PRGRS_BAR);
		putchar('\n');
	}
}
