#include <stdio.h>

unsigned setbits(unsigned , unsigned , unsigned , unsigned );
void print_bit(unsigned );
unsigned invert(unsigned , unsigned , unsigned );

int main()
{
	printf("%#x \n", invert(0xFFFF, 4, 8));

	return 0;
}

void print_bit(unsigned x)
{
	int i;
	for (i = 0; x != 0; i++) {
		if ( i % 4 == 0)
			putchar(' ');
		printf("%d", x & 0x01);
		x >>= 1;
	} putchar('\n');
}

unsigned invert(unsigned x, unsigned p, unsigned n)
{
	int i;
	unsigned mask;

	for (i = 0, mask = ~0; i < n; i++)
		x ^= 1 << (p + i);

	return x;
}
