/*
    没有 尾指针的循环链表
    作者：洛
    时间：2020年6月3日08:48:23
    复习：2020年8月25日11:39:09
*/

#include <stdio.h>
#include <malloc.h>
#define MaxSize 10
typedef int ElemType;
typedef struct WithRearQueue
{
    /* data */
    ElemType data[MaxSize];
    int front;//指向队首指针的前一个
    int count;//队列元素的个数
}Queue,* PQueue;

/*
    初始化一个链表
*/
void initQueue(PQueue * q){
    *q = (PQueue)malloc(sizeof(Queue));
    (*q)->front = 0;//指向队首元素的前一个
    (*q)->count = 0;//元素个数为0
}

/*
    入队
    rear 指向队尾元素
*/
bool enQueue(PQueue * q,ElemType e){
//判断队列是否满
    if((*q)->count == MaxSize)
        return false;
    //计算队尾
    int rear = ((*q)->front + (*q)->count) % MaxSize;
    rear = (rear+1) % MaxSize;//rear指针进1
    (*q)->data[rear] = e;
    (*q)->count++;
    return true;
}
/*
    出队
*/
bool delQueue(PQueue * q,ElemType * e){
    //判断 队列是否为空
    if((*q)->count == 0)
        return false;
    (*q)->front = ((*q)->front + 1) % MaxSize;//队首指针进1
    *e = (*q)->data[(*q)->front];
    (*q)->count--;//队列元素个数减一
    return true;
}
void displayQueue(PQueue q){
    int front = q->front;
    for(int i = 0; i < q->count; i++){
        front = (front+1) % MaxSize;
        printf("%d\t",q->data[front]);
    }
}
int main(void){
    PQueue q;
    initQueue(&q);
    for (int i = 0; i < 10; i++)
    {
        /* code */
        enQueue(&q,i);
    }
    displayQueue(q);
    getchar();
    getchar();

    return 0;
}

