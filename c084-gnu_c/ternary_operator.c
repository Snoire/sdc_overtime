#include <stdio.h>
/* 这好像是 gnu 的扩展语法 */
/* https://gcc.gnu.org/onlinedocs/gcc-10.2.0/gcc/Conditionals.html#Conditionals */

/* the expression `x ? : y` has the value of x if that is nonzero; otherwise, the value of y.
   This example is perfectly equivalent to `x ? x : y` */

int main()
{
    printf("|%s|\n", "hi" ?: "");  /* 没想到吧，三目运算符还能这么写 */
    printf("|%s|\n", NULL ?: "");  /* 防止字符串指针为 NULL */
    printf("|%s|\n", NULL);
//    printf("|%s|\n", "hi" ? "" : );  /* 这么写就会有语法错误 */

    return 0;
}
