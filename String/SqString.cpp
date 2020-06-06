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
    将一个字符串常量赋给串s
    s：用于存储 cstr中的字符串常量
*/
void StrAssign(SqString *s, char cstr[])
{
    int i;
    for (i = 0; cstr[i] != '\0'; i++)
    {
        s->data[i] = cstr[i];
    }
    s->length = i; //i最后就为 字符串的长度
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
    判断两个串是否相等
*/
bool StrEqual(SqString s, SqString t)
{
    if (s.length != t.length)
        return false; //长度不相等，false
    for (int i = 0; i < t.length; i++)
    {
        if (s.data[i] != t.data[i])
            return false; //相同位置上，字符不相等
    }
    return true;
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
    将串2 插入到 串1 的第i个字符中，即 将s2的第一个字符作为s1的第i个字符，并返回产生的新串。
        参数不正确是返回一个空串
*/
SqString InsStr(SqString s1, int i, SqString s2)
{
    SqString str;
    str.length = 0;
    int j;
    if (i <= 0 || i > s1.length + 1)
        return str;             //参不正确
    for (j = 0; j < i - 1; j++) //将 s1.data[0..i-2]赋值到str
    {
        //j-1为s2子串插入的位置，将其之前的字符先移向新串str
        str.data[j] = s1.data[j];
    }
    for (j = 0; j < s2.length; j++) //将 s2.data[0..length-1]赋值到str
    {
        str.data[i + j - 1] = s2.data[j]; //i+j-1  为插入的物理位置
    }
    for (j = i - 1; j < s1.length; j++)
    {                                         //将 s1.data[i-1 .. length-1]赋值到str
        str.data[s2.length + j] = s1.data[j]; //s2.length+i-1  两次循环之后，应插入的位置
    }

    return str;
}

/*
    从串中删去 第i个字符开始的长度为j子串，并返回产生的新串
        参数不好正确，返回空串
*/
SqString DelStr(SqString s, int i, int j)
{
    SqString str;
    str.length = 0;
    if (i <= 0 || i > s.length || i + j > s.length + 1) //i+j > s.length+1 不懂
    {
        return str;
    }
    int k;
    for (k = 0; k < i - 1; k++)
    {
        str.data[k] = s.data[k]; //将 s.data[0..i-2]赋值到str
    }
    for (k = i + j - 1; k < s.length; k++)
        str.data[k - j] = s.data[k]; //将 s.data[i+j-1 ..s.length-1]赋值到str
    str.length = s.length - j;

    return str;
}

/*
    在串s中，将 第i个字符开始的j个字符构成的子串 用串t 替换，并返回新产生的串。
    参数不正确时，返回一个空串
*/
SqString RepStr(SqString s, int i, int j, SqString t)
{
    SqString str;
    str.length = 0;
    if (i <= 0 || i > s.length || j < 0 || i + j - 1 > s.length)
        return str;
    for (int k = 0; k < k - 1; k++)
    {
        str.data[k] = s.data[k]; //将 s.data[0.. k-2]赋值到str
    }
    for (int k = 0; k < t.length; k++)
    {
        str.data[i + k - 1] = t.data[k]; //将 t.data[0..t.length-1]
    }
    for (int k = i + j - 1; k < s.length; k++)
    {
        str.data[t.length + k - 1] = s.data[k];
    }
    str.length = s.length - j + t.length;

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

//应用
/*
    Brute-Force--简单匹配算法
    思路：
        从目标串 s开始的第一个字符，和模式串t中的第一个字符比较，若相等，则继续逐个比较后续字符；否则从目标串s的第二个字符开始重新与模式串t
        中的第一个字符比较。
        依次类推，若从模式串s的第i个字符开始，每个字符依旧和目标串t中的对应字符相等，则匹配成功 i，否则匹配失败 -1
*/

int index(SqString s, SqString t)
{
    int i = 0, j = 0;
    while (i < s.length && j < t.length)
    {
        if (s.data[i] == t.data[j])
        {        //继续匹配下一个字符
            i++; //主串和子串依次匹配下一个字符
            j++;
        }
        else
        {                  //主串，子串指针回溯重新开始下一次匹配
            i = i - j + 1; //主串从下一位置开始匹配
            j = 0;
        }
    }

    if (j >= t.length)
        return (i - t.length); //返回匹配的第一个字符的下标
    else
        return -1; //模式匹配不成功
}

/*
    KMP算法：
        思路：
            1.设s为目标串，t为模式串，并设i指针和j指针分别指示目标串和模式串中正待比较的字符，令i和j初值为0
            2.若有si = tj，则i和j分别增1
                ·否则，i不变，j退回到j = next[j]的位置（模式歘右化）
                ·重复该步骤，直到出现下列两种情况之一
                    ·j退回到某个j = next[j]位置是由 si = tj，则指针个增1后继续匹配
                    ·j退回到j = -1，此时令i，j指针各增1，从si+1 和t0开始继续匹配
*/
void GetNext(SqString t,int next[]){
    int j,k;
    j = 0;
    k = -1;
    next[0] = -1;
    while(j < t.length){
        if(k == -1 || t.data[j] == t.data[k]){//k为-1 或比较字符串相等时
            j++;
            k++;
            next[j] = k;
        }else
        {
            k = next[k];
        }
        
    }
}

int KMPIndex(SqString s,SqString t){
    int next[MaxSize],i = 0,j = 0;
    GetNext(t,next);
    while(i < s.length && j < t.length){
        if(j == -1 || s.data[i] == t.data[j]){
            i++;
            j++;
        }else
        {
            j = next[j];//i不变，j后退
        }
        
    }
    if(j >= t.length)
        return i-t.length;
    else
    {
        return -1;
    }
    
}



int main(void)
{
    SqString s,t;
    char a[] = {'a','b','c','d','\0'};
    char b[] = {'b','c','d','\0'};
    InitString(&s,a);
    InitString(&t,b);
    int i = KMPIndex(s,t);
    printf("%d\n",i);
    DispStr(s);
    DispStr(t);


    getchar();
    getchar();
    return 0;
}