/*
    递归计算Fibonacci 数列
*/
#include <stdio.h>

/*
    计算 Fibonacci 第n项的值
    1 1 2 3 5 8 13...
*/
int Fib(int n){
    if(n == 1 || n == 2){
        return 1;
    }else
    {   //第n项的值等于 （n-1）   +   （n-2）
        int a = Fib(n-1) + Fib(n-2);
        return a;
    }
    
}

int main(void){

    int a = Fib(7);
    printf("%d\n",a);
    getchar();
    getchar();
    return 0;
}