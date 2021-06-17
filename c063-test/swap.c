// https://www.runoob.com/w3cnote/c-swap-data.html
#include <stdio.h>

void swap(int *a, int *b)   /* 可能会溢出，但是为啥算出的结果还是对的？ */
{
    *a = *a + *b;
    printf("sum: %d, %#.8x\n", *a, *a);
    *b = *a - *b;
    *a = *a - *b;
}

void swap1(int *a, int *b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int main()
{
//    int a = 3;
//    int b = 4;
#if 0
    int a = 0x80000000;
    int b = (int) 0x80000000 + 1;
    printf("b: %#.4x\n", b);
    //int b = 0x7ffffffe;
#else
    int a = 0xffffffff;
    int b = 0xfffffffe; /* 换了好几个，好像一直都是对的 */
#endif

    swap(&a, &b);
    printf("a: %d, b: %d\n", a, b);

    swap1(&a, &b);
    printf("a: %d, b: %d\n", a, b);

    return 0;
}
