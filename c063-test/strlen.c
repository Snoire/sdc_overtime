#include <stdio.h>
#include <string.h>


int main()
{
    char *str = "www.baidu.com,www.time.com,www.google.com,www.bilibili.com,time.windows.cn";
//    char *p = NULL;
//    char buf[64] = "";
//    int i = 0;
    str = NULL;

    printf("len1: %ld\n", sizeof((char) (' '))); // 这么写有什么必要吗。。
    printf("len2: %ld\n", sizeof((char) (':'))); // 这么写有什么必要吗。。
    printf("length = %ld\n", strlen(str));  // 段错误，strlen 的参数不能是 NULL

    return 0;
}
