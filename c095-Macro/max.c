#include <stdio.h>
#define NDEBUG
#include <assert.h>

#define MAX1(A,B)   ((A) > (B) ? (A) : (B))
#define MAX2(A,B)   ({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a > __b ? __a : __b; })
#define MAX3(A,B)   ({ __auto_type __a = (A); __auto_type __b = (B); __a > __b ? __a : __b; })


int test()
{
    int a1 = 1, b1 = 2;
    int a2 = 1, b2 = 2;
    int __a = 1, __b = 2;
    int a3 = 1, b3 = 2;

    printf("max1: %d\n", MAX1(a1, b1));
    printf("max1: %d\n", MAX1(a1++, ++b1));         /* error */
    printf("\n");


    printf("max2: %d\n", MAX2(a2++, ++b2));
    printf("max2: %d\n", MAX2(MAX2(a2, b2), 5));
    printf("max2: %d\n", MAX2(__a, __b));           /* error */
    printf("\n");


    printf("max3(%d++, ++%d): ", a3, b3);
    printf("%d\n", MAX3(a3++, ++b3));

    printf("max3(%d, %d): ", __a, __b);
    printf("\t%d\n", MAX3(__a, __b));

    printf("max3(%d++, ++%d): ", __a, __b);
    printf("%d\n", MAX3(__a++, ++__b));

    printf("max3(MAX(%d++, ++%d), 1): ", __a, __b);
    printf("%d\n", MAX3(MAX3(__a++, ++__b), 1));    /* MAX3 应该是没啥问题的 */

    assert(MAX1(a1++, ++b1) == 3);

    return 0;
}

int main()
{
    test();
    return 0;
}
