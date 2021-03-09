# include <stdio.h>
# include "hFile1.h"
# include "hFile2.h"
# include "hFile3.h"

int main()
{
	printf("+>> func1....\n");
    func1();        //c.biancheng.net/cpp/html/3378.html  递归解决分鱼问题

    printf("+>> func2....\n");
    func2();        //验证 for 循环的循环条件

    printf("+>> func3....\n");
    func3();        //测试枚举类型成员的使用方式
    
    return -2;      //这个影响程序运行之后的 echo $? 不可以是负数，因为返回值是有符号整数
                    //在 main 函数中， return(0) 和 exit(0) 是等价的 apue 7.3
}
