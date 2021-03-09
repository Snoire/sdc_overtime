#include <stdio.h>
#include <stdlib.h>

int printchar(const char *buf)
{
    for (int i = 0; buf[i]; i++) {
        if (i)
            printf(", ");
            //printf("\n");
        printf("%d:|%c|", buf[i], buf[i]);  // 打印 \r 会把光标移动到最开始
    }
    printf("\n");

    return 0;
}

/* 在 linux 下打开 windows 文件(以 \r\n 结尾) */
int main()
{
    FILE *fp = NULL;
    char buf[1024] = "";

    if ((fp = fopen("text.txt", "a+")) == NULL) {  // a+ 和 ab+ 没区别
        fprintf(stderr, "cant open the file\n");
        exit(0);
    }

    fgets(buf, sizeof(buf), fp);
//    printf("buf: |%s|\n", buf);
    printchar(buf);   // 会读取 \r\n
    fgets(buf, sizeof(buf), fp);
    printchar(buf);

    return 0;
}

