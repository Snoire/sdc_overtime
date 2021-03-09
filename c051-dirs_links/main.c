#define _DEFAULT_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

int creatfile(const char *file)
{
    int fd;
//    fd = open(file, O_CREAT|O_RDWR|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);  // 644
    fd = open(file, O_CREAT|O_RDWR|O_TRUNC, 0644);          //感觉这样写更直观啊，八进制必须以 0 开头
    if (fd == -1)
        fprintf(stderr, "open %s error!\n", file);
    close(fd);
    printf("create file: %s\n", file);

    return 0;
}

long statfile(const char *file)
{
    struct stat filestat;

    if (stat(file, &filestat))
        fprintf(stderr, "stat %s error!\n", file);
    printf("i-node of %s: %40ld\n", file, filestat.st_ino);

    return filestat.st_ino;
}

int filetype(unsigned char type)
{
    switch (type) {
    case DT_REG:
        printf("regular file"); break;
    case DT_LNK:
        printf("symbolic link"); break;
    case DT_DIR:
        printf("directory"); break;
    case DT_BLK:
        printf("block device"); break;
    case DT_CHR:
        printf("character device"); break;
    case DT_FIFO:
        printf("FIFO"); break;
    case DT_SOCK:
        printf("socket"); break;
    default:
        printf("unknown type"); break;
    }

    printf("\n");

    return 0;
}

int main()
{
    long inode, inode2;
#if 0
    /* Existing file: x
       Action performed: mv x y  */
    creatfile("x");
    inode = statfile("x");
    printf("mv x y\n");
    rename("x", "y");
    if (inode == statfile("y"))
        printf("x and y are the same file. mv succeeded\n");
    unlink("y");

#elif 0
    /* Existing file: x, y
       Action performed: mv x y  */
    creatfile("x");
    inode = statfile("x");
    creatfile("y");
    inode2 = statfile("y");
    if (inode != inode2)
        printf("x and y are not the same file.\n");
    printf("mv x y\n");
    rename("x", "y");
    if (inode == statfile("y"))
        printf("The original y file is overwritten.\n");
    unlink("y");

#elif 0
    /* Existing file: x, y. x and y refer to the same file
       Action performed:
       ln x y
       mv x y  */
    creatfile("x");
    inode = statfile("x");
    printf("ln x y\n");      /* x and y refer to the same file */
    link("x", "y");
    inode2 = statfile("y");
    if (inode == inode2)
        printf("x and y refer to the same file.\n");
    printf("mv x y\n");
    rename("x", "y");
    printf("The x and y files still exist. no changes are made (and the call succeeds)\n");
    unlink("x");
    unlink("y");

#elif 0
    /* Existing file: x, y(symbolic link)
       Action performed:
       ln -s nonexistentfile y
       mv x y  */
    char buf[128] = "";
    creatfile("x");
    inode = statfile("x");
    printf("ln -s nonexistentfile y\n");
    symlink("nonexistentfile", "y");
    inode2 = statfile("y");
    readlink("y", buf, sizeof(buf));
    printf("readlink y: %s\n", buf);
    printf("mv x y\n");
    rename("x", "y");
    if (inode == statfile("y"))
        printf("symbolic link is treated as a normal pathname(the existing newpath symbolic link is removed)\n");
    unlink("y");

#elif 0
    /* Removing a Directory */
    printf("mkdir dir\n");
    mkdir("dir", 0755);
    creatfile("dir/x");
    printf("rm dir\n");
    if (rmdir("dir") == -1)
        printf("failed to remove dir due to the directory isn't empty.\n");

    printf("rm dir/x\n");
    unlink("dir/x");
    printf("rm dir\n");
    if (rmdir("dir") == 0)
        printf("rm succeeded.\n");
    // remove("dir/x");  //the same with unlink("dir/x");
    // remove("dir");    //the same with rmdir("dir");

#elif 1
    /* Reading Directories */
    DIR *pdir;
    struct dirent *pdirent;

    pdir = opendir(".");
    errno = 0;
    while(pdirent = readdir(pdir)) {   //在 wsl 中，目录中的 .. 的 inode 不准
        printf("%-20ld  ", pdirent->d_ino);
        printf("%-20s  ", pdirent->d_name);
        filetype(pdirent->d_type);
        pdirent->d_ino = 0;
    }
    if (errno != 0) {
        fprintf(stderr, "readdir error\n");
    } else {
        printf(" -- We reached end-of-directory --\n");
    }
    closedir(pdir);

#else

#endif

    return 0;
}

