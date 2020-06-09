#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef struct release
{
    ElemType data;
    struct release * next;
}linkList,* pLinkList;


/*
    初始化一个头指针
*/
void initList(pLinkList *pL)
{
    *pL = (pLinkList)malloc(sizeof(linkList));
    (*pL)->next = NULL;
}
/*
    根据数组，建立 单链表（头插法）
    pL头结点，a 为数组首地址，n为 数组长度
    思路：
        1.创建一个头结点 给 pL，和i =1，
        2.循环 遍历 i<n
        3.循环
            ·生成一个新结点 p
            ·将本次循环的 数组中的值给 p->data[i]
            ·将 p插入到头结点 与上一新节点之间
*/
void createListF(pLinkList *pL, ElemType a[], int n)
{
    initList(&(*pL));
    pLinkList p;
    for (int i = 0; i < n; i++)
    {
        //生成新的结点
        p = (pLinkList)malloc(sizeof(linkList));
        //赋值
        p->data = a[i];
        //插入到上一插入结点之后,包含了NULL，第一个插入的结点，即为尾结点
        p->next = (*pL)->next;
        //插入头结点之后
        (*pL)->next = p;
    }
}

/*
    释放单链表p中的所有节点
    f(p)释放 a1-an，f（p->next）释放a2-an
*/
void release(pLinkList * p){
    if(*p != NULL){//递归出口
        release(&((*p)->next));//递归体
        free(*p);
    }
}

int main(void){
    pLinkList p;
    ElemType a[] = {1,2,3};
    createListF(&p,a,3);
    release(&p);

    getchar();
    getchar();
    return 0;
}
