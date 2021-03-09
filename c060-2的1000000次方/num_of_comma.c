#include <stdio.h>

int main()
{
    int num = 0;
    char *buf = "36,40,44,48";

    for (int i = 0; buf[i]; i++) {
        if (buf[i] == ',')
            num++;
    }
    num++;

    printf("num: %d\n", num);
    return 0;
}
