#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *src = "hello, world";
    char *dest = NULL;

    int len = strlen(src);
    dest = (char *) malloc(len + 1);

    char *d = dest;
    //char *s = src[len];
    char *s = src + len - 1;

    while (len-- != 0) {
        *d++ = *s--;
    }
    printf("%s", dest);

    return 0;
}
