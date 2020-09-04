/*
    作者：洛
    时间：2020年6月2日15:17:26
    复习：2020年8月25日11:19:48
*/

#include <stdio.h>
#include <malloc.h>
#define MaxSize 10
typedef int ElemType;
typedef struct 
{
    ElemType data[MaxSize];//存放队列的数据
    int front;//指向队头的前一位置
    int rear;//指向队尾元素
}Queue,* PQueue;

/*
    初始化 一个空队列
    q ： 队列
*/
void initQueue(PQueue * q){
    *q = (PQueue)malloc(sizeof(Queue));
    (*q)->front = -1;
    (*q)->rear = -1;
    //front == rear时，队列为空
}

/*
    销毁一个队列
    q为队列指针
*/
void destroryQueue(PQueue * q){
    //传入 queue的 地址
    free(&(*q));
    *q = NULL;
}

/*
    判断队列是否为空，
    返回：
        true 空，反之
    
*/
bool isEmpty(PQueue q){
    if(q->front == q->rear)
        return true;
    return false;
}
/*
    判断队列是否已经满了
    返回：
        true 满了，反之
*/
bool isFull(PQueue q){
    if(q->rear == MaxSize-1)
        return true;
    return false;
}
/*
    将 e元素 入队
    q：队列，e：待入队的元素
*/
bool enQueue(PQueue * q,ElemType e){
    //判断队列是否满了
    if(isFull(*q))
        return false;
    //rear自增，入队
    (*q)->data[++(*q)->rear] = e;
    return true;
}

/*
    删除队头，出队
    返回：
        true，删除成功，反之
*/
bool delQueue(PQueue * q,ElemType * e){
    //判断队列是否为空
    if(isEmpty(*q))
        return false;
    *e = (*q)->data[++(*q)->front];//队列front 加1

    return true;
}

/*
    遍历整个队列
*/
void displayQueue(PQueue q){
    int q1 = q->front,r1 = q->rear;
    while(q1 < r1){
        printf("%d\t",q->data[q1+1]);
        q1++;
    }
}

int main(void){

    PQueue queue;
    ElemType e = 10;
    initQueue(&queue);
    for(int i = 0; i < 20; i++){
        enQueue(&queue,e);
    }
    displayQueue(queue);
    // for(int i = 0; i < 20; i++){
    //     delQueue(&queue,&e);
    // }
    displayQueue(queue);

    getchar();
    getchar();
    return 0;
}