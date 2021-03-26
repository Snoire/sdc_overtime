#include <stdio.h>

int main()
{
    int a = -1;
    unsigned int b = (unsigned int) a;

    printf("a: %u\n", (unsigned int) a);
    printf("b: %u\n", b);

    if ((int) b <= 0)
        printf("b: %d\n", b);

    return 0;
}
