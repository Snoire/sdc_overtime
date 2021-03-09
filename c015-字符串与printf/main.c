# include <stdio.h>
int main()
{
    const char * unknown = "first\n"\
                                       "second\n"\
                            "third\n";
    printf("%s\n",unknown);

    const char * unknown1 = "first""second""third";
    printf("%s\n",unknown1);

    char st[]="连续写两个常量字符串，等于连接起来"; //字符串变量，即字符数组就不能这样写了，得用 sprintf 之类的函数
    char str[]="为什么上面的指针可以直接用？";
    printf("%s\n",st);
    printf("%s\n",str);
    printf("%s\n",&str); //这两句输出效果相同啊   format '%s' expects argument of type 'char *', but argument 2 has type 'char (*)[43]' [-Wformat=]

    return 0;
}
