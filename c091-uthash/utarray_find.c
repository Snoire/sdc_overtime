#include <stdio.h>
#include <netinet/ether.h>
#include "utarray.h"

#if 0
struct ether_addr {
    uint8_t ether_addr_octet[6];
}
#endif

/* 对于 bsearch 来说，怎么排序并不重要，
 * 只要给它一个能排序的方法就行
 * 它的目的是用两分法来找出元素在不在列表里面
 * 所以我这里把 struct ether_addr 当作 long 来排序，哈哈
 * int 才四个字节，不够用，所以用 long
 * 省得用 ether_ntoa 转换成 macstr，再逐个比较字符 */
#if 0  /* 我以为可以的。。当我没说 */
static int easort(const void *_a, const void *_b) {
//    unsigned char * a = (const unsigned char *)_a;
//    unsigned char * b = (const unsigned char *)_b;
    unsigned char * a = (unsigned char *)_a;
    unsigned char * b = (unsigned char *)_b;
    for (int i = 0; i < 6; i++) {
        if (a[i] < b[i])
            return -1;
        else if (a[i] > b[i])
            return 1;
    }
    return 0;
}
#elif 1   /* 突然发现 memcmp 用来这里非常合适 */
static int easort(const void *a, const void *b) {
    return memcmp(a, b, 6);
}
#else
static int easort(const void *a, const void *b) {
    unsigned long _a = *(const unsigned long *)a << 16;  /* 这样好像可以，把多余的两个字节去掉 */
    unsigned long _b = *(const unsigned long *)b << 16;  /* 但是这样写不好 */

    printf("%lu %s %lu\n", _a, (_a < _b) ? "<": (_a > _b) ? ">" :"=", _b);
    return (_a < _b) ? -1 : (_a > _b);
}
#endif

int main()
{
    UT_array *maclist;
    UT_icd ea_icd = { sizeof(struct ether_addr), NULL, NULL, NULL };
    utarray_new(maclist, &ea_icd);
    struct ether_addr ea, *p;
    printf("len of array: %d\n", utarray_len(maclist));

    char *macstr = NULL;
    char buf[18] = "";

    macstr = "14:2E:5E:89:09:BE";
    ether_aton_r(macstr, &ea);
    utarray_push_back(maclist, &ea);
    printf("ea: %lu\n", *(unsigned long *) &ea << 16);

    macstr = "D4:3B:04:BF:59:14";
    ether_aton_r(macstr, &ea);
    utarray_push_back(maclist, &ea);
    printf("ea: %lu\n", *(unsigned long *) &ea << 16);

    macstr = "4E:A8:71:09:E6:94";
    ether_aton_r(macstr, &ea);
    utarray_push_back(maclist, &ea);
    printf("ea: %lu\n", *(unsigned long *) &ea << 16);

    macstr = "5C:87:9C:F0:AD:DE";
    ether_aton_r(macstr, &ea);
    utarray_push_back(maclist, &ea);
    printf("ea: %lu\n", *(unsigned long *) &ea << 16);

    /* print */
    int i = 0;
    printf("\nmaclist:\n");
    p = NULL;
    while ((p = (struct ether_addr *) utarray_next(maclist, p))) {       /* 有啥区别 *//* 。。为啥有时候没问题，有时候有问题 */
        ether_ntoa_r(p, buf);     /* 会被转换成小写啊 */
        printf("%d: %s\n", i, buf);
        i++;
    }

    macstr = "5c:87:9c:f0:ad:de";
//    macstr = "4e:a8:71:09:e6:94";
//    macstr = "4e:A8:71:09:e6:94";
//    macstr = "3e:A8:71:09:e6:94";
    ether_aton_r(macstr, &ea);

    /* find */
    p = utarray_find(maclist, &ea, easort);
    if (p) {
        ether_ntoa_r(p, buf);     /* 会被转换成小写啊 */
        printf("find: %s, index: %lu\n", buf, utarray_eltidx(maclist, p));
        /* delete */
        utarray_erase(maclist, utarray_eltidx(maclist, p), 1);
    } else {
        printf("not found\n");
    }
    printf("len of array: %d\n", utarray_len(maclist));



    /* print */
    i = 0;
    printf("\nmaclist:\n");
    p = NULL;
    while ((p = (struct ether_addr *) utarray_next(maclist, p))) {       /* 有啥区别 *//* 。。为啥有时候没问题，有时候有问题 */
        ether_ntoa_r(p, buf);     /* 会被转换成小写啊 */
        printf("%d: %s\n", i, buf);
        i++;
    }


    utarray_free(maclist);
    return 0;
}
