#include <stdio.h>
#include <malloc.h>
#define N 5

// ����n�׷���ĺ�  n2
int sum1(int a[][5],int n){
    int i,j,sum=0;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            sum += a[i][j];
        }
    }
    return sum;

}

// ����������λ������С���������ʱ�临�Ӷ�n2
int * sort(int a[],int n){
    int i,j,temp = 0;
    for(i = 0; i < n; i++){
        for(j = i+1; j < n; j++){
            if(a[i] > a[j]){
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    return a;
}

// ����n�������������������Сֵ
int * maxAndMin(int a[],int n){
    int * b = sort(a,n);
    int * c = (int *)malloc(2*sizeof(int));
    c[0] = b[n-1];
    c[1] = b[0];
    return c;
}

// ���� һά���飬 a�����ַ��n���鳤��
void printf_arr(int a[],int n){
    for(int i = 0; i < n; i ++){
        printf("%d\t",a[i]);
    }
}
int main(void){
    // n�׷������
    // int a[N][N] = {{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5}};
    // int sum = sum1(a,5);
    // printf("%d",sum);

// ����������С�������� 
    // int b[] = {3,2,1,7,6};
    // int * b1 = sort(b,5);
    // printf_arr(b1,5);

// �����Сֵ
    int c[] = {1,2,3,56,3};
    int * a = maxAndMin(c,5);
    printf_arr(a,2);
    getchar();
    return 0;
}