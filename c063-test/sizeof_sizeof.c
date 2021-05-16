#include <stdio.h>

struct x {
    int time;
    char mac[32];
    int wired;
    char rate[8];
    char rssi[8];
};

int main()
{
    printf("sizeof(struct x): %ld\n", sizeof(struct x));
    printf("sizeof(sizeof(struct x)): %ld\n", sizeof(sizeof(struct x)));

    return 0;
}
