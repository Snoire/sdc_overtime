// https://leetcode-cn.com/circle/article/KBnaqU/
#include <stdio.h>
#include <stdlib.h>

static void inline printarr(int *arr, int num)
{
    for (int i = 0; i < num; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int cmp(const void *a, const void *b) {
    /* 一个非常小的 int 减去非常大的 int，结果溢出，int 放不下 */
//    return *(int*)a - *(int*)b;  /* a、b分别指向arr1/arr2中某个元素 */

    /* 这种写法倒是不会溢出，但是如果只相差 1，除 2 后会变成 0，就不对了 */
//    return ((long)*(int*)a - *(int*)b)/2;

    /* https://www.runoob.com/cprogramming/c-function-qsort.html */
#if 0
    const int *aa = a;
    const int *bb = b;
    if (*aa < *bb)
        return -1;
    else if (*aa > *bb)
        return 1;
    else 
        return 0;
#else
    const int *aa = a;
    const int *bb = b;
    return (*aa > *bb) - (*aa < *bb);
#endif
}

int main()
{
    int arr1[] = { 5, 0x7fffffff, 6, 5, (int)(0x80000000), -3, 0, 1, 4 };
    printarr(arr1, sizeof(arr1)/sizeof(int));

    qsort(arr1, sizeof(arr1) / sizeof(arr1[0]), sizeof(arr1[0]), cmp);
    printarr(arr1, sizeof(arr1)/sizeof(int));
    printf("\n");

    int *arr2 = (int*)calloc(8, sizeof(int));
    arr2[0] = 5; arr2[1] = 8; arr2[2] = 6; arr2[3] = 1; arr2[4] = -3; arr2[5] = 0; arr2[6] = 1; arr2[7] = 4; 
    printarr(arr2, 8);

    qsort(arr2, 8, sizeof(arr2[0]), cmp);  /* 如果将8改成sizeof(arr2) / sizeof(arr2[0])，排序会失败 */
    printarr(arr2, 8);
}

