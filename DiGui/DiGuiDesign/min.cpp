#include <stdio.h>

/*
    使用递归 计算出一个 数组的最小值
    A[i] 为 当前函数 数组下标，m所保存的值为 A[i]前一个元素
*/
double min(float A[],int i){
    double m;
    if(i == 0)
        return A[0];//递归出口 
    else
    {
        m = min(A,i-1);//递归体
        if(m > A[i])
            return A[i];
        else
            return m;
    }
    

}

int main(void){

    float A[] = {1.0,2.0,3.0,4.0};
    float a = min(A,3);
    printf("%f\n",a);
    getchar();
    getchar();
    return 0;
}