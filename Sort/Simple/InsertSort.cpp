/* 
    直接插入排序
    思想：
        1.
    作者：泽兑ing
    时间：2020年9月14日11:23:26
 */
#include <stdio.h>
#include <malloc.h>
#define Max 10
#define NON -9999
typedef int KeyNode;

typedef struct SQList
{
    KeyNode arr[Max];//顺序表数据域,arr[0]存放哨兵或其他
    int length;//为顺序表中实际元素个数
}SQList,*PSQList;

void InsertSort(SQList * list){
    int i,j;//
    KeyNode temp;
    //遍历长度减一次
    for(i = 2; i < list->length; i++){
        temp = list->arr[i];//将需要插入的元素，赋给temp
        j = i-1;//从右边向左边进行遍历，寻找arr[i]在有序区R[0..i-1]的插入位置
        while (j >= 1 && list->arr[i] < list->arr[j])
        {
            //插入元素小于沿途元素，将沿途元素逐一向后让一位
            list->arr[j+1] = list->arr[j];
            j--;
        }
        //找到位置
        list->arr[j+1] = temp;
    }
}


int main(void){
    PSQList list;
    int arr[] = {NON,2,1,3,4,5,6,0,7,8};
    for (int i = 0; i < Max; i++)
    {
        list->arr[i] = arr[i];
    }
    list->length = Max-1;
    InsertSort(list);

    for(int i = 1; i <= list->length; i++){
        printf("%d\t",list->arr[i]);
    }
    
    getchar();
    getchar();
    return 0;
}