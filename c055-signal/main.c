#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void sighandler(int signum)
{
    printf("捕获信号 %d，跳出...\n", signum);
    exit(1);
}

void sighandler2(int signum)
{
    printf("捕获信号 %d，跳出..\n", signum);
    exit(1);
}

int main()
{
    void (*old_handler)(int);
    void (*nex_handler)(int);

    old_handler = signal(SIGINT, sighandler);
    nex_handler = signal(SIGINT, sighandler2);

    printf("^C:%s\n", strsignal(SIGINT));  //Displaying Signal Descriptions

    printf("oldhandler: %p\n", old_handler);
    printf("nexhandler: %p\n", nex_handler);
    printf("sighandler: %p\n", sighandler);
    printf("lathandler: %p\n", sighandler2);
 
    while(1) {
       printf("开始休眠一秒钟...\n");
       sleep(1);
    }
 
    return(0);
}
