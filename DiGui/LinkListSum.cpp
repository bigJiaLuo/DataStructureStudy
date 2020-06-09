#include <stdio.h>
#include <malloc.h>

typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode * next;
}linkList,* pLinkList;

void initList(pLinkList * p){
    *p = (pLinkList)malloc(sizeof(linkList));
    (*p)->next = NULL;
    (*p)->data = 0;
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
    求一个单链表所有data域的和
*/
ElemType Sum(pLinkList p){
    if(p == NULL) 
        return 0;
    else{
        int  n = p->data + Sum(p->next);
        return n;
    }
}

int main(void){
    pLinkList p;
    int a[] = {1,2,3,4,5};
    createListF(&p,a,5);

    ElemType n = Sum(p);
    printf("%d\n",n);
    getchar();
    getchar();

    return 0;
}