#include <stdio.h>

int main()
{
    unsigned short a, b;
    int i = 0;

    a = 12;
    b = 1800;

    /* 把两个 short 合成一个 int */
    i = a<<16;
    i += b;

    printf("a: %hu, b: %hu\n", a, b);
    /* 这样拆分 */
    printf("a: %hu, b: %hu\n", i>>16, i);
    printf("a: %hu, b: %hu\n", i>>16, (short) i);
    

    return 0;
}
