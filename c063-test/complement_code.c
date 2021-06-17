#include <stdio.h>

int main()
{
    short a = 6;
    short b = -18;

//    printf("a: %hd, 0x%04hx\n", a, a);
//    printf("b: %hd, 0x%04hx\n", b, b);
    printf("a: %hd, %#.4hx\n", a, a);
    printf("b: %hd, %#.4hx\n", b, b);

    return 0;
}
