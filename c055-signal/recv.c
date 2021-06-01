//https://www.cnblogs.com/hoys/archive/2012/08/19/2646377.html
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/ether.h>

struct wired_device_t {
    unsigned char mac[6];
    unsigned int rate;
} __attribute__((packed));

void new_op(int signum, siginfo_t * info, void *myact)
{
    struct wired_device_t *pentry = info->si_value.sival_ptr;

    printf("signo: %d, code: %d, pid: %d, uid: %d, int: %d, ptr: %p\n",
            info->si_signo, info->si_code, info->si_pid, info->si_uid,
            info->si_value.sival_int, info->si_value.sival_ptr);    /* 传过来的指针无法在另一个进程中访问 */
    printf("the int value is %d \n", info->si_int);
//    printf("rate: %d\n", pentry->rate);
    while(1);
}

int main(int argc, char **argv)
{
    struct sigaction act;
    int sig;
    pid_t pid;

    pid = getpid();
    sig = atoi(argv[1]);

    sigemptyset(&act.sa_mask);
    act.sa_sigaction = new_op;
    act.sa_flags = SA_SIGINFO;

    if (sigaction(sig, &act, NULL) < 0) {
        printf("install sigal error\n");
    }

    printf("pid: %d, wait for the signal..\n", pid);
    while (1) {
        sleep(2);
    }

    return 0;
}
