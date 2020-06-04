/*
    顺序串
    作者：洛
    时间：2020年6月4日15:01:27
*/

#include <stdio.h>
#include <malloc.h>
#define MaxSize 10
typedef struct SqString
{
    char data[MaxSize];//串的数据
    int length;//串的长度
}SqString,* PSqString;

/*
    将一个字符串常量赋给串s
    s：用于存储 cstr中的字符串常量
*/
void StrAssign(SqString * s,char cstr[]){
    int i;
    for(i = 0; cstr[i] != '\0'; i++){
        s->data[i] = cstr[i];
    }
    s->length = i;//i最后就为 字符串的长度
}

void StrCopy(SqString * s,SqString t){}

int main(void){
    

    getchar();
    getchar();
    return 0;
}