#include <stdio.h>
#include <unistd.h>

#define POWER 1000000
#define LEN   301030
/* calculate 2 to the power 1000 */
/* 35 分钟才算出来。。 */
int main()
{
    char d[LEN] = {0};
    int carry, temp;

    setbuf(stdout, NULL);
    d[0] = 1;
    for (int i = 0; i < POWER; i++) {
        carry = 0;
        temp = 0;

        printf("%.4f%%\r", (double) (i+1)*100/POWER);

        for (int j = 0; j < LEN; j++) { /* 模拟手动运算过程 */
            temp = d[j] * 2 + carry;
            d[j] = temp % 10;
            carry = temp / 10;          /* 进位 */
        }
    }
    printf("\n");

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
