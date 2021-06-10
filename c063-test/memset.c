#include <stdio.h>

int main()
{
    int n[2][4];
    memset(n, 0xFF, sizeof(n));

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            printf("n[%d][%d]: %d\n", i, j, n[i][j]);
        }
    }

    return 0;
}
