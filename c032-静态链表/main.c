#include <stdio.h>

#define maxSize 6

typedef struct {
    int data;
    int cur;
}component;


void reserveArr(component *);             //将结构体数组中所有分量链接到备用链表中
int initArr(component *);                 //初始化静态链表
void displayArr(component *, int);        //输出函数
int mallocArr(component *);                          //从备用链表上摘下空闲节点的函数



int main()
{
    component array[maxSize];
    int body = initArr(array);   //返回数据链表的表首 1
    printf("静态链表为：\n");
    displayArr(array, body);

    printf("\n----------\n");
    for(int i=0; i<maxSize; i++)
    {
        printf("array[%d]: %d,%d \n", i, array[i].data, array[i].cur);
    }

    return 0;
}


//创建备用链表
void reserveArr(component *array)
{
    for (int i=0; i<maxSize; i++)
    {
        array[i].cur = i+1;      //将每个数组分量链接到一起
    }
    array[maxSize-1].cur = 0;    //链表最后一个结点的游标值为0
}



int mallocArr(component * array) //读出 array[0].cur 的值
{
    //若备用链表非空，则返回分配的结点下标，否则返回 0（当分配最后一个结点时，该结点的游标值为 0）
    int i = array[0].cur;
    if (array[0].cur)
    {
        array[0].cur = array[i].cur;
    }
    return i;
}


//初始化带头节点的静态链表（头节点不存储数据）
int initArr(component *array)
{
    reserveArr(array);
    int body = mallocArr(array);
    //声明一个变量，把它当指针使，指向链表的最后的一个结点，因为链表为空，所以和头结点重合
    int tempBody = body;
    for (int i=1; i<4; i++)
    {
        int j = mallocArr(array);  //从备用链表中拿出空闲的分量
        array[tempBody].cur = j;   //将申请的空闲分量链接在链表的最后一个结点后面
        array[j].data = i;         //给新申请的分量的数据域初始化
        tempBody = j;              //将指向链表最后一个结点的指针后移
    }
    array[tempBody].cur = 0;       //新的链表最后一个结点的指针设置为0
    return body;                   //这个 body 不总是 1 吗？
}



void displayArr(component *array, int body)
{
    printf("*,%d ", array[body].cur);         //打印头节点
    int tempBody = array[body].cur;           //下面从首元节点开始
    while (tempBody)
    {
        printf("%d,%d ", array[tempBody].data, array[tempBody].cur);
        tempBody = array[tempBody].cur;
    }
}



