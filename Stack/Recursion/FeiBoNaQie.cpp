#include <stdio.h>

void printfFei1(){
    int fei[40];
    int i,j;
    fei[0] = 1;
    fei[1] = 1;
    printf("%d\t",fei[0]);
    printf("%d\t",fei[1]);
    for(i = 2; i < 40; i++){
        fei[i] = fei[i-1] + fei[i-2];
        printf("%d\t",fei[i]);
    }
}

int feb(int i){
    if(i < 2)
        return i == 0 ? 0 : 1;
    return feb(i-1) + feb(i -2);
}
void printfFei2(){
    printf("使用递归输出斐波那契：");
    for(int i = 0; i < 40; i++){
        printf("%d\t",feb(i));
    }

}

int main(void){


    printfFei2();
    
    getchar();
    getchar();
    return 0;
}