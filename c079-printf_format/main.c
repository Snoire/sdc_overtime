#include <stdio.h>

int main()
{
    int a = -12;
    unsigned int b = 12;

    printf("a %d, b %d\n", a, b);
    printf("a %d, b %u\n", a, b);

    return 0;
}

