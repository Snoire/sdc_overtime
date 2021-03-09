/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2019.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 24-6 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

#define BUF_SIZE 1000
#define SYNC_SIG SIGUSR1                /* Synchronization signal */

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

char * currTime(const char *format)
{
    static char buf[BUF_SIZE];  /* Nonreentrant */
    time_t t;
    size_t s;
    struct tm *tm;

    t = time(NULL);
    tm = localtime(&t);
    if (tm == NULL)
        return NULL;

    s = strftime(buf, BUF_SIZE, (format != NULL) ? format : "%c", tm);  //作者很喜欢用三元运算符啊

    return (s == 0) ? NULL : buf;
}

static void             /* Signal handler - does nothing but return */
handler(int sig)
{
}

//int main(int argc, char *argv[])
//int main()    //这么写，实际运行程序的时候，可以加参数不报错
int main(void)  //这么写好像也可以欸，加参数也不报错。。
{
    pid_t childPid;
    sigset_t blockMask, origMask, emptyMask;
    struct sigaction sa;

    setbuf(stdout, NULL);               /* Disable buffering of stdout */

    sigemptyset(&blockMask);            /*用来初始化清空一个信号集*/
    sigaddset(&blockMask, SYNC_SIG);    /* Block signal */ /*把信号加到信号集中，以后会用到*/
    if (sigprocmask(SIG_BLOCK, &blockMask, &origMask) == -1) /* block SYNC_SIG, 防止这个信号触发 handler */
        errExit("sigprocmask");

    sigemptyset(&sa.sa_mask);           /*设置 SYNC_SIG 信号触发时 block 的信号集*/
    sa.sa_flags = SA_RESTART;           /*自动重启被信号打断的系统调用*/
    sa.sa_handler = handler;
    if (sigaction(SYNC_SIG, &sa, NULL) == -1)  /*设置信号，把 SYNC_SIG 信号的行为改成调用自定义 handler*/
        errExit("sigaction");

    switch (childPid = fork()) {
    case -1:
        errExit("fork");

    case 0: /* Child */

        /* Child does some required action here... */

        printf("[%s %ld] Child started - doing some work\n",
                currTime("%T"), (long) getpid());
        sleep(2);               /* Simulate time spent doing some work */

        /* And then signals parent that it's done */

        printf("[%s %ld] Child about to signal parent\n",
                currTime("%T"), (long) getpid());
        if (kill(getppid(), SYNC_SIG) == -1)       /*向父进程发送 SYNC_SIG 信号*/
            errExit("kill");

        /* Now child can do other things... */

        _exit(EXIT_SUCCESS);

    default: /* Parent */

        /* Parent may do some work here, and then waits for child to
           complete the required action */

        printf("[%s %ld] Parent about to wait for signal\n",
                currTime("%T"), (long) getpid());
        sigemptyset(&emptyMask);
        if (sigsuspend(&emptyMask) == -1 && errno != EINTR) /*临时把 sig mask 变成空集，也就是不 block 任何信号，等待被一个信号触发，再恢复原状*/
            errExit("sigsuspend");
        printf("[%s %ld] Parent got signal\n", currTime("%T"), (long) getpid());

        /* If required, return signal mask to its original state */

        if (sigprocmask(SIG_SETMASK, &origMask, NULL) == -1)
            errExit("sigprocmask");

        /* Parent carries on to do other things... */

        exit(EXIT_SUCCESS);
    }
}
