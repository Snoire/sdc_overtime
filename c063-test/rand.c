#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int a;
    srand((unsigned)time(NULL));
    a = rand() % 2567;
    printf("%d\n", a);

    return 0;
}
