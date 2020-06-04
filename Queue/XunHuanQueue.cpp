/*
    循环队列
    
*/

#include <stdio.h>
#include <malloc.h>

#define MaxSize 10
typedef int ElemType;
typedef struct XunHuanQueue
{
    ElemType data[MaxSize];
    int front;//队首指针，指向队首的前一个元素
    int rear;//队尾指针指向当前队尾元素
}XunHuanQueue,* PXunHuanQueue;

/*
    初始化循环队列
*/
void initQueue(PXunHuanQueue * q){
    *q = (PXunHuanQueue)malloc(sizeof(XunHuanQueue));
    (*q)->rear = -1;
    (*q)->front = -1;
    //队为空条件 rear == front
}
/*
    判断队列是否为空
    返回:  
        true 空，反之
*/
bool isEmpty(PXunHuanQueue q){
    if(q->front == q->rear)
        return true;
    return false;
}

/*
    判断队列是否满
*/
bool isFull(PXunHuanQueue q){
    if((q->rear +1) % MaxSize == q->front)
        return true;
    return false;
}

/*
    销毁队列
*/
void destroryQueue(PXunHuanQueue * q){
    free(*q);
    *q = NULL;
}

/*
    将元素e，队尾入队
    返回：
        true：成功，反之
*/
bool enQueue(PXunHuanQueue * q,ElemType e){
    if(isFull(*q))
        return false;
        //入队,队尾指针进1
    (*q)->rear = ((*q)->rear + 1) % MaxSize;
    (*q)->data[(*q)->rear] = e;

    return true;

}

/*
    队首出队列
*/
bool delQueue(PXunHuanQueue * q,ElemType * e){
    if(isEmpty(*q))
        return false;
        //一开始front指向队首的前一个位置，指针后移一位，指向队首
    (*q)->front = ((*q)->front + 1) % MaxSize;
    *e = (*q)->data[(*q)->front];
    return true;
}

void displayQueue(PXunHuanQueue q){
    int front = q->front,rear = q->rear;
    printf("循环队列遍历：\n");
    while (front != rear)
    {
        printf("%d\t",q->data[front+1]);
        front = (front +1) % MaxSize;
    }
    
}



int main(void){
    PXunHuanQueue q;
    initQueue(&q);
    ElemType e;
    for(int i = 0; i <10; i++ ){
        enQueue(&q,i);
    }
    for(int i = 0; i < 9; i++){
        delQueue(&q,&e);
    }
    displayQueue(q);
    
    getchar();
    getchar();
    return 0;
}



