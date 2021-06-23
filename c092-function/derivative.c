#include <stdio.h>
#include <math.h>

typedef double (*func_t)(double);

func_t derivative(func_t f)
{
    double delta = 1e-4;
    double _derivative(double x) {
        return (f(x + delta) - f(x))/delta;
    }
    /* 这里是可以的 */
    //printf("%.14f\n", _derivative(5.2));
    /* 不能把它传出去 */
    return _derivative;
}



int main()
{
    func_t c = derivative(sin);
    /* 出错了，看来不能这么用 */
    printf("%.14f  %.14f\n", cos(5.2), c(5.2));
    return 0;
}
