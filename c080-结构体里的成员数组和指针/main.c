#include <stdio.h>
struct str{
    int len;
    char s[0];
};
 
struct foo {
    struct str *a;
    char rate[9];
};
 
int main(int argc, char** argv) {
    struct foo f = {0};
    printf("%d\n", sizeof(f.rate)); /* 可以获取结构体内数组的大小 */
    printf("%d\n", sizeof(f.a->s)); /* 可以获取结构体内数组的大小 */

    if (f.a->s) {
        printf(f.a->s);  /* crash */
    }
    return 0;
}
