#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/ether.h>

struct wired_device_t {
    unsigned char mac[6];
    unsigned int rate;
} __attribute__((packed));

int main(int argc, char **argv)
{
    pid_t pid;
    int signum;
    union sigval mysigval;

//    unsigned char macbin[6] = { 0 };
    char *macstr = "14:2E:5E:89:09:BE";
    struct wired_device_t wired_list;

    ether_aton_r(macstr, (struct ether_addr *) &wired_list.mac);
    wired_list.rate = 1000;

    signum = atoi(argv[1]);
    pid = (pid_t) atoi(argv[2]);

//    mysigval.sival_int = 8;     //不代表具体含义，只用于说明问题
    mysigval.sival_ptr = &wired_list;

    if (sigqueue(pid, signum, mysigval) == -1)
        printf("send error\n");

    printf("rate: %d\n", wired_list.rate);
    printf("p: %p\n", mysigval.sival_ptr);
    sleep(2);

    return 0;
}
