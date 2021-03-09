#include <stdio.h>
#include <string.h>

int main()
{
    char *p = "hi, all";

    printf("sizeof(' '): %d\n", sizeof(' '));                 /* 这个为什么是 4 ？难道是 int 型？ */
    printf("sizeof((char) ' '): %d\n\n", sizeof((char) ' ')); /* 1 */

    printf("sizeof(char *): %d\n", sizeof(char *));               /* 8，char 型指针 */
    printf("sizeof(int [6]): %d\n", sizeof(int [6]));             /* 24，6 个元素的 int 数组 */
    printf("sizeof(int *[6]): %d\n", sizeof(int *[6]));           /* 48，有 6 个元素的数组，每个元素是 int * 指针 */
    printf("sizeof(int (*)[6]): %d\n\n", sizeof(int (*)[6]));     /* 8，一个指针，指向 int [6] 数组 */

    printf("strlen(\"hi, all\"): %d\n", strlen("hi, all"));   /* 这个没有结尾的 0 */
    printf("sizeof(\"hi, all\"): %d\n\n", sizeof("hi, all")); /* 没想到吧，能直接得到字符串常量的长度，不用自己数了 */

    printf("sizeof(p): %d\n", sizeof(p));            /* 8，指针 */
    printf("sizeof(*p): %d\n\n", sizeof(*p));        /* 1，第一个字符，char 型 */

    printf("strlen(p): %d\n", strlen(p));            /* 这个才能得到字符串里的字符数，不算 \0 */
    printf("strlen(*p): %d\n", strlen(*p));          /* segmentation fault */

    return 0;
}

