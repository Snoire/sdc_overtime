#include <stdio.h>
#include <string.h>
#include <math.h>

int top = -1;//top 变量时刻表示栈顶元素所在位置


void push(char *a, char elem)
{
    a[++top] = elem;
}


void pop(char *a)
{
    if (top == -1)
        return;

    //输出时要按照正确的格式显示给用户
    if (a[top] >= 10)
        printf("%c", a[top]+55);
    else
        printf("%d", a[top]);

    top--;
}


//将各进制数转换成十进制数
int scaleFun(char *data, int system)
{
    int k = (int)strlen(data)-1;
    int system_10_data = 0;
    int i;

    for (i=k; i>=0; i--)
    {
        int temp;

        if (data[i]>=48 && data[i]<=57)
            temp = data[i]-48;
        else
            temp = data[i]-55;

        system_10_data += temp * pow(system, k-i);
    }

    return system_10_data;
}



int main()
{
    char data[100];
    int system, system_10_data, newSystem;

    printf("进制转换器，请输入原数据的进制（2-36）:");
    scanf("%d", &system);

    printf("请输入要转换的数据：");
    scanf("%s", data);

    printf("请输入转换后的数据的进制：");
    scanf("%d", &newSystem);

    system_10_data = scaleFun(data, system);

    while (system_10_data/newSystem)
    {
        push(data, system_10_data%newSystem);
        system_10_data /= newSystem;
    }
    push(data, system_10_data%newSystem);

    printf("转换后的结果为：\n");

    while (top != -1)
        pop(data);

    printf("\n");

    return 0;
}


//超过十进制就不好处理了，比如 24 进制时不能区分 19 到底是一位数还是两位数

