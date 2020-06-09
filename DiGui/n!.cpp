#include <stdio.h>

/*
    求n的阶乘
*/
int fun(int n){
    if(n == 1)//递归结束条件
        return 1;
    else
    {
        int a = fun(n-1)*n;//n的规模不断缩小
        return a;
    }

}


int main(void){
    int n = fun(4);
    printf("%d\n",n);

    getchar();
    getchar();
    return 0;
}