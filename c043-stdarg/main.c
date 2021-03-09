#include <stdio.h>
#include <stdarg.h>

//The function foo takes a string of format characters and prints out
//the argument associated with each format character based on the type.
void foo(char *fmt, ...)   /* '...' is C syntax for a variadic function */
{
    va_list ap;
    int d;
    char c, *s;

    va_start(ap, fmt);
    while (*fmt) {
        switch (*fmt++) {
        case 's':              /* string */
            s = va_arg(ap, char *);
            printf("string %s\n", s);
            break;
        case 'd':              /* int */
      //      printf("ap address is: %p\n", ap); //这里很诡异，如果加了这一句，下面一句就会有问题。先放一放，以后有时间再细究
            printf("the ap before is: %d\n", *ap); //这个 ap 是 va_list 类型，没必要知道它到底是什么东西
            d = va_arg(ap, int);
            printf("int %d\n", d);
            break;
        case 'c':              /* char */
            /* need a cast here since va_arg only
               takes fully promoted types */
            c = (char) va_arg(ap, int);
            printf("char %c\n", c);
            break;
        }
    }
    va_end(ap);
}

int main()
{
    foo("dsc", 10, "hi", 'c');  //第一个参数定义了后面几个参数的格式

    return 0;
}
