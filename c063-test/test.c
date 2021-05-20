#include <stdio.h>
/* */

int main()
{
    char *str = "0";
//    char *str2 = "56";

    if (*str == '3' || *str == '5' || *str == '6')
        printf("ok\n");
    else
        printf("oh no\n");

    str = NULL;
    if (*str != 0)
        printf("str != 0");

    return 0;
}
