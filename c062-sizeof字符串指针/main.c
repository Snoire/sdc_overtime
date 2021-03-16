#include <stdio.h>
#include <string.h>

size_t strlen2(const char *str);

int main()
{
    char *p = "hi, all";
    char str[] = "";
    char str1[] = "";
    char str2[8] = "";
    char *q = NULL;

    printf("sizeof(' '): %d\n", sizeof(' '));                 /* 这个为什么是 4 ？难道是 int 型？ */
    printf("sizeof((char) ' '): %d\n\n", sizeof((char) ' ')); /* 1 */

    printf("sizeof(str): %d\n", sizeof(str));
    printf("strlen(str): %d\n\n", strlen(str));

    printf("|%s|\n", fgets(str1, 7, stdin));
    printf("|%s|\n", str1);
    printf("sizeof(str1): %d\n", sizeof(str1));
    //for (int i = 0; i < 9; i++)
    //    printf("%d: %c\n", i, *(str1 + i));
    printf("strlen(str1): %d\n", strlen(str1));      /* 为什么是 0 ? */
    printf("strlen2(str1): %d\n\n", strlen2(str1));  /* 这个才是和我预期的一样 */
    q = str1;
    printf("strlen(q): %d\n", strlen(q));            /* 8, 和用 gdb 看到的一样 */
    printf("strlen2(q): %d\n\n", strlen2(q));

    printf("|%s|\n", fgets(str2, 16, stdin));
    printf("|%s|\n", str2);
    printf("sizeof(str2): %d\n", sizeof(str2));
    printf("strlen(str2): %d\n\n", strlen(str2));

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

/* usage: ./c62
 * some_str1
 * some_str2 */
