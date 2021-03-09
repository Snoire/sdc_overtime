#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"


int main()
{
    int num = 0;
    char str[10];
    char str2[10];

    printf( COLOR_CYAN "(ot) " COLOR_RESET );
    *str = 'l';
//    fgets(str, 2 , stdin); //读取1个字符  用 fgets 无法读取 Ctrl+d，即 EOF/-1 ，str 的值保持不变 
    *str = getchar();        //用 getchar 可以，但是输入缓冲区很奇怪，接下来继续用 getchar 来读取，会直接读取一个 -1，好像 -1 一直存在缓冲区里
    if(*str==10)
        num = 0;
    else if(*str==-1) {
        printf("\n");
    //    return 0;
    } else {
        num = *str;
        scanf("%*[^\n]");        //清空缓冲区
        scanf("%*c");            //不能合写成 scanf("%*[^\n]%*c"); 因为如果缓冲区里只有一个 \n，前面匹配会失败，后面不会继续了
    }

    printf("str[0] = %c\n", *str);
    printf("str[0] = %d\n\n", *str);

    printf("str[1] = %c\n", str[1]);
    printf("str[1] = %d\n\n", str[1]);

    printf("str[2] = %c\n", str[2]);
    printf("str[2] = %d\n\n", str[2]);





    int n;
    char buf[4] = "";

    n = read(STDIN_FILENO, buf, 2);
    if (n < 0) {
        perror("read STDIN_FILENO");
        exit(1);
    }
    printf("buf[0]: %d\n", buf[0]);



    /* 2rd time */
    printf("2rd time\n");
    printf( COLOR_CYAN "(ot) " COLOR_RESET );
    *str2 = 'h';
    *str2 = getchar();
    if(*str2==10)
        num = 0;
    else {
        num = *str2;
    }

    printf("str2[0] = %c\n", *str2);
    printf("str2[0] = %d\n\n", *str2);

    printf("str2[1] = %c\n", str2[1]);
    printf("str2[1] = %d\n\n", str2[1]);

    printf("str2[2] = %c\n", str2[2]);
    printf("str2[2] = %d\n", str2[2]);

    return 0;
}

