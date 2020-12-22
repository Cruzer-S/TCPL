#include <stdio.h>

main()
{
    int ch, count;

    for (count = 0; (ch = getchar()) != EOF; ) {
        if (ch == '\n') count++;
        if (ch ==  ' ') count++;
        if (ch == '\t') count++;
    }

    printf("count: %d\n", count);
}