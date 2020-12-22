#include <stdio.h>

main()
{
    float fahr, cels;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    
    printf("%10s%5s%12s\n", "Fahrenheit", "To", "Celsius");
    while (fahr <= upper) {
        cels = (5.0 / 9.0) * (fahr - 32.0);
        printf("%5.0f%10s%11.1f\n", fahr, "->", cels);
        fahr = fahr + step;
    }
}