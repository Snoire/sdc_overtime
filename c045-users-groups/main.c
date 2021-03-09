#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> //for getpwnam and getuid
#include <pwd.h>       //for getpwnam only
#include <unistd.h>    //for getuid only
#include <shadow.h>    //for getspnam

char *userNameFromId(uid_t uid)
{
    struct passwd *pwd;
    pwd = getpwuid(uid);

    return (pwd == NULL) ? NULL : pwd->pw_name;
}

uid_t userIdFromStr(const char *name)
{
    struct passwd *pwd;
    uid_t uid;
    char *endptr;
    if (name == NULL || *name == '\0')
        return -1;
    uid = strtol(name, &endptr, 10);
    if (*endptr == '\0')
        return uid;

    pwd = getpwnam(name);
    if (!pwd)
        return -1;

    return pwd->pw_uid;
}

int showUserName()
{
    uid_t uid, euid;
    gid_t gid, egid;
    uid = getuid();
    euid = geteuid();
    gid = getgid();
    egid = getegid();
    printf("Hi, %s, ", userNameFromId(uid));
    printf("gid is: %d\n", gid);
    printf("euid is: %d, egid is: %d\n", euid, egid);

    return 0;
}

int printpasswd()
{
    struct passwd *pwd;
    while ((pwd = getpwent()))
        printf("%-8s %5ld\n", pwd->pw_name, (long)pwd->pw_uid);

    return 0;
}

int main(int argc, char **argv)
{
    char *username, *passwd, *encrypted, *p;
    struct passwd *pwd;
    struct spwd *spwd;
    size_t len;
    long lnmax;

    showUserName();
//    printpasswd();
    lnmax = sysconf(_SC_LOGIN_NAME_MAX);
    printf("lnmax is %ld\n", lnmax);

    username = malloc(lnmax);    //我觉得这里lnmax加1更好吧，lnmax不包括最后的最后的\0
                                 //没必要，下面使用的fgets会确保最后一位一定有\0，参见c27
    printf("Username: ");
    fflush(stdout);
    fgets(username, lnmax, stdin);

//    printf("username is %s\n", username);
    len = strlen(username);
    if (username[len - 1] == '\n') //如果username的长度小于lnmax-1（正常情况下就是这样），字符串最后有一个\n，后面是\0，就把\n去掉
        username[len - 1] = '\0';  //如果等于lnmax-1，则正好放下，最后一个为\0；大于lnmax-1则截断

    pwd = getpwnam(username);
    spwd = getspnam(username);     //好像要加sudo执行才能执行
                                   //所以要把可执行文件拥有者设为root，再设置权限为4755就行了
    if (spwd)       //不为NULL，说明存在 shadow password record
        pwd->pw_passwd = spwd->sp_pwdp;
    printf("pwd->pw_passwd: %s\n", pwd->pw_passwd);
    
    passwd = getpass("Passwd: ");
    
    encrypted = crypt(passwd, pwd->pw_passwd);
    for (p = passwd; *p != '\0'; ) //清零，毁尸灭迹
        *p++ = '\0';
//    memset(password, 0, sizeof(password));  //password是指针啊，sizeof(p)永远是4啊！ //所以说不知道它的长度，还是用上面的方法吧
    printf("encrypted: %s\n", encrypted);  //手动验证过了，和文件中的是一样的

    if (!strcmp(encrypted, pwd->pw_passwd)) {
        printf("Successfully authenticated: UID=%ld\n", (long) pwd->pw_uid);
    }

    return 0;
}
