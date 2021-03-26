#include <stdio.h>

int main()
{
    int a = -12;
    unsigned int b = 12;
    int c = 866667;
    int d = 975000;

    printf("a %d, b %d\n", a, b);
    printf("a %d, b %u\n", a, b);

    if (c%1000)
        printf("c/1000 = %.1f\n", c / 1000.0);
    else
        printf("c/1000 = %d\n", c / 1000);

    if (d%1000)
        printf("d/1000 = %.1f\n", d / 1000.0);
    else
        printf("d/1000 = %d\n", d / 1000);

    return 0;
}

