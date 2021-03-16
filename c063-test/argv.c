#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("argc: %d\n", argc);
    printf("argv[0]: %d\n", atoi(argv[0]));
    if (argc > 1) {
        printf("argv[1]: %s\n", argv[1]);
        printf("argv[1][0]: %c\n", argv[1][0]);
        argv[1][0] = '2';
        printf("argv[1]: %s\n", argv[1]);  /* argv 的值可被修改，可见它不是字符串常量 */
    }

    return 0;
}
