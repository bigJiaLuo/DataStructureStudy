/*
    解决报数问题
        有一排人，开始报数 1,2，1,2.其中报1的人往前站队，报2的人站队伍的后面
        输出其最后报数顺序
        例：12345678
            13572468

    作者：洛
    时间：2020年6月4日09:48:38
*/

#include <stdio.h>
#include <malloc.h>
#define MaxSize 9

typedef int ElemType;
typedef struct SqQueue{
    ElemType data[MaxSize];
    int front;//队首的前一指针
    int rear;//队尾指针
}SqQueue,* PSqQueue;

/*
    输出最后报数 序列
    n：总人数
        思路：
            1.初始化一个循环队列
            2.遍历 队列
                ·输出奇数队首
                ·判断队列是否为空
                    ·不空，则队首指针后移，将偶数队首加入到队首。
*/
void number(int n){
    PSqQueue q;
    q = (PSqQueue)malloc(sizeof(SqQueue));
    q->front = q->rear = 0;//队首，队尾为0，空队列

    //初始化队列
    for(int i = 0; i < n; i++){
        //尾指针移向
        q->rear = (q->rear + 1) % MaxSize;
        q->data[q->rear] = i+1;
    }

    printf("报数出列顺序：\n");
    while (q->rear != q->front)
    {
        q->front = (q->front + 1) % MaxSize;//指向队首指针
        //输出奇数序号
        printf("%d\t",q->data[q->front]);
        //若队列不空
        if (q->front != q->rear)
        {
            //将 偶数的序号加入到队尾
            q->front = (q->front+1) % MaxSize;//移向偶数队首
            q->rear = (q->rear+1) % MaxSize;//指向新的队尾
            q->data[q->rear] = q->data[q->front];//将序号加入队尾
        }
        
    }
    printf("\n");
    
}
int main(void){

    printf("初始序号：\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%d\t",i+1);
    }
    printf("\n");

    number(8);
    getchar();
    getchar();
    return 0;
}