#include <stdio.h>

int main()
{
    double a, b;
    int c;

    a = 4.0;
    b = 40/10.0;
    c = 4;

    printf("a == b: %d\n", a == b);  // 准确的小数，可以相等
    printf("a == c: %d\n", a == c);  // 整数和小数居然也相等

    return 0;
}

