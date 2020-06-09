#include <stdio.h>
#include <malloc.h>
#define MaxSize 20
typedef struct SqString
{
    char data[MaxSize]; //串的数据
    int length;         //串的长度
} SqString, *PSqString;

void InitString(SqString *s, char str[])
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        s->data[i] = str[i];
    }
    s->length = i;
}
/*
    将字符串 t 复制给 s
    思路：
        1.遍历 串t
        2.赋值操作
*/
void StrCopy(SqString *s, SqString t)
{
    int i;
    for (i = 0; i < t.length; i++)
    {
        s->data[i] = t.data[i];
    }
    s->length = t.length;
}
/*
     取子串：返回串s中从 第i个字符开始的，由连续j个字符组成的子串。参数不正确返回一个空串
     返回：
        截取后的子串
*/
SqString SubStr(SqString s, int i, int j)
{

    SqString str;
    int k;
    str.length = 0;
    if (i <= 0 || i > s.length || j < 0 || i + j - 1 > s.length)
        return str; //参数错误,返回空串
    for (k = i - 1; k < s.length; k++)
    {
        str.data[k - i + 1] = s.data[k]; //将子串赋值给str
    }
    str.length = j; //连续j个字符，就是子串的长度
    return str;
}

/*
    求字符串长度
*/
int StrLength(SqString s)
{
    return s.length;
}

/*
    串连接：有两个子串s，t连接一起形成的串
    思路：
        1.遍历 子串s
        2.遍历 子串t
        ·注意累加长度
*/
SqString Concat(SqString s, SqString t)
{
    SqString str;
    int i;
    str.length = s.length + t.length; //长度累加
    for (int i = 0; i < s.length; i++)
    {
        str.data[i] = s.data[i];
    }
    for (int i = 0; i < t.length; i++)
    {
        str.data[s.length + i] = t.data[i];
    }

    return str;
}

/*
    输出一个字符串
*/
void DispStr(SqString s)
{
    int i;
    for (i = 0; i < s.length; i++)
    {
        printf("%c", s.data[i]);
    }
    printf("\n");
}


// SqString invert(SqString * s){
//     SqString string = *s;
//     SqString s1,s2;
//     if(StrLength(string) > 0){
//         SqString s3 = SubStr(string,2,StrLength(string)-1);
//         s1 = invert(&s3);
//         s2 = Concat(s1,SubStr(string,1,1));
//     }else
//     {
//         StrCopy(&s2,string);
//     }
    
//     return s2;
    
// }
int main(void){
    SqString s;    
    char a[] = {'1','2','3','4','\0'};
    InitString(&s,a);
    // invert(&s);
    DispStr(s);
    getchar();
    getchar();
    return 0;
}