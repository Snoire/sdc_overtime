#include <stdio.h>

extern int nonexist();

int hello(const char str)
{
    printf("hello, %s\n", str);

    return 0;
}

int func()
{
    nonexist();
    return 0;
}
