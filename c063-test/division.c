#include <stdio.h>

int modulo(long a, int b) {
    return (a % b + b) % b;
}

int floordiv(long a, int b) {
    return (a - modulo(a, b)) / b;
}


int main()
{
    printf(" 3 /  2: %2d\n", 3 / 2);
    printf("-3 /  2: %2d\n", -3 / 2);
    printf(" 3 / -2: %2d\n", 3 / -2);
    printf("-3 / -2: %2d\n", -3 / -2);
    printf("\n");

    printf(" 3 modulo  2: %2d\n", modulo(3, 2));
    printf("-3 modulo  2: %2d\n", modulo(-3, 2));
    printf(" 3 modulo -2: %2d\n", modulo(3, -2));
    printf("-3 modulo -2: %2d\n", modulo(-3, -2));
    printf("\n");

    printf(" 3 floor  2: %2d\n", floordiv(3, 2));
    printf("-3 floor  2: %2d\n", floordiv(-3, 2));
    printf(" 3 floor -2: %2d\n", floordiv(3, -2));
    printf("-3 floor -2: %2d\n", floordiv(-3, -2));
    printf("\n");

    printf("-4294967295 floor 2: %2d\n", floordiv(-4294967295, 2));
    printf("4294967295 floor 2: %2d\n", floordiv(4294967295, 2));

    return 0;
}
