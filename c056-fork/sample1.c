#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/* identify which is the parent process and which is the child process */
int main()
{
    pid_t pid, ppid, childPid;

    switch (childPid = fork()) {
    case -1:
        fprintf(stderr, "fork failed.\n");
        break;
    case 0:
        pid = getpid();
        ppid = getppid();

        printf("hi, I'm the child!\n");
        printf("[child] My process id is %d\n", pid);
        printf("[child] My parent's process id is %d\n", ppid);
        break;
    default:
        pid = getpid();

        printf("hi, I'm the parent!\n");
        printf("[parent] My process id is %d\n", pid);
        printf("[parent] My child's process id is %d\n", childPid);
    }


    return 0;
}

