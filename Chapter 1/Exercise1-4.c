#include <stdio.h>

main()
{
    float fahr, cels;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    cels = lower;
    
    printf("%10s%5s%14s\n", "Celsius", "To", "Fahrenheit");
    while (cels <= upper) {
        fahr = (9.0 / 5.0) * cels + 32;
        printf("%7.0f%8s%11.0f\n", cels, "->", fahr);
        cels = cels + step;
    }
}