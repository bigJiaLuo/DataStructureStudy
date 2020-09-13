#include <stdio.h>

/*
    s查找集合，0角标不存放元素，n为元素个数，key为查找关键字
    找到了：返回关键字下标，否则 返回 0
*/
int SequentialSearch_1(int s[],int n,int key){
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == key)
        {
            return i;
        }
    }
    return 0;
}

/*
    SequentialSearch_1存在需要对s[]角标是否越界进行重复性判断，此算法添加哨兵用以优化算法
    s查找集合，0角标不存放元素，n为元素个数，key为查找关键字
    找到了：返回关键字下标，否则 返回 0
*/
int SequtialSearch_2(int s[],int n,int key){
    s[0] = key;//下标0 设为哨兵
    while (s[n] != key)//判断是否相等
    {
        n--;
    }
    //while循环找到key则n为key在s中的下标，否则，等于哨兵，下标为0
    return n;
}

int main(void){
    int a[] = {0,2,3,4};
    int b = SequtialSearch_2(a,4,3);
    return 0;
}
