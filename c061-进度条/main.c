#include <stdio.h>
#include <unistd.h>

/* TODO: 太简陋了 */
void processbar(int t, int n)
{
    setbuf(stdout, NULL);
    printf("[%3d%%]\r", t*100/n);
}

int main()
{
    for (int i=0; i < 9; i++) {
        processbar(i, 9);
        sleep(1);
    }
    printf("\n");

    return 0;
}

