#include <stdio.h>
#include <string.h>

int main()
{
    char str[10], *p;
    p = str;
    
    printf("sizeof(p) = %d\n", sizeof(p));
    printf("sizeof(*p) = %d\n", sizeof(*p));
    printf("sizeof(str) = %d\n", sizeof(str));  //所以用 memset 的时候，只能用 sizeof(p)

    memset(str, 0, sizeof(str));  //只能写sizeof(str), 不能写sizeof(p)
    for (int i=0; i<10; ++i)
    {
        printf("%d\x20", str[i]);
    }
    printf("\n");

    return 0;
}

