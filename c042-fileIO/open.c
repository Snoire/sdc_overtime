#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd, ret;
    char str[2] = "";
    fd = open("scan_log_mode", O_WRONLY | O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if (fd == -1)
        printf("failed to open scan_log_mode.\n");
    else {
        write(fd, argv[1], 1); 
        if (ret <= 0)
            printf("failed to write to scan_log_mode\n");
        close(fd);
    }

    if (access("scan_log_mode", F_OK) == 0)
    {
        fd = open("scan_log_mode", O_RDONLY); //如果不重新打开读不出来，因为之前是只写模式
        if (fd == -1) {
            printf("failed to open scan_log_mode.\n");
        } else {
            ret = read(fd, str, 1);
            if (ret <= 0)
                printf("failed to read scan mode\n");
            printf("the mode is %s\n", str);
            close(fd);
        }
    } else {
        /*  */
        printf("file does not exit!\n");
    }




    return 0;
}
