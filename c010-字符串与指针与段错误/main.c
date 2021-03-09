//字符串与指针
//char *argv 与 char **argv

# include <stdio.h>
int main()
{
#if 0
    char str[2][6] = {"abcde","xyzo"};
    char *pstr[] = {str[0],str[1]};    //pstr 是一个有两个元素的数组，每个元素的类型是 char *
    char **ppstr = pstr;            //ppstr 是一个二级指针，指向 pstr 这个数组的转化成的指针

    printf("sizeof(str)= %d\n",sizeof(str));
    printf("sizeof(pstr[1])= %d\n",sizeof(pstr[1]));
    printf("sizeof(char *)= %d\n",sizeof(char *));
    printf("sizeof(char )= %d\n",sizeof(char ));
    printf("sizeof(int *)= %d\n",sizeof(int *));
    printf("sizeof(int )= %d\n",sizeof(int ));
    printf("sizeof(ppstr )= %d\n\n",sizeof(ppstr ));

    printf("str[1]=%s\n",str[1]);
    printf("str[1][2]=%c\n",str[1][2]);  //这里访问的是一个字符，如果用 %s ，就会发生 segmentation fault ，估计一直没碰到 \0，访问到无权访问的空间了

    printf("pstr[1]=%s\n",pstr[1]);
    printf("pstr[1][2]=%c\n",pstr[1][2]);

    printf("ppstr[1]=%s\n",ppstr[1]);
    printf("ppstr[1][2]=%c\n",ppstr[1][2]); //可以看到它们的效果是一样的，其实把数组下标看作一种运算符就好理解一点，大概

    printf("*(ppstr+1)=%s\n",*(ppstr+1));
    printf("*(*(ppstr+1)+2)=%c\n",*(*(ppstr+1)+2));
#else
    // 验证空指针被 printf 以 %s 输出的结果
    char *str = "hi, all";
    printf("one: |%s|\n", str);

    str = NULL;
    printf("two: |%s|\n", str);   // 会输出 two: |(null)|，也就是说允许 str 为空指针

    char str1[10] = "";
    printf("three: |%.16s|\n", str1);
#endif

    return 0;
}
