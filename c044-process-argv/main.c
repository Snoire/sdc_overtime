#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

extern char *program_invocation_name;
extern char *program_invocation_short_name;

int main()
{
/*********************************************\
*  $ ./c44 &                                  *              
*  [1] 16833                                  *
*  the process id is 16833                    *
*  $ ps                                       *
*    PID TTY          TIME CMD                *
*     7785 tty3     00:01:14 zsh              *
*     16833 tty3     00:00:00 c44             *
*     16836 tty3     00:00:00 ps              * 
\*********************************************/
#if 1
    pid_t pid, ppid;
    pid = getpid();
    printf("the process id is %d\n", pid);

    ppid = getppid();
    printf("the parent of process id is %d\n", ppid);

	printf("the full name of program is %s\n", program_invocation_name);
	printf("the short name of program is %s\n", program_invocation_short_name);

    sleep(20);
#endif

    return 0;
}

