#include <stdio.h>
#include <malloc.h>
#define MaxSize 20 //存储空间初始分配量
// 定义 状态代码
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int Status;   // 函数的类型，值为 函数结果状态代码，如：OK
typedef int ElemType; // 默认的元素类型 int ，别名ElemTyp

typedef struct List
{
    /* data */
    ElemType *data; //包含 默认大小的 ElemType类型数组
    int length;     // 线性表长度
} SqList;

/*
    初始化线性表
    思路：
        重新分配一段空间，并设长度为0
*/
Status initList(SqList *pL)
{
    pL->data = (ElemType *)malloc(MaxSize * sizeof(ElemType));
    if (!pL->data)
        return ERROR;
    (pL)->length = 0;
    return OK;
}
/*
    创建顺序线性表
    思路：
        1.遍历数组a
        2.逐一进行赋值
    pL线性表的指针，a为 创建线性表提供的数组，n为 数组长度
*/
Status createList(SqList *pL, ElemType a[], int n)
{
    if (!pL || !a)
    {
        return ERROR;
    }
    initList(pL);
    for (int i = 0; i < n; i++)
    {
        pL->data[i] = a[i];
        pL->length++;
    }
    return OK;
}

/*
    递归 求解线性表中的最大值
    思路：
        1.将L分解成两个子表，分别求出子表中的最大值ai 和aj，再比较 ai 和aj 得出最大值
        2.对于子表如何求最大值，采用相同的方法，将两个子表也各自分化为对应两个子表，得出对应最大值
        3.不断分解，直到表中的元素为一个为止，（表中只有一个值，它就是最大值）
*/
int Max(SqList L,int i,int j){
    int mid;
    int max,max1,max2;
    if(i == j)//说明表中只有data[i]这一个元素
        max = L.data[i];//递归出口
    else//递归体
    {
        mid = (i+j)/2;
        max1 = Max(L,i,mid);
        max2 = Max(L,mid+1,j);
        max = (max1 > max2) ? max1 : max2;
    }

    return max;
}

int main(void){
    
    SqList L;
    int l[] = {1,2,3,4};
    createList(&L,l,4);
    int max = Max(L,0,3);
    printf("%d",max);
    getchar();
    getchar();
    return 0;
}