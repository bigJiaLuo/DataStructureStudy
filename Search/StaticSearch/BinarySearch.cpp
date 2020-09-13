/*
    折半查找
*/
#include <stdio.h>

/*
    s为有序表，n为元素个数，0角标不存放元素，key为需要查找的关键字
*/
int BinarySearch(int * s,int n,int key){
    int low,high,mid;
    low = 1;
    high = n;

    while (low <= high)
    {
        mid = (low+high)/2; //查找范围折半
        if (s[mid] < key)
        {
            low = mid+1;//从中间值的右边一位继续查找
        }
        else if (s[mid] > key)
        {
            high = mid-1;//从中间值的左边一位继续查找
        }
        else
            return mid;//已找到key
    }

    return 0;//未找到对应key
    
}

/*
    插值查找   核心算法low + (high-low) * (key-s[low])/(s[high]-s[low])
    s为有序表，n为元素个数，0角标不存放元素，key为需要查找的关键字
*/
int InterpolationRearch(int * s,int n,int key){
    int low,high,mid;
    low = 1;
    high = n;

    while (low <= high)
    {
        mid = low + (high-low) * (key-s[low])/(s[high]-s[low]);//插值
        if (s[mid] < key)
        {
            low = mid+1;//从中间值的右边一位继续查找
        }
        else if (s[mid] > key)
        {
            high = mid-1;//从中间值的左边一位继续查找
        }
        else
            return mid;//已找到key
    }

    return 0;//未找到对应key

}


/* 
    计算使用折半查找关键字 key 所需要比较的次数
 */
int BinSearch1(int arr[],int n,int key){
    int low = 0,high = n-1,mid;
    int count = 1;//最开始与根节点比较，初始化唯一
    while (low <= high)
    {
        mid = (low+high) / 2;
        if(arr[mid] == key)
            return count;
        else if (arr[mid] < key)
        {
            low = mid+1;
        }else
        {
            high = low - 1;
        }
        count++;//进行一次比较自增
    }
    //查找失败的次数，因为count-1
    return count -1;
}


int main(void){
    int s[] = {0,1,2,3,4};
    // int v = BinarySearch(s,5,3);
    // int v = InterpolationRearch(s,5,3);
    int v = BinSearch1(s,5,3);
    printf("%d",v);

    getchar();
    getchar();
    return 0;
}