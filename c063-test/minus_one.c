#include <stdio.h>

int main()
{
    int a = -1;
    unsigned int b = (unsigned int) a;

    printf("a: %u\n", (unsigned int) a);
    printf("b: %u\n", b);

    return 0;
}
