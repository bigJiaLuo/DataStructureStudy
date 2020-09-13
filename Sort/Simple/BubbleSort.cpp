/* 
    冒泡排序
    1.在一组无序序列中，从最后面挑选两个元素，分别记录其下标。
    2.然后通过比较两者的大小，将较小的值往前移后，将其下标分别前移。
    3.循环 元素个数-1次
    时间复杂度 O(n^2)
 */
#include <stdio.h>
#include <malloc.h>
#define Max 10
#define NON -9999
typedef struct SQList
{
    int arr[Max];//顺序表数据域,arr[0]存放哨兵或其他
    int length;//为顺序表中实际元素个数
}SQList,*PSQList;

/* 
    交换两元素
 */
void swap(int * arr,int i,int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

/* 
    简易版冒泡排序（实则为最简单的选择排序）
 */
void BubbleSort1(SQList * list){
    for (int i = 1; i < list->length; i++)
    {
        for (int j = i+1; j <= list->length; j++)
        {
            if(list->arr[i] > list->arr[j])
                swap(list->arr,i,j);

        }
    }
    printf("");
}

/* 
    正宗的冒泡排序
 */
void BubbleSort2(SQList * list){
    for (int i = 1; i < list->length; i++)
    {
        for (int j = list->length-1; j >= i; j--)
        {
            if(list->arr[j] > list->arr[j+1])//前面的大于后面的，将后面的元素先前冒
                swap(list->arr,j,j+1);
        }
    }
    printf("");
}

/* 
    正宗冒泡排序，优化版
    已知，冒泡排序如果之后的循环不发生交换操作，说明从底部到截止点都是有序的，不必重复循环
 */
void BubbleSort3(SQList * list){
    int flag = 1;//允许进入第一个循环
    for (int i = 1; i < list->length && flag; i++)//若i已到界点或未发生交换flag = 0,退出
    {
        flag = 0;//在未开始判断前先置为假
        for(int j = list->length-1;j >= i; j--){
            if(list->arr[j] > list->arr[j+1]){
                swap(list->arr,j,j+1);
                flag = 1;//已发生交换
            }
        }
    }
    printf("");
}

int main(void){
    PSQList list;
    int arr[] = {NON,2,1,3,4,5,6,0,7,8};
    for (int i = 0; i < Max; i++)
    {
        list->arr[i] = arr[i];
    }
    list->length = Max-1;
    BubbleSort3(list);
    // BubbleSort2(list);
    // BubbleSort1(list);
    for ( int i = 0; i < Max; i++)
    {
        printf("%d\t",list->arr[i]);
    }
    
    
    getchar();
    getchar();
    return 0;
}