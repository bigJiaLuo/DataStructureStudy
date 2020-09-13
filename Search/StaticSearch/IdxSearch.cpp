#include <stdio.h>
#define MAXI 5
typedef int KeyType;//关键字类型
typedef struct IdxSearch
{
    KeyType key;    //关键字
    int link;//指向对应快的起始下标
}IdxType;
typedef struct List
{
    KeyType key;
}List;

typedef int SeqList;//顺序表
typedef IdxType IDX[MAXI];
typedef List SeqList[MAXI];

/*
    I为索引表，b为块数，R为无序顺序表，n为元素个数，key关键字
*/
int IdxSearch(IDX I,int b,SeqList R,int n,KeyType key){
    int low = 0,high = n-1,mid,i;
    int s = n/b;//s为每块元素的个数
    while (low <= high)//在索引表中进行折半查找，找到位置为high+1
    {
        mid = (low+high) / 2;
        if (I[mid].key >= key )
        {
            high = mid-1;
        }
        else
            low = mid+1;        
    }

    //应在索引表的high+1块中，再在对应的线性表中进行顺序查找
    i = I[high+1].link;
    while ((i <= I[high+1].link+s-1) && R[i].key != key)
    {
        i++;
    }
    if (i <= I[high+1].link+s-1)//i还在 high+1 块中，说明找到元素
    {
        return i+1;//返回逻辑序号
    }else
    {
        return 0;//未找到
    }
    
    
    
    
}
int main(void){

    return 0;
}