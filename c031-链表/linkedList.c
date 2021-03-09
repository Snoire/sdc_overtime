//http://data.biancheng.net/view/160.html

#include <stdio.h>
#include <stdlib.h>

typedef struct link{
    char elem;                //代表数据域
    struct link * next;       //代表指针域，指向直接后继元素
}Link;                        //Link为节点名，每个节点都是一个 Link 结构体



//创建一个存储 {1,2,3,4} 且无头节点的链表
Link * initLink()
{
    Link * p = NULL;                              //创建头指针

    Link * temp = (Link*)malloc(sizeof(Link));  //创建首元节点
    temp->elem = 1;
    temp->next = NULL;

    p = temp;                      //头指针指向首元节点

    for (int i=2; i<5; i++)        //从第二个节点开始创建
    {
        Link *a = (Link*)malloc(sizeof(Link));
        a->elem = i;
        a->next = NULL;

        temp->next = a;             //将temp节点与新建立的a节点建立逻辑关系
        temp = temp->next;          //指针temp每次都指向新链表的最后一个节点，其实就是 a节点，这里写temp=a也对
    }

    return p;                     //返回建立的节点，只返回头指针 p即可，通过头指针即可找到整个链表
}



int freeLink(Link * p)                    //释放链表的空间
{
    Link * temp = NULL;
    while(p)                              // p!=NULL
    {
        temp = p;
        p = p->next;
        free(temp);
    }

    return 0;
}



int main()
{
    Link * p = initLink(), * temp;
    temp = p;

    for(int i=0; temp; i++)      //本来是写 temp->next 的
    {
        printf("link[%d].elem = %d\n", i, temp->elem);
        temp = temp->next;
    }

    freeLink(p);
    temp = NULL;
    p = NULL;

    return 0;
}


