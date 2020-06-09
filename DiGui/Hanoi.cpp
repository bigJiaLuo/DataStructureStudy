/*
    汉诺塔问题（Hanoi）
     x y z
    递归思想：  将n 个盘子 从 x 借助于 y 移到z上
        1.将 n-1个盘子从 x 借助于 z 移到 y上
        2.move（n,x,z）将 n个圆盘从 x 移到 z
        3.将 n-1 个盘子 从y 借助于 x 移到 z上
*/
#include <stdio.h>


void Hanoi(int n,char x,char y,char z){
    if(n == 1)
        printf("\t将%d个盘片从%c移动到%c",n,x,z);//只有一片时，将x上的一片移到z上
    else{
        Hanoi(n-1,x,z,y);
        printf("\t将第%d个盘片从%c移动到%c",n,x,z);
        Hanoi(n-1,y,x,z);
    }
}



int main(void){
    Hanoi(3,'x','y','z');

    getchar();
    getchar();
    return 0;
}