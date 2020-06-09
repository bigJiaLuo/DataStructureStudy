/*
    ��ŵ�����⣨Hanoi��
     x y z
    �ݹ�˼�룺  ��n ������ �� x ������ y �Ƶ�z��
        1.�� n-1�����Ӵ� x ������ z �Ƶ� y��
        2.move��n,x,z���� n��Բ�̴� x �Ƶ� z
        3.�� n-1 ������ ��y ������ x �Ƶ� z��
*/
#include <stdio.h>


void Hanoi(int n,char x,char y,char z){
    if(n == 1)
        printf("\t��%d����Ƭ��%c�ƶ���%c",n,x,z);//ֻ��һƬʱ����x�ϵ�һƬ�Ƶ�z��
    else{
        Hanoi(n-1,x,z,y);
        printf("\t����%d����Ƭ��%c�ƶ���%c",n,x,z);
        Hanoi(n-1,y,x,z);
    }
}



int main(void){
    Hanoi(3,'x','y','z');

    getchar();
    getchar();
    return 0;
}