// https://gcc.gnu.org/onlinedocs/gcc-11.1.0/gcc/Nested-Functions.html#Nested-Functions
#include <stdio.h>
#include <math.h>

int summation(int n, int (*term)(int), int (*next)(int))
{
    int total = 0, k = 1;
    while (k <= n) {
        total += term(k);
        k = next(k);
    }
    return total;
}

int successor(int k) {
    return k + 1;
}

int sum_cubes(int n)
{
    /* 这应该是嵌套函数的正确用法吧
     * 虽然也能写在外面，但是这个函数，除了 sum_cubes 之外，别人也不会用它
     * 而且，定义在里面可以访问到 sum_cubes 的变量，不需要再把参数传进去了(这个例子看不出来) */
    int cube(int k) {
        return pow(k, 3);
    }
    return summation(n, cube, successor);
}

int sum_naturals(int n)
{
    int identity(int k) {
        return k;
    }
    return summation(n, identity, successor);
}


int main()
{
    printf("%d\n", sum_cubes(3));
    printf("%d\n", sum_naturals(10));
    return 0;
}
