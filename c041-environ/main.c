#include <stdio.h>
#include <stdlib.h>     //for getenv()
#include <string.h>     //for strcpy()
extern char **environ;  //for environ

int main()
{
#if 0
    printf("The environ1 is: %s\n", environ[0]);
    printf("The environ2 is: %s\n", environ[1]);
    printf("The environ3 is: %s\n", environ[2]);
    printf("The environ4 is: %s\n", environ[3]);
    printf("The environ5 is: %s\n", environ[4]);
    printf("The environ6 is: %s\n", environ[5]);
    printf("The environ7 is: %s\n", environ[6]);
    printf("The environ8 is: %s\n", environ[7]);
    printf("The environ9 is: %s\n", environ[8]);
    printf("The environ10 is: %s\n", environ[9]);
    printf("The environ11 is: %s\n", environ[10]);
#elif 0   //这种方法我居然没想到。。
    char **env = environ;
    while(*env) {  //如果字符串不为空，那么它的地址就不是 NULL。更准确的说，列表的最后是一个指向 NULL 的指针，和 argv 是一样的
        printf("%s\n", *env);
        env++;
    }
//tlpi page 171
//An alternative method of accessing the environment list is to declare a third argument to the main() function:
//int main(int argc, char *argv[], char *envp[])
//but its scope is local to main().
#elif 1  //找了一下，发现有 getcwd() 这个函数→_→
    char pwd[64] = "";
//    pwd = secure_getenv("PWD");  //这样是不对滴  //要用 secure_getenv() 需要加这个宏 _GNU_SOURCE
    strcpy(pwd, getenv("PWD"));    //所以你干嘛不直接 char pwd[] = getenv("PWD");
    printf("$PWD = %s\n", pwd);
#endif

    return 0;
}

