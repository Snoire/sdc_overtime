#include <stdio.h>

#define POWER 1000
#define LEN   310
/* calculate 2 to the power 1000 */
/* 这种方法效率太低了。。 */
int main()
{
    char d[LEN] = {0};
    int carry, temp;

    d[0] = 1;
    for (int i = 0; i < POWER; i++) {
        carry = 0;
        temp = 0;

        for (int j = 0; j < LEN; j++) { /* 模拟手动运算过程 */
            temp = d[j] * 2 + carry;
            d[j] = temp % 10;
            carry = temp / 10;          /* 进位 */
        }
    }

    int flag = 1;
    for (int i = 0; i < LEN; i++) {  /* print array in reverse order */
        if (flag) {                  /* 把数字开头的 0 去掉 */
            if (!d[LEN-1-i])
                continue;
            else
                flag = 0;
        }
        printf("%d", d[LEN-1-i]);
    }
    printf("\n");

    return 0;
}
