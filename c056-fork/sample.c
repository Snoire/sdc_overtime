#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid, ppid;
    printf("hi, I'm the parent!\n");

    fork();

    pid = getpid();
    printf("the process id is %d\n--------------------------\n", pid);

    ppid = getppid();
    printf("the parent of process id is %d\n-----------------------------------\n", ppid);

    return 0;
}

