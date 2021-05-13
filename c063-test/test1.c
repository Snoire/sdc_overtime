#include <stdio.h>

int main()
{
    /* 同类型运算中：
     * 整型：比int小的，都会转换成int，比int大的不变。
     * */
    int a = (int)(0x80000000);
    int b = 0x7fffffff;

    //unsigned int c = a - b;
    //unsigned int c = (unsigned int)(a - b);
    //unsigned int c = (unsigned int)a - b;
    //unsigned int c = a - (unsigned int)b;
//    long c = a - b;          /* 所以这个会溢出 */

    /* 不同类型运算中：
     * 如果两边均比int小或等于int，那么结果为int。如果两边有比int大的，那么结果为比int大的类型。
     * char < short < int < long < float < double
     * */
    long c = (long)a - b;      /* 不会溢出 */

    printf("a: %d, b: %d, c: %ld\n", a, b, c);

    char c1 = -128;
    char c2 = 127;
    int c3 = c1 - c2;       /* 这个不会 */
    printf("c1: %d, c2: %d, c3: %d\n", c1, c2, c3);

    return 0;
}
