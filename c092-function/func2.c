// https://blog.csdn.net/zhushh/article/details/51045185
#include <stdio.h>

void input(int num) {
    printf("Input: %d\n", num);
}
 
void receive(int num) {
    printf("Receive: %d\n", num);
}
 
void print(int num) {
    printf("Print: %d\n", num);
}

typedef void (*func_t)(int);

func_t lambda(int num, func_t func)
{
    func(num);
    if (num > 0) {
        return receive;
    } else {
        return print;
    }
}

int main()
{
    int num;
    func_t func;
    while (scanf("%d", &num)) {
        func = lambda(num, input);
        func(num);
    }
    return 0;
}
