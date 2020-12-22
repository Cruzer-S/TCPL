#include <stdio.h>

int main(void)
{
    int ch;

    for (; (ch = getchar()) != EOF; ) {
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            putchar('\n');
            while (ch == ' ' || ch == '\t' || ch == '\n') 
                ch = getchar();
        }
        putchar(ch);
    }
    
    return 0;
}