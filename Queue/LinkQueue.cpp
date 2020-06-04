/*
    链式队列
    作者：洛
    时间：2020年6月3日09:45:22
*/
#include <stdio.h>
#include <malloc.h>
typedef int ElemType;

//数据结点
typedef struct LinkQueue
{
    /* data */
    ElemType data;//数据域
    struct LinkQueue * next;//下一元素指针
}LinkQueue,* PLinkQueue;

//头结点
typedef struct HeadQueue{
    LinkQueue * front;//指向队首指针
    LinkQueue * rear;//尾指针
}HeadQueue,* PHeadQueue;

/*
    初始化队列
*/
void initQueue(PHeadQueue * q){
    *q = (PHeadQueue)malloc(sizeof(HeadQueue));
    (*q)->front = (*q)->rear = NULL;//初始化时，队首，队尾指针都为NULL
}

/*
    销毁一个队列
*/
void destroryQueue(PHeadQueue * q){
    PLinkQueue front = (*q)->front,r;//fonrt队首指针,r指向下一个
    if(front != NULL){//释放数据结点
        r = front->next;
        while (r!=NULL)
        {
            /* code */
            free(front);
            front = r;//front，r都指向下一个
            r = front->next;
        }
        
    }
    free(front);
    free(*q);
}

/*
    判断队列是否为空
*/
bool isEmpty(PHeadQueue q){
    if(q->rear == NULL)
        return true;
    return false;
}
/*
    入队
    思路：
        1.创建新节点
        2.队尾指针连接新节点
            ·新结点是否作为头数据结点，front，rear同时连接
*/
bool enQueue(PHeadQueue q,ElemType e){
    //1.创建结点
    PLinkQueue s = (PLinkQueue)malloc(sizeof(LinkQueue));
    s->data = e;
    s->next = NULL;
    //2.连接新节点
    if(q->rear == NULL){
        //头数据结点
        q->rear = q->front  = s;
    }else{
        //非头点
        q->rear->next = s;
        q->rear = s;
    }

}

/*
    出队
    思路：
        1.头结点连接 队首的下一个结点
*/
bool deQueue(PHeadQueue q,ElemType * e){
    if(isEmpty(q))
        return false;
    PLinkQueue p = q->front;
    if(q->front == q->rear)
        q->front = q->rear = NULL;//队列中只剩一个元素
    else
        q->front = p->next;//队首指针指向下一个
    *e = p->data;
    
    free(p);
    return true;

}


int main(void){

    return 0;
}

