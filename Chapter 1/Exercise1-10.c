#include <stdio.h>

main()
{
    int ch, ck;

    for (ck = EOF; (ch = getchar()) != EOF; ck = EOF) {
        if (ch == '\t') ck = 't';
        if (ch == '\n') ck = 'n';
        if (ch == '\b') ck = 'b';
        if (ch == '\\') ck = '\\';

        if (ck != EOF) {
            putchar('\\');
            ch = ck;
        }
        putchar(ch);
    }
}