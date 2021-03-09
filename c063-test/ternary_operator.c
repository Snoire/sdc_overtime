#include <stdio.h>

int main()
{
    printf("|%s|\n", "hi" ?: "");  /* 没想到吧，三目运算符还能这么写 */
    printf("|%s|\n", NULL ?: "");  /* 防止字符串指针为 NULL */
    printf("|%s|\n", NULL);
//    printf("|%s|\n", "hi" ? "" : );  /* 这么写就会有语法错误 */

    return 0;
}
