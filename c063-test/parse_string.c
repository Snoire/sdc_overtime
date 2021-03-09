#include <stdio.h>
#include <string.h>

int main()
{
    char *str = "www.baidu.com,www.time.com,www.google.com,www.bilibili.com,time.windows.cn";
    char *p = NULL;
    char buf[64] = "";
    int i = 0;

    for (i = 0; i < 16; i++) {
//        printf("i = %d\n", i);
        memset(buf, 0, sizeof(buf));

#if 0
        if (*str != 0) {   //这里很危险，str 为 NULL 时会段错误
#else
        if (str && *str != 0) {  //这样才安全
#endif
            if ((p = strchr(str, ','))) {
                strncpy(buf, str, strlen(str) - strlen(p));
                printf("str%d: %s\n", i, buf);
                str = p + 1;
            } else {
                printf("str%d: %s\n", i, str);
#if 0
                break;
#else
                str = NULL;
#endif
            }
        }
    }
//    printf("i = %d\n", i);
//    
//    p = "hi";
//    if (p)
//        if (*p != 0)
//            printf("*p != 0\n");


    return 0;
}
