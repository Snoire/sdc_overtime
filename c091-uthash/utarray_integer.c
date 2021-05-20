#include <stdio.h>
#include "utarray.h"

int intsort(const void *a, const void *b)
{
    int _a = *(const int *) a;
    int _b = *(const int *) b;
    return (_a < _b) ? -1 : (_a > _b);
}

int main()
{
    UT_array *nums;
    int i, *p = NULL;
    int num;

    utarray_new(nums, &ut_int_icd);
    for (i = 0; i < 10000; i++) {
        num = rand() % 2567;
        utarray_push_back(nums, &num);
//        utarray_push_back(nums, &i);
    }
    utarray_sort(nums, intsort);

//    for (p = (int *) utarray_front(nums); p != NULL; p = (int *) utarray_next(nums, p)) {
    while ((p = (int *) utarray_next(nums, p))) {       /* 有啥区别 *//* 。。为啥有时候没问题，有时候有问题 */
        printf("%d ", *p);      /* p 为 NULL 时，utarray_next 返回第一个元素 */
    }

    printf("\n");
    utarray_free(nums);

    return 0;
}
