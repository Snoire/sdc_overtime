#include <stdio.h>
#include <unistd.h>

void printarg(int argc, char *argv[])
{
    printf("\n--------------------------\n");
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    printf("--------------------------\n");
}

int main(int argc, char *argv[])
{
    printarg(argc, argv);

    int ch;
    printf("\n");
    printf("optind:%d，opterr：%d\n", optind, opterr);

    while ((ch = getopt(argc, argv, "ab:c:de::")) != -1) {
        printf("optind: %d\n", optind);
        switch (ch) {
        case 'a':
            printf("|-a|\n");
            break;
        case 'b':
            printf("|-b %s|\n", optarg);
            break;
        case 'c':
            printf("|-c %s|\n", optarg);
            break;
        case 'd':
            printf("|-d|\n");
            break;
        case 'e':
            printf("|-e %s|\n", optarg);
            break;
        case '?':
            printf("Unknown option: %c\n", (char) optopt);
            break;
        }
    }

    printf("optind=%d,argv[%d]=%s\n", optind, optind, argv[optind]);

    /* 命令重新排序了 */
    printarg(argc, argv);

    /* 去掉选项之后，对剩下的命令分析 */
    if (optind > 1)
        argv[optind - 1] = argv[0];
    argv += optind - 1;
    argc -= optind - 1;

    printarg(argc, argv);

    return 0;
}

/* example: ./getopt2 help -b barg show -c123 -ehi commit */
