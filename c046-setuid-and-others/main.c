#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h> 

int main()
{
    //看一下 setuid 到底是什么，会不会把 set-user-ID-root 程序不可逆地取消特权
    uid_t ruid, euid, suid;
    getresuid(&ruid, &euid, &suid);
    printf("ruid: %d, euid: %d, suid: %d\n", ruid, euid, suid);

    //用 setuid “临时”切换成普通用户
    if (setuid(ruid) == -1)
        printf("setuid error!\n");

    getresuid(&ruid, &euid, &suid);
    printf("ruid: %d, euid: %d, suid: %d\n", ruid, euid, suid);

// 破案了。。
/*
// 如果可执行文件的拥有者是 root，调用 setuid 会同时修改 suid
$ sudo chown root:root c46
$ sudo chmod u+s c46
$ ./c46
ruid: 1000, euid: 0, suid: 0
ruid: 1000, euid: 1000, suid: 1000

// 如果是其他人，不会修改 suid
$ sudo chown len:len c46
$ sudo chmod u+s c46
$ ./c46
ruid: 1000, euid: 1001, suid: 1001
ruid: 1000, euid: 1000, suid: 1001
*/

//    sleep(30);       // 在这里可以用 cat /proc/<pid>/status 查看


    return 0;
}

