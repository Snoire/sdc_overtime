#include <stdio.h>

int main()
{
    char *str1 = "Could you find me?";
    char str2[] = "You can't find me!";

    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);

    return 0;
}

/*
 * $ grepn "Could you find me?"
 * Binary file encry_str matches
 * encry_str.c:5:    char *str1 = "Could you find me?";
 *
 * $ grepn "You can't find me\!"
 * encry_str.c:6:    char str2[] = "You can't find me!";
 *
 * 第二种写法中的字符串，在程序中里是乱的，但是能找到零散的一部分
 * $ strings encry_str
 * u/UH
 * You can'H
 * t find mH
 * []A\A]A^A_
 * Could you find me?
 * str1: %s
 */
