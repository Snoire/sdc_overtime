// https://leetcode-cn.com/circle/article/KBnaqU/
#include <stdio.h>
#include <stdlib.h>
#include "utarray.h"

static void inline printarr(int (*arr)[2], int num)
{
    for (int i = 0; i < num; i++) {
        printf("(%d,%d) ", arr[i][0], arr[i][1]);
    }
    printf("\n");
}

/* int (*arr)[2] 和 int **arr 是不一样的，指向的空间就不一样，一个是连续的，一个是分散的 */
static void inline printarr2(int **arr, int num)
{
    for (int i = 0; i < num; i++) {
        printf("(%d,%d) ", arr[i][0], arr[i][1]);
    }
    printf("\n");
}

void printarr3(UT_array *arr3)
{
#if 1
    printf("\narr3:");
    int **p = NULL;
    /* utarray_next 取出的是每个元素的地址，由于每个元素本身就是地址，所以元素的地址就是二级指针了 */
    /* 这样做看上去好像多此一举，直接把元素的内容（指针）传过来不就得了？
     * 但是考虑到 utarry 是通用型的结构，所以取每个元素的地址才是适用于所有数据的方式 */
    while ((p = (int **) utarray_next(arr3, p))) {
        printf("(%d,%d) ", p[0][0], p[0][1]);
//        printf("%p %p\n", p, *p);
    }
    printf("\n");
#else   /* 说了多少遍，数组和指针是不一样的! */
    printf("\narr3:");
    int (*p)[2] = NULL;
    while ((p = (int (*)[2]) utarray_next(arr3, p))) {
        //printf("([%p]%d,%d) ", p, p[0][0], p[0][1]);
        printf("%p %p\n", p, *p);
    }
    printf("\n\n");
#endif
}

int cmp1(const void *a, const void *b) {
    int *m = (int*)a, *n = (int*)b;  /* 此处为了看起来清晰一些，定义m、n来取代a、b，这里可以看到，入参的是一维指针类型，也就是之前所说的arr1的某个元素，即以为指针 */
    if (m[0] != n[0]) {
        return m[0] - n[0];
    }
    else {
        return m[1] - n[1];
    }
}

/* 传进来的是 arr 的元素地址，也就是 &arr[0]、&arr[1] 这样子，或者说 arr + 0、arr + 1 */
int cmp2(const void *a, const void *b) {
    int *m = *(int**)a, *n = *(int**)b;  /* 与上面不同的是，这里入参的是二维指针，即arr2入参，重要！！！ */
    if (m[0] != n[0]) {                  /* 并不是 arr2 入参，虽然的确是 int ** */
        return m[0] - n[0];
    }
    else {
        return m[1] - n[1];
    }
}

void intptr_dtor(void *_elt) {	/* utarry_free 的时候，把每个 int (*)[2] 指针指向的数据也释放掉了 */
  int (*elt)[2] = *(int (**)[2])_elt;	/* 可以这样写? */ /* 还真的可以 */
  if (elt) free(elt);
  printf("free: %p\n", elt);
}

