#include <stdio.h>

int main()
{
    int *p = NULL;
    int a = *p;         /* crash */
    printf("a: %d\n", a);
    return 0;
}
