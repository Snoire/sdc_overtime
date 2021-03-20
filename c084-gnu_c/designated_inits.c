#include <stdio.h>
/* https://gcc.gnu.org/onlinedocs/gcc-10.2.0/gcc/Designated-Inits.html#Designated-Inits */

int main()
{
    int a[6] = { [5] = 1, [2] = 4 };  /* 其余值默认 0 */
    for (int i = 0; i < sizeof(a)/sizeof(int); i++)
        printf("a[%d] = %d\n", i, a[i]);

    printf("\n");
    int b[6] = { [1 ... 3] = 1, [4 ... 5] = 2 };  /* 其余值默认 0 */
    for (int i = 0; i < sizeof(b)/sizeof(int); i++)
        printf("b[%d] = %d\n", i, b[i]);

    printf("\n");
    struct point {
        int a;
        char b;
        short c;
    };
    struct point p = { .b = 'b', .a = 10 };
    printf("p.a = %d\n", p.a);
    printf("p.b = %c\n", p.b);
    printf("p.c = %d\n", p.c);

    return 0;
}
