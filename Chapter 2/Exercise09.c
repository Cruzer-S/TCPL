#include <stdio.h>

int bitcount(unsigned );

int main()
{
	printf("bitcount(0xFFAA): %d \n", bitcount(0xFFAA));

	return 0;
}

int bitcount(unsigned x)
{
	int b = 0;

	while (x > 0) {
		b++;
		x &= (x - 1);
	}

	return b;
}

