#include <stdio.h>
#include <string.h>

int main()
{
    char *ms = "0";
    char *vs = "5";

    printf("1: %d\n", strchr(vs, '3'));
    if (strchr(vs, '5') >= 0)
        printf("2: %d\n", strchr(vs, '5'));
    if (strchr(vs, '6') >= 0)
        printf("3: %d\n", strchr(vs, '6'));

    return 0;
}
