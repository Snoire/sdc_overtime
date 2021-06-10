#include <stdio.h>
#include <string.h>

int main()
{
    char n[2][4];
//    memset(n, 0xFF, sizeof(n));
    memset(n, 0x7F, sizeof(n));     /* 最大正数(1 byte)，127 */

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            printf("n[%d][%d]: %d\n", i, j, n[i][j]);
        }
    }

    return 0;
}
