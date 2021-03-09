#include <unistd.h>
#include <stdio.h>
int opt(int argc, char *argv[])
{
    int ch;
    opterr = 0;                 //设置为0就不会输出错误到 stderr
    printf("optind:%d，opterr：%d\n", optind, opterr);
    printf("--------------------------\n\n");
    while ((ch = getopt(argc, argv, "ab:c:de::")) != -1) {
        printf("optind: %d\n", optind);
        switch (ch) {
        case 'a':
            printf("HAVE option: -a\n\n");
            break;
        case 'b':
            printf("HAVE option: -b\n");
            printf("The argument of -b is %s\n\n", optarg);
            break;
        case 'c':
            printf("HAVE option: -c\n");
            printf("The argument of -c is %s\n\n", optarg);
            break;
        case 'd':
            printf("HAVE option: -d\n");
            break;
        case 'e':
            printf("HAVE option: -e\n");
            printf("The argument of -e is %s\n\n", optarg);
            break;
        case '?':
            printf("Unknown option: %c\n", (char) optopt);      //这里是输出到标准输出的，不归 stderr 管
            break;
        }
    }

    printf("optind:%d，opterr：%d\n", optind, opterr);
    return 0;

}

int main(int argc, char **argv)
{
    char str[10] = { 0 };
    printf("str= %s\n", str);

    if (str) {
        printf("这个 str 和下面的 argv[optind] 不同，它不是 NULL\n");
    } else
        printf("出错!\n");

    opt(argc, argv);
    printf("optind:%d，opterr：%d\n", optind, opterr);
    printf("argv[aptind]= %s\n", argv[optind]); //调用 getopt 之后，optind 指向不存在的字符，argv[aptind] 变成 NULL 指针

    if (argv[optind]) {
        printf("让我看看你到底是什么 -> argv[aptind]= %s\n", argv[optind]);
    } else
        printf("出错!\n");
    return 0;

}
