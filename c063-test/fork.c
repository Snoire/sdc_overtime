#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdarg.h>
#include<errno.h>


int main(int argc, char *argv[])
{
    pid_t pid;
    int loop;
    printf("P:%d C:%d\n",getpid(),getppid()); 

    for (loop = 0; loop < 2; loop++) {
        if ((pid = fork()) < 0) {
            fprintf(stderr, "[fork:%d]: ", loop);
            return -1;
        } else if (pid == 0) {
            printf("[Child process]P:%d C:%d\n",getpid(),getppid()); 
        } else {
            sleep(2);
        }
    }

    return 0;
}
