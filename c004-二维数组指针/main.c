#include <stdio.h>

int main()
{
     int a[2][4] = {{0,1,2,3},{4,5,6,7}};  
     int (*p)[4] = a;  //有点不理解 p 到底是个啥，它是一级指针还是二级指针?
                       //它是数组指针，算是一级指针
     int *s = a;   //我想知道这个会怎样 //warning: initialization of ‘int *’ from incompatible pointer type ‘int (*)[4]’
                   //这一句在编译器看来相当于 int *s = a[0];
     int sizea = sizeof(a);
     int sizep = sizeof(p);
     int sizepa = sizeof(*p);  //它为啥是16字节? //你zz吗？对p寻址不就是一维数组吗，4*4byte
 
     printf("s[0] = %d\n",0[s] ); //所以说，s是一维数组指针
     printf("s[1] = %d\n",1[s] ); //由此可见，指针变量里存的真的就是一个首地址，但是为了界定
     printf("s[3] = %d\n",3[s] ); //指针对应的变量的内存范围，需要用指针的类型来指定
     printf("s[4] = %d\n",4[s] ); //从这里就开始越界了，但是二维数组连续存放
     printf("s[7] = %d\n",7[s] ); //所以也能访问到值
     

     printf("p[1][2] = %d\n", *(*(p+1)+2) ); //p 和 a 基本上可以互换，除了一点，a 是常量，它的值不能变，不能执行 a++

     printf("a[0][2] = %d\n",0[a][2] ); //记得这个东西吗，数组下标也是一种运算符
     printf("a[0][2] = %d\n",0[p][2] ); //既然数组下标只是一种运算符，那么这么写也是可以的喽
     printf("sizea = %d\n",sizea );
     printf("sizep = %d\n",sizep );
     printf("size(&a) = %d\n",sizeof(&a) );  //size(&a) = 8 //&a的类型为int (*)[4]，也就是等价于 p
     printf("size(*s) = %d\n",sizeof(*s) );  //4
     printf("sizepa = %d\n\n--------\n\n",sizepa );

//还有一个问题，我记得 char **argv 和 char *argv[]
//关于 char *argv[] 和 char **argv，因为在函数形参的 [] 表示指针而不是数组，
//所以 char *argv[] 其实被转化成 char **argv
//http://akaedu.github.io/book/ch23s06.html
     char ** av;
     char *strv[4] = { "first", "second", "third", "forth" };
     av = strv;  //av 是二级指针，strv 是二维数组，为什么下面的不可以
     printf("strv[0] = %s\n", *av);
     int **pv = a; //warning: initialization of ‘int **’ from incompatible pointer type ‘int (*)[4]’ [-Wincompatible-pointer-types]
                   //这么说来，只有一个解释，字符串不等价于字符数组
     printf("size(*pv) = %d\n",sizeof(*pv) );  //8 //pv是二级指针，所以它存放的变量（指针）是8byte，相当于两个int
     printf("pv[0]=%d\n",pv[0]);  //0              //所以这里好像是跳着数
     printf("pv[1]=%d\n",pv[1]);  //2              //但是问题来了，既然每个变量是8byte，那么为什么不乱码，还能读取出来正确的int
     printf("pv[2]=%d\n",pv[2]);  //4              //可能是 printf 函数的特殊处理，毕竟*p取出来的值为 0x100000000
     printf("pv[3]=%d\n",pv[3]);  //6              //破案了。。The int argument..（man 3 printf） 看来 printf 的 %d 只能处理 int，再长就舍去了
     printf("pv[4]=%d\n",pv[4]);  //?

     printf("pv[0]=%p\n",pv[0]);                   //pv[0]=0x100000000
     printf("pv[0]=%ld\n",pv[0]); //4294967296     //输出长整型就现出原形了，>>> int('100000000', 16)
                                                   //                        4294967296


//在gdb中用 “x/32b p”，“x/32b s”，“x/32b pv”查看，发现它们的值完全一样
//p s pv 存放的值都是0x7ffffffee3b0（&a[0][0]的地址，用 p &a[0][0]查看）
//区别在于使用的时候对它们的解释不同
/*  (gdb) p pv
    $15 = (int **) 0x7ffffffee3b0
    (gdb) p p
    $16 = (int (*)[4]) 0x7ffffffee3b0
    (gdb) p s
    $17 = (int *) 0x7ffffffee3b0
    (gdb) p &a[0][0]
    $18 = (int *) 0x7ffffffee3b0

    (gdb) p pv+1
    $19 = (int **) 0x7ffffffee3b8
    (gdb) p p+1
    $20 = (int (*)[4]) 0x7ffffffee3c0
    (gdb) p s+1
    $21 = (int *) 0x7ffffffee3b4

    (gdb) p *s
    $22 = 0
    (gdb) p *p
    $23 = {0, 1, 2, 3}
    (gdb) p *pv
    $24 = (int *) 0x100000000
*/
     return 0;
 }
