/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2019.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 25-2 */
/* Usage: 
   ./fork_stdio_buf
   ./fork_stdio_buf > file.txt
   cat file.txt
   */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("Hello world\n");
    write(STDOUT_FILENO, "Ciao\n", 5);

    if (fork() == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    /* Both child and parent continue execution here */

    exit(EXIT_SUCCESS);
}


