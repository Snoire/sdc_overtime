// https://leetcode-cn.com/circle/article/KBnaqU/
#include <stdio.h>
#include <stdlib.h>

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
    for (int i = 0; i < 10; i++) {
        arr2[i] = (int*)calloc(2, sizeof(int));
        arr2[i][0] = rand() % 2567;
        arr2[i][1] = rand() % 2567;
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
}

/*
 *                                这里还需要再寻址一次
 *                                +-------------------
 *                                |                                     two int
 *    +------+                    +- +-------+                       0 +-------+
 *    | arr2 |  ----------------> 0  |  ptr  |    ---------------->  1 |-------|
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

