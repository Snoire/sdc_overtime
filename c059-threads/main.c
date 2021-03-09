/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2019.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 29-1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/syscall.h> 
#include <unistd.h>
#include <pthread.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)


static void * threadFunc(void *arg)
{
    char *s = (char *) arg;
    sleep(3);

    printf("Message from thread: |%s|\n", s);
    printf("Message from thread: pthread_t: %ld\n", (long) pthread_self());
    printf("Message from thread: tid: %ld\n", syscall(SYS_gettid));

    return (void *) strlen(s);
}

int main(int argc, char *argv[])
{
    pthread_t t1;
    void *res;
    int s;

    s = pthread_create(&t1, NULL, threadFunc, "Hello world\n");
    if (s != 0)
        errExit("pthread_create");

    sleep(1);
    printf("Message from main(): hi!\n");
    printf("Message from main(): child pthread_t: %ld\n", (long) t1);
    printf("Message from main(): self pthread_t:  %ld\n", (long) pthread_self());
    printf("Message from main(): tid: %ld\n", syscall(SYS_gettid));
    s = pthread_join(t1, &res);
    if (s != 0)
        errExit("pthread_join");

    printf("Thread returned %ld\n", (long) res);

    exit(EXIT_SUCCESS);
}
