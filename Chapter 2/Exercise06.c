#include <stdio.h>

unsigned setbits(unsigned , unsigned , unsigned , unsigned );
void print_bit(unsigned );
unsigned clearbits(unsigned , unsigned , unsigned );

int main()
{
	printf("%#x \n", setbits(0xFFFF, 4, 8, 0xAB));

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

unsigned clearbits(unsigned x, unsigned p, unsigned n)
{
	int i;
	unsigned mask;

	for (i = 0, mask = ~0; i < n; i++)
		mask &= ~(1 << p + i);

	return x & mask;
}

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y)
{
	int i;

	x = clearbits(x, p, n);

	for (i = 0; i < n; i++) {
		x |= (y & 0x01) << (p + i);
		y >>= 1;
	}

	return x;
}
