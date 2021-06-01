#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *p = NULL;
    printf("%u\n", atoi(p));    /* segmentation fault */
    return 0;
}
