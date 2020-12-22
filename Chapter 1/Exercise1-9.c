#include <stdio.h>

main()
{
    int ch;

    for (; (ch = getchar()) != EOF;) {
        if (ch == ' ') {
            putchar(' ');
            while ((ch = getchar()) == ' ') ;
        }
        
        putchar(ch);
    }
}