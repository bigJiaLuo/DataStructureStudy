/*
    作者：洛
    时间：2020年6月3日19:26:59
    只包含尾指针的循环队列
*/

#include <stdio.h>
#include <malloc.h>

typedef int ElemType;
//数据结点类型,也可作为 队尾结点
typedef struct LinkNode
{
    ElemType data; //数据域
    struct LinkNode *next;
} LinkNode, *PLinkNode;

/*
    初始化一个队列
*/
void initQueue(PLinkNode * rear)
{
    *rear = (PLinkNode)malloc(sizeof(LinkNode));
    (*rear)->next = NULL; //rear为空，代表队列为空
}

/*
    入队
    思路：
        1.创建新节点
        2.判断是否队列是否为空队列
            ·空，则单独是新结点构成循环链表
            ·将新结点 加入到 尾结点之后，且构成循环链表
*/
void enQueue(PLinkNode *rear, ElemType e)
{
    //1.创建新节点
    PLinkNode p = (PLinkNode)malloc(sizeof(LinkNode));
    p->data = e;
    //2.判断队列是否为空队列
    if ((*rear)->next == NULL)
    {
        (*rear) = p; //尾指针指向尾结点
        p->next = *rear;    //尾结点指向其自身构成循环链表
    }
    else
    {
        p->next = (*rear)->next; //新结点指向其 队首
        (*rear)->next = p;       //将p 构建成新的尾结点
        (*rear) = p;             //(*rear)指向尾结点
    }
}

/*
    出队
    思路：
        1.判断队列是否为空
        2.判断队列是否只有一个数据结点
            释放其rear，rear置为空
        3.将尾结点 的next 指向 首节点的下一个
            释放首节点
*/
bool deQueue(PLinkNode * rear,ElemType * e){
    //1.
    if((*rear)->next == NULL)
        return false;
    //2,
    if((*rear)->next == (*rear)){
        *e = (*rear)->data;
        free(*rear);
        (*rear) = NULL;
    }else
    {
        //二个以上的结点
        *e = (*rear)->next->data;
        LinkNode * p = (*rear)->next;//首节点
        (*rear)->next = p->next;//指向新的首节点
        free(p);
        p = NULL;
    }
    return true;
}

void displayQueue(PLinkNode rear){
    if(rear->next == NULL)
        return;
    PLinkNode p = rear->next;//队首指针
    while (p != rear)
    {
        printf("%d\t",p->data);
        p = p->next;
    }
    printf("%d\n",p->data);//打印最后的队尾指针
    
}
int main(void)
{

    PLinkNode rear;
    initQueue(&rear);
    for(int i = 0; i < 10; i++){
        enQueue(&rear,i);
    }
    displayQueue(rear);

    getchar();
    getchar();
    return 0;
}