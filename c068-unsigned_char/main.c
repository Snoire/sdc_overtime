#include <stdio.h>
#include <string.h>

int main()
{
    char a = (char) ~0;                       // 没有报警告，可能是隐式转换的时候前后都是0
    unsigned char b = (unsigned char) ~0xef;  // 数字默认是 int, 不手动加上会报警告
    unsigned int c = ~0xef;
    unsigned int d = 0xffffffff;              // d 和 e 等价
    unsigned int e = ~0;

    printf("char a: |%d|, |%c|, |%#X|\n", a, a, a);
    printf("char b: |%d|, |%c|, |%#X|\n", b, b, b);
    printf("char c: |%d|, |%c|, |%#X|\n", c, c, c);
    printf("char d: |%d|, |%c|, |%#X|\n", d, d, d);
    printf("char e: |%d|, |%c|, |%#X|\n", e, e, e);

    char str[32] = "";
    char chr = -1;
    str[0] = chr;
    printf("str: |%.16s|\n", str);
    printf("str[0]: |%d|, |%c|, |%#X|\n", str[0]);

    //str = NULL;  // 字符数组的地址不可能是 NULL
    if (str[0])  // 空字符串，所以这边就可以放心用了，如果是指针就要先加个判断
//    if (strcmp(NULL, ""))  // 这个遇到 NULL 也会段错误，而且麻烦，好处是直观
        printf("非空字符串\n");
    else
        printf("空字符串\n");

//    char *pstr = NULL;
//    pstr[0] = 1;  //段错误

    unsigned char ustr[16] = "hi";
    printf("ustr: |%s|, |%#X|\n", ustr, ustr[0]);

    unsigned char sstr[16] = "hi";   // 因为是正数，所以储存的值一样，ascii 的值都在 0~127 之间
    printf("sstr: |%s|, |%#X|\n", sstr, sstr[0]);

    return 0;
}
