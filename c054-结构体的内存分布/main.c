#include <stdio.h>

int main()
{
    struct foostruct{  //把大的放在前面会好一点 https://www.jianshu.com/p/666852837034
        char c;    //1
        int a[2];  //8
        double d;  //8
    };

    struct foostruct foo[4] = {
        {'0', {0,1}, 0.1},
        {'1', {10,11}, 1.1},
        {'2', {20,21}, 2.1},
        {'3', {30,31}, 3.1}
    };

    printf("sizeof struct: %d\n", sizeof(struct foostruct)); //24

    return 0;
}

/* 
   结构体对齐的原则可以总结为：
   结构体起始地址按最大变量字节数 sizeof(double) 对齐；
   结构体内每个变量按照自身字节数对齐；
   结构体的大小 sizeof(struct foostruct) 是最大变量字节数的整数倍；
   */
