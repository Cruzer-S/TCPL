#include <stdio.h>

main()
{
    printf("getchar() != EOF: %d\n", getchar() != EOF);
}

/* when zero-length file comes to input file, the value of statement is zero.
   otherwise, the value of statement is non-zero value such as 1.               */