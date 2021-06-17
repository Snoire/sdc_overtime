#include <stdio.h>

void swap(int *a, int *b)   /* 可能会溢出 */
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int main()
{
    int a = 3;
    int b = 4;
    swap(&a, &b);

    printf("a: %d, b: %d\n", a, b);
    return 0;
}
