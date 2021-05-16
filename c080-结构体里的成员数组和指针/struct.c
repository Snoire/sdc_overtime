// https://www.coolshell.cn/articles/11377.html
#include <stdio.h>
struct str{
    int len;
    char s[0];
    char *ps;
};
 
struct foo {
    struct str *a;
};
 
int main(int argc, char** argv)
{
    struct foo f = { 0 };
    __attribute__((unused)) char *p = f.a->s;
    __attribute__((unused)) char *ps = f.a->ps; /* segmentation fault */
    __attribute__((unused)) int i = f.a->len;   /* segmentation fault */

    if (f.a->s) {
        printf(f.a->s);                         /* segmentation fault */
    }
    return 0;
}

/*
 * 对于结构体来说，访问其中的成员，只有数组名是特殊的。
 * 包括指针在内，访问结构体中普通变量，
 * 就是根据它们在结构体中的依稀地址去获取其中的内容。
 * 而访问结构体内的数组成员，只是得到它的依稀地址而已，
 * 数组内具体的数据还需要进一步处理。
 */
