#include <stdio.h>

int main()
{
    unsigned long long flag = 0;
    flag = (1ULL<<45);

    printf("%llu\n", flag);
    return 0;
}
