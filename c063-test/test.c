#include <stdio.h>
/* */

int main()
{
#if 0
    int sum = 0;
    unsigned char noise = -81;
    printf("(int) noise: %d\n", (int) noise);
    printf("noise: %d\n", noise);
    sum += noise;
    printf("sum: %d\n", sum);
#elif 1
    signed char a = -81; /* char 有可能是 signed char，也有可能是 unsigned char */
    unsigned char b = a;
    printf("a: %hhu\n", a);
    printf("b: %hhd\n", b);
#else

    char *str = "0";
//    char *str2 = "56";

    if (*str == '3' || *str == '5' || *str == '6')
        printf("ok\n");
    else
        printf("oh no\n");

    str = NULL;
    if (*str != 0)
        printf("str != 0");
#endif

    return 0;
}
