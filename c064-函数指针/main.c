#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
        return a>b ? a : b;
}

int main()
{
//    int *pf = NULL;
//    pf = max(1,2);
    int a,b;
    int *c[] = {&a, &b};
    char cmd[128] = "";

//    printf("num is %d\n", sizeof(c)/sizeof(int*)); // 计算结构体成员数量
    sprintf(cmd, "echo 'num is %d' > tmp.txt", sizeof(c)/sizeof(int*));
    printf("cmd: |%s|\n", cmd);
    system(cmd);

    return 0;
}

