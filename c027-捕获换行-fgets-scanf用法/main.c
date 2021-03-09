#include <stdio.h>

char clearInput;

/* fgets 的用法 */
int fun1()
{
    int value, retvalue;
    char str[5];
//    retvalue = scanf("%d",value);
//    printf("value = %d\n",value);
//    printf("retvalue = %d\n",retvalue);

    fgets(str, 5, stdin);
    printf("str = %s\n", str);
    //输出捕获的第一个字符的 ASCII 值
    printf("str[0] = %d\n", *str); //换行的 ASCII 是 10
    printf("str[1] = %d\n", *(str+1)); 
    printf("str[2] = %d\n", *(str+2)); 
    printf("str[3] = %d\n", *(str+3)); 
    printf("str[4] = %d\n", *(str+4)); 
    if(*str==10)
        printf("bingo\n");

/*
    fgets(str, 2, stdin);
    printf("str = %s\n", str);
    //输出捕获的第一个字符的 ASCII 值
    printf("str[0] = %d\n", *str); //换行的 ASCII 是 10
    printf("str[1] = %d\n", *(str+1)); //换行的 ASCII 是 10
    if(*str==10)
        printf("bingo\n");
*/
//    while((clearInput = getchar()) != '\n' && clearInput != EOF);  //如果缓冲区里面没有东西，在这里就会阻塞

    if( *(str+3)!='\n' && *(str+3)!=0 )  //只有在第四个字符既不是\n，也不是\0的时候，也就是说缓冲区里有多余的字符时，才能去清空缓冲区，否则会卡住
    {
        scanf("%*[^\n]"); //逐个读取缓冲区中\n之前的其它字符
        scanf("%*c");     //再将这个\n读取并丢弃
    }
    
    return 0;
}

/* scanf 的用法 */
int fun2()
{
    int value, retvalue;
    char str[5] = "";
    char c[10] = "";
    char linebreak;
    int ret = 0;

    ret = scanf("%4[^\n]", str);   //最多读取4个字符（不包括\n），如果超过，那么缓冲区里会有残留字符和\n（可能有多个\n，看你输入了几个）
    printf("ret: %d\n", ret);     //如果输入\n，返回值是0；EOF 是 -1；否则是1，无论是否超过范围，它都成功读取并保存了一个值。
    scanf("%*[^\n]"); //（从下一行开始阅读注释）所以需要先清空除了\n的其他字符，就算不存在其他字符也没有影响，顶多这个scanf读取失败，因为能够确定现在的缓冲区至少有一个\n字符，所以不会卡住的。
    scanf("%1[\n]", c);   //所以如果前面的scanf输入超过4个字符，这里就会读取失败，什么也读不到。（转到上一行）
//    scanf("%[\n]", c);   //如果这么写，那么scanf会一直读取换行符，看起来好像一直换行scanf一直等待输入没用一样，其实scanf一直在读取换行符，保存在c字符串里。所以需要指定读取一个字符。

//    scanf("%c", &linebreak);   //事实上经过上面的处理，缓冲区只剩下一个\n，用%c就可以读取出来。
//    printf("linebreak: |%c|\n", linebreak);
//    printf("linebreak: |%d|\n", linebreak);

/* 总结一下捕获 \n 的标准流程
   scanf("%4[^\n]", str);
   scanf("%*[^\n]");
   scanf("%1[\n]", &linebreak);  //或者 scanf("%c", &linebreak);
   //可惜无法捕获 Ctrl + D
*/

    printf("str = |%s|\n", str);
    //输出捕获的第一个字符的 ASCII 值
    printf("str[0] = %d\n", *str); //换行的 ASCII 是 10 printf("str[1] = %d\n", *(str+1)); 
    printf("str[1] = %d\n", *(str+1)); 
    printf("str[2] = %d\n", *(str+2)); 
    printf("str[3] = %d\n", *(str+3)); 
    printf("str[4] = %d\n\n", *(str+4)); 

    printf("c = |%s|\n", c);
    printf("c[0] = %d\n", *c);
    printf("c[1] = %d\n", *(c+1)); 
    printf("c[2] = %d\n", *(c+2)); 
    printf("c[3] = %d\n", *(c+3)); 
    printf("c[4] = %d\n", *(c+4)); 
    if(*str==10)
        printf("bingo\n");
    
    return 0;
}

int main()
{
    fun2();
    
    return 0;
}