int main()
{
    int arr1[10][2] = { {1, 5}, {2, 3}, {0, 1}, {8, 3}, {1, 0}, {4, 8}, {3, 2}, {2, 9}, {2, 1}, {1, 0} };
    printarr(arr1, sizeof(arr1)/sizeof(int [2]));

//    qsort(arr1, 10, sizeof(arr1) / 10, cmp1);  //qsort(arr1, 10, sizeof(int*), cmp1);
    qsort(arr1, 10, sizeof(int [2]), cmp1);  /* 你说的是这里吧 */
    printarr(arr1, sizeof(arr1)/sizeof(int [2]));
    printf("\n");


    srand((unsigned int) -1);
    int **arr2 = (int**)calloc(10, sizeof(int*));

    UT_icd arr_icd = { sizeof(int (*)[2]), NULL, NULL, intptr_dtor };    /* arr3 里面存放的是 int (*)[2] 指针 */
    UT_array *arr3; /* 和 arr2 一样，不过是用 utarray 实现的 */
    utarray_new(arr3, &arr_icd);    /* arr3 和 arr2 分别维护了一个 10 个元素的指针数组
                                    不过，每个元素（int (*)[2]）指向的数据是同一份 */

    for (int i = 0; i < 10; i++) {
        arr2[i] = (int*)calloc(2, sizeof(int));
        arr2[i][0] = rand() % 2567;
        arr2[i][1] = rand() % 2567;

//        int *p = arr2[i];
		utarray_push_back(arr3, &arr2[i]);	/* 如果写 arr2[1]，那就是把 arr2[1] 指向的内容拷到 utarray 里 */
        printf("push: arr2[%d]: %p\n", i, arr2[i]);
    }
    /* 这个不行。。 */
    //printarr((int (*)[2]) arr2, 10);
    printarr2(arr2, 10);
    qsort(arr2, 10, sizeof(int*), cmp2);  /* 由于之前说过对指针sizeof的话，得到的大小是指针大小，而入参的是二维指针，而非二维数组，二维指针的元素为一维指针，因此这里的单个元素大小是以为int*的大小 */

    printarr2(arr2, 10);
#if 0
    qsort(arr2, 10, sizeof(int) * 2, cmp2);  /* 单个元素大小也可以写成sizeof(int) * 2，因为arr2中每个元素都包含两个int型 */  /* ??? */
    printarr((int (*)[2]) arr2, 10);
#endif

    printarr3(arr3);
    /* 只是把指针数组排序了，真正的数据一直没动过 */
    utarray_sort(arr3, cmp2);   /* 直接调用 cmp2，和 arr2 是一样的 */
    printarr3(arr3);


    printf("\n\narr: %p\n", arr2);
    printf("arr[0]: %p\n", arr2[0]);
    printf("arr[0][0]: %d\n", arr2[0][0]);
    printf("sizeof(int **): %ld\n", sizeof(int **));
    printf("sizeof(int *): %ld\n", sizeof(int *));
    int (*p)[2] = (int (*)[2]) arr2;  /* 指针的类型转换，虽然指针的值不会变，但是怎么看待指针指向的数据的方式变了 */
    printf("p: %p\n", p);
    printf("p[0]: %p\n", p[0]);  /* 看，这里就不一样了 */
    printf("p[0][0]: %d\n", p[0][0]);
    printf("sizeof(int (*p)[2]): %ld\n", sizeof(int (*)[2]));
    printf("sizeof(int [2]): %ld\n\n", sizeof(int [2]));
    /* 还不懂的话，我画个图给你看 */

    utarray_free(arr3);
}

/*
 *                                这里还需要再寻址一次
 *                                +-------------------
 *                                |                                     two int
 *    +------+                    +- +-------+                       0 +-------+
 *    | arr2 |  ----------------> 0  |  ptr  |    ---------------->  1 |-------|          <------------  arr3 另外维护了一张表，也指向这些数据
 *    +------+                       |-------|                         +-------+        +-------+
 *       |                        1  |  ptr  |    ----------------------------------->  |-------|
 *       |                           |-------|                 +-------+                +-------+
 *       |                        2  |  ptr  |    --------->   |-------|
 *       |                           |-------|                 +-------+       +-------+
 *       |                        3  |  ptr  |    ------------------------->   |-------|
 *       |                           |-------|           +-------+             +-------+
 *       |                        4  |  ptr  |    ---->  |-------|
 *       |                           |-------|           +-------+                                +-------+
 *       |                        5  |  ptr  |    -------------------------------------------->   |-------|
 *       |                           |-------|                           +-------+                +-------+
 *       |                        6  |  ptr  |    ------------------->   |-------|
 *       |                           |-------|                           +-------+             +-------+
 *       |                        7  |  ptr  |    ----------------------------------------->   |-------|
 *       |                           |-------|                   +-------+                     +-------+
 *       |                        8  |  ptr  |    ----------->   |-------|
 *       |                           |-------|                   +-------+                +-------+
 *       |                        9  |  ptr  |    ------------------------------------>   |-------|
 *       |                           +-------+                                            +-------+
 *       |
 *       |                        +------------------------------+
 *       |                        |                              |
 *    +-----+                     +- +-------+                 起始点
 *    |  p  |  ---------------->  0  |-------|
 *    +-----+                        +-------+
 *                                1  |-------|
 *                                   +-------+
 *                                2  |-------|
 *                                   +-------+
 *                                3  |-------|
 *                                   +-------+
 *                                4  |-------|
 *                                   +-------+
 *                                5  |-------|
 *                                   +-------+
 *                                6  |-------|
 *                                   +-------+
 *                                7  |-------|
 *                                   +-------+
 *                                8  |-------|
 *                                   +-------+
 *                                9  |-------|
 *                                   +-------+
 *
 *
 */

