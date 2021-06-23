#include <stdio.h>

typedef int (*func_t)();

func_t values()
{
    int i = 0;
    int lambda()
    {
        return ++i;
    }
    return lambda;  /* 这样应该是错的吧 */
}

int main()
{
    func_t v1 = values(0);
    func_t v2 = values(6);

    printf("v1: %d\n", v1());
    printf("v2: %d\n", v2());   /* 和 v1 是同一个 */
    printf("v1: %d\n", v1());
    printf("v1: %d\n", v1());

    return 0;
}

