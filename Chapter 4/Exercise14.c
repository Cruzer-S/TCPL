#include <stdio.h>

#define swap(t, x, y) t = x, x = y, y = t

int main(void)
{
	int a, b, t;

	scanf("%d %d", &a, &b);

	swap(t, a, b);

	printf("%d %d\n", a, b);

	return 0;
}
