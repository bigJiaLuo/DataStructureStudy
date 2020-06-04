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

/*
    将字符串 t 复制给 s
    思路：
        1.遍历 串t
        2.赋值操作
*/
void StrCopy(SqString * s,SqString t){
    int i;
    for(i = 0; i < t.length; i++){
        s->data[i] = t.data[i];
    }
    s->length = t.length;
}

/*
    判断两个串是否相等
*/
bool StrEqual(SqString s,SqString t){
    if(s.length != t.length)
        return false;//长度不相等，false
    for(int i = 0; i < t.length; i++){
        if(s.data[i] != t.data[i])
            return false;//相同位置上，字符不相等
    }
    return true;
}

/*
    求字符串长度
*/
int StrLength(SqString s){
    return s.length;
}

/*
    串连接：有两个子串s，t连接一起形成的串
    思路：
        1.遍历 子串s
        2.遍历 子串t
        ·注意累加长度
*/
SqString Concat(SqString s,SqString t){
    SqString str;
    int i;
    str.length = s.length+t.length;//长度累加
    for (int i = 0; i < s.length; i++)
    {
        str.data[i] = s.data[i];
    }
    for(int i = 0; i < t.length; i++){
        str.data[s.length+i] = t.data[i];
    }

    return str;
}

/*
     取子串：返回串s中从 第i个字符开始的，由连续j个字符组成的子串。参数不正确返回一个空串
     返回：
        截取后的子串
*/
SqString SubStr(SqString s,int i,int j){
    
    SqString str;
    int k;
    str.length = 0;
    if(i <= 0 || i > s.length || j < 0 || i+j-1 > s.length)
        return str;//参数错误,返回空串
    for(k = i-1; k < s.length; k++){
        str.data[k-i+1] = s.data[k];//将子串赋值给str
    }
    str.length = j;//连续j个字符，就是子串的长度
    return str;

}

/*
    将串2 插入到 串1 的第i个字符中，即 将s2的第一个字符作为s1的第i个字符，并返回产生的新串。
        参数不正确是返回一个空串
*/
SqString InsStr(SqString s1,int i,SqString s2){
    SqString str;
    str.length = 0;
    int j;
    if(i <= 0 || i > s1.length+1)
        return str;//参不正确
    for ( j = 0; j < i-1; j++)//将 s1.data[0..i-2]赋值到str
    {
        //j-1为s2子串插入的位置，将其之前的字符先移向新串str
        str.data[j] = s1.data[j];
    }
    for ( j = 0; j < s2.length; j++)//将 s2.data[0..length-1]赋值到str
    {
        str.data[i+j-1] = s2.data[j];//i+j-1  为插入的物理位置
    }
    for(j = i-1; j < s1.length; j++){//将 s1.data[i-1 .. length-1]赋值到str
        str.data[s2.length+j] = s1.data[j];//s2.length+i-1  两次循环之后，应插入的位置
    }

    return str;
}

/*
    从串中删去 第i个字符开始的长度为j子串，并返回产生的新串
        参数不好正确，返回空串
*/
SqString DelStr(SqString s,int i,int j){
    SqString str;
    str.length = 0;
    if (i <= 0 || i > s.length || i+j > s.length+1)//i+j > s.length+1 不懂
    {
        return str;
    }
    int k;
    for(k = 0; k < i-1; k++){
        str.data[k] = s.data[k];//将 s.data[0..i-2]赋值到str
    }
    for(k = i+j-1; k < s.length; k++)
        str.data[k-j] = s.data[k];//将 s.data[i+j-1 ..s.length-1]赋值到str
    str.length = s.length-j;
    
    return str;

}

/*
    在串s中，将 第i个字符开始的j个字符构成的子串 用串t 替换，并返回新产生的串。
    参数不正确时，返回一个空串
*/
SqString RepStr(SqString s,int i,int j,SqString t){
    SqString str;
    str.length = 0;
    if(i <= 0 || i > s.length || j < 0 || i+j-1 > s.length)
        return str;
    for (int k = 0; k < k-1; k++)
    {
        str.data[k] = s.data[k];//将 s.data[0.. k-2]赋值到str
    }
    for (int k = 0; k < t.length; k++)
    {
        str.data[i+k-1] = t.data[k];//将 t.data[0..t.length-1]
    }
    for (int k = i+j-1; k < s.length; k++)
    {
        str.data[t.length+k-1] = s.data[k];
    }
    str.length = s.length - j + t.length;
    
    return str;
}

/*
    输出一个字符串
*/
void DispStr(SqString s){
    int i;
    for(i = 0; i < s.length; i++){
        printf("%c",s.data[i]);
    }
    printf("\n");
}
int main(void){
    SqString s;


    getchar();
    getchar();
    return 0;
}