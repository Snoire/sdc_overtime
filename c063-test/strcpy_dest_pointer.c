#include <stdio.h>
#include <string.h>

int main()
{
    char a[10] = "hello";
    char *b[3];

    printf("asss\n");
    //strcpy(b[1], a);
    b[1] = a;
    printf("b: %s\n", b[1]);

    return 0;
}
