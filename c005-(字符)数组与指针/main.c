#include <stdio.h>
int main()
{
    int arr[] = {99,15,100,33,29};    //这是一个数组
    int *p = arr;                     //数组名被转化成它第一个元素的地址了
    int (*p2)[5]= &arr;               //对数组名取地址是 数组指针

    printf("arr[0]= %d\n",*p);
    printf("arr[0]= %d\n",(*p2)[0]);

    printf("p:  %p\n", p);
    printf("p2: %p\n\n", p2);

    printf("p+1:  %p\n", p+1);          //加了 4 字节
    printf("p2+1: %p\n\n", p2+1);       //加了 20 字节

    char str[12] = "str";
    printf(" str: %p\n", str);          //可以看到这两地址都是一样的，只是它们的类型不一样
    printf("&str: %p\n", &str);         //因为字符串其实就是（字符）数组，所以和上面是一样的

    printf("str+1:  %p\n", str+1);      //加了 1 字节
    printf("&str+1: %p\n\n", &str+1);   //加了 12 字节

//    scanf("%s", &str);                //所以 scanf 里加不加 & 是一样的（一般不加）
//    printf("str: %s\n", str);

    return 0;
}
