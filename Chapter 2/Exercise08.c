#include <stdio.h>
#include <limits.h>

#ifndef UINT_WIDTH
#define UINT_WIDTH (CHAR_BIT * sizeof(unsigned))
#endif

unsigned rightrot(unsigned , unsigned );

int main()
{
	printf("%#x \n", rightrot(0x1234FEDC, 16));

	return 0;
}

unsigned rightrot(unsigned x, unsigned n)
{
	unsigned save;
	int i;

	for (i = 0; i < n; i++) {
		save = x & 0x01;
		x >>= 1;
		x |= (save << (UINT_WIDTH - 1));
	}

	return x;
}
