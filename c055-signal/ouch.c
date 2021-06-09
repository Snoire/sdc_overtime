// tlpi signals/ouch.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void sigHandler(int sig)
{
    printf("Ouch!\n");
}


int main(int argc, char **argv)
{
    if (signal(SIGINT, sigHandler) == SIG_ERR) {
        perror("signal");
        return -1;
    }

    for (int i = 0; ; i++) {
        printf("%d\n", i);
        sleep(3);
    }

    return 0;
}
