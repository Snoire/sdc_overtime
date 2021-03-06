#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define QLEN 10
/*
 * Create a server endpoint of a connection.
 * Returns fd if all OK, <0 on error.
 * name : file_name
 */
int serv_listen(const char *name)
{
    int fd, len, err, rval;
    struct sockaddr_un un;

    /* create a UNIX domain stream socket */
//    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    if ((fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)   /* AF_UNIX 和 PF_UNIX 好像一样 */
        return (-1);

    /* in case it already exists */
    unlink(name);

    /* fill in socket address structure */
    memset(&un, 0, sizeof(un)); //bzero ok
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, name);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(name);

    /* bind the name to the descriptor */
    if (bind(fd, (struct sockaddr *) &un, len) < 0) {
        rval = -2;
        goto errout;
    }

    if (listen(fd, QLEN) < 0) { /* tell kernel we're a server */
        rval = -3;
        goto errout;
    }

    return (fd);

errout:
    err = errno;                /*tmp store in case of close error */
    close(fd);
    errno = err;
    return (rval);
}

/*uidptr: in/out param which shows the caller*/
int serv_accept(int listenfd, uid_t * uidptr)
{
    int clifd, len, err, rval;
    struct sockaddr_un un;
    struct stat statbuf;        /*display file or file system status */

    len = sizeof(un);           /*watch out here */
    if ((clifd = accept(listenfd, (struct sockaddr *) &un, (socklen_t *) &len)) < 0)
        return (-1);            /* often errno=EINTR, if signal caught */

    /* obtain the client's uid from its calling address */
    len -= offsetof(struct sockaddr_un, sun_path);      /* len of pathname */
    un.sun_path[len] = 0;       /* null terminate */

    if (stat(un.sun_path, &statbuf) < 0) {
        rval = -2;
        goto errout;
    }

    if (S_ISSOCK(statbuf.st_mode) == 0) {
        rval = -3;              /* not a socket */
        goto errout;
    }

    if (uidptr != NULL)
        *uidptr = statbuf.st_uid;       /* return uid of caller */

    /* we're done with pathname now */
    unlink(un.sun_path);
    printf("unlink %s\n", un.sun_path);

    return (clifd);

errout:
    err = errno;
    close(clifd);
    errno = err;
    return (rval);
}


int main(void)
{
    int lfd, cfd, n, i;
    uid_t cuid;
    char buf[1024];

    lfd = serv_listen("foo.socket");
    if (lfd < 0) {
        switch (lfd) {
        case -3:
            perror("listen");
            break;
        case -2:
            perror("bind");
            break;
        case -1:
            perror("socket");
            break;
        }
        exit(-1);
    }

    cfd = serv_accept(lfd, &cuid);
    if (cfd < 0) {
        switch (cfd) {
        case -3:
            perror("not a socket");
            break;
        case -2:
            perror("a bad filename");
            break;
        case -1:
            perror("accept");
            break;
        }

        exit(-1);
    }

    //watch out we get the cuid
    while (1) {
r_again:
        n = read(cfd, buf, 1024);

        if (n == -1) {
            if (errno == EINTR)
                goto r_again;
        } else if (n == 0) {
            printf("the other side has been closed.\n");
            break;
        }

//        write(cfd, buf, n);
//        sleep(5);
        for (i = 0; i < n; i++)
            buf[i] = toupper(buf[i]);

        write(cfd, buf, n);
        write(cfd, buf, n);
    }

    close(cfd);
    close(lfd);
    unlink("foo.socket");
    return 0;
}
