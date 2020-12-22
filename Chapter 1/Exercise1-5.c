#include <stdio.h>

main()
{
    int fahr;

    printf("%10s%5s%12s\n", "Fahrenheit", "To", "Celsius");
    for (fahr = 300; fahr >= 0; fahr = fahr - 20)
        printf("%5d%10s%11.1f\n", fahr, "->", (5.0 / 9.0) * (fahr - 32));
}