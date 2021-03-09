#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>

int main()
{
#if 0
    clock_t last, now;
    int i = 0;

    last = clock();

    while (1) {
        sleep(15);  // sleep 的时候好像 cpu 是不计数的。。
        i += 15;
        now = clock();
        printf("i: %d, %ld, %ld, %f\n", i, last, now, (double) (now-last) / CLOCKS_PER_SEC);
        if ((double) (now-last) / CLOCKS_PER_SEC >= 9)
            break;
    }
#else
#endif
    int i = 0;
    long last, now;
    struct sysinfo si;

    sysinfo(&si);
    last = si.uptime;

    while (1) {
        sleep(1);  // sleep 的时候好像 cpu 是不计数的。。
        i += 1;
        sysinfo(&si);
        now = si.uptime;
        printf("i: %d, %ld, %ld, %ld\n", i, last, now, (now-last));
        if ((now-last) >= 9)
            break;
    }

    printf("9s has pass.\n");

    return 0;
}
