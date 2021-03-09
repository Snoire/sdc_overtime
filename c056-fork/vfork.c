/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2019.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 24-4 */
/* 应该避免使用 vfork */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

//#define EXIT_FAILURE    1   /* Failing exit status.  */             /* 这两个定义在 stdlib.h */
//#define EXIT_SUCCESS    0   /* Successful exit status.  */
#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

int main(int argc, char *argv[])
{
    int istack = 222;

    switch (vfork()) {
    case -1:
        errExit("vfork");

    case 0:             /* Child executes first, in parent's memory space */
        sleep(3);                   /* Even if we sleep for a while,
                                       parent still is not scheduled */
        write(STDOUT_FILENO, "Child executing\n", 16);   /* 没见过这种用法欸 */
        istack *= 3;                /* This change will be seen by parent */
        _exit(EXIT_SUCCESS);                             /* 这里为啥用 _exit */
        /* The child of a vfork() should not terminate by calling exit(), since that would cause the parent’s stdio buffers to be flushed and closed. */

    default:            /* Parent is blocked until child exits */
        write(STDOUT_FILENO, "Parent executing\n", 17);
#if 0        /* 这样写会把缓冲区的字符丢掉 */
        setbuf(stdout, NULL);
        printf("istack=%d", istack);
        _exit(EXIT_SUCCESS);
#elif 0   /* 设置无缓冲就不会了 */
        setbuf(stdout, NULL);
        printf("istack=%d", istack);
        _exit(EXIT_SUCCESS);
#else
        printf("istack=%d\n", istack);
        exit(EXIT_SUCCESS);
#endif
    }
}

