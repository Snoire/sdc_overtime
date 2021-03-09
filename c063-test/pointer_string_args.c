#include <stdio.h>

int fun(char *str)
{
    printf("str: %s\n", str);
    snprintf(str, 16, "%s", "hi");  /* 因为传进来的是指针，所以可以修改，不必传进来二级指针 */
    return 0;
}

int main()
{
    char str[] = "strings";
    printf("str: %s\n", str);
    fun(str);
    printf("str: %s\n", str);

    return 0;
}
