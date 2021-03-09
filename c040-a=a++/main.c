#include <stdio.h>

int main()
{
    int a = 5;
    int b = 5;
    int i = 5;
    a = a++;    //warning: operation on ‘a’ may be undefined [-Wsequence-point]
    b = ++b;    //warning: operation on ‘b’ may be undefined [-Wsequence-point]

    i = (++i)+(++i)+(++i)+(++i);  //warning: operation on ‘i’ may be undefined [-Wsequence-point]

    printf("a = %d\n", a); //a == 5
    printf("b = %d\n", b); //b == 6
    printf("i = %d\n", i); //i == 31

    return 0;
}

/************************************************************************************************************\
*                                                                                                            *
* 之前我学到的前置运算符（前自增）先自增，再赋值，后置运算符先赋值，后自增。但是在这里解释不通，说明这不对。 * 
* 今天看到一个说法，两种都是先自增，但是前置运算符（++a）返回增加后的值；后置运算符（a++）返回本来的值。     *
*                                                                                                            *
* https://stackoverflow.com/questions/24853/c-what-is-the-difference-between-i-and-i                         *
* ++i will increment the value of i, and then return the incremented value.                                  *
* i++ will increment the value of i, but return the original value that i held before being incremented.     *
*                                                                                                            *
* 跟上面的关系不大，在两个 Sequence Point 之间，同一个变量的值只允许被改变一次，这些表达式都是 undefined     *
*                                                                                                            *
\************************************************************************************************************/
