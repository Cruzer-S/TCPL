#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
	printf("  signed char  : %20d ~ %d\n", CHAR_MIN, CHAR_MAX);
	printf("unsigned char  : %20u ~ %u\n\n", 0, UCHAR_MAX);

	printf("  signed short : %20d ~ %d\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned short : %20d ~ %d\n\n", 0, USHRT_MAX);

	printf("  signed int   : %20d ~ %d\n", INT_MIN, INT_MAX);
	printf("unsigned int   : %20u ~ %u\n\n", 0, UINT_MAX);

	printf("  signed long  : %20ld ~ %ld\n", LONG_MIN, LONG_MAX);
	printf("unsigned long  : %20ld ~ %lu\n\n", 0, ULONG_MAX);

	printf("         float : %20g ~ %g\n", FLT_MIN, FLT_MAX);
	printf("        double : %20g ~ %g\n", DBL_MIN, DBL_MAX);
	printf("   long double : %20lg ~ %lg\n", LDBL_MIN, LDBL_MAX);

	return 0;
}
