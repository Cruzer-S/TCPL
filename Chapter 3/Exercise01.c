#include <stdio.h>

int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (low <= high) {
		mid = (low + high) / 2;

		if (v[mid] == x) return mid;

		(x < v[mid]) ? 
			(high = mid - 1) : 
			(low  = mid + 1);
	}
}

int main()
{
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	printf("binsearch(5, arr, 10): %d \n",
			binsearch(5, arr, 10));

	return 0;
}
