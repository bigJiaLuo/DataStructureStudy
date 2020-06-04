
// 自定义Set集合
// 13.描述一个集合的抽象数据类型ASet，其中所有元素为正整数，集合的基本运算包括：
// （1）由整数数组a[0..n-1]创建一个集合。
// （2）输出一个集合的所有元素。
// （3）判断一个元素是否在一个集合中。
// （4）求两个集合的并集。
// （5）求两个集合的差集。
// （6）求两个集合的交集。
// 在此基础上设计集合的顺序存储结构，并实现各基本运算的算法。
// 答：抽象数据类型ASet的描述如下：
// ADT ASet
// {数据对象：D={d；l0≤isn，n为一个正整数}
// 数据关系：无。
// 基本运算：
// createset（&s，a，n）：创建一个集合s；
// dispset（s）：输出集合s；
// inset（s，e）：判断元素e是否在集合s中。
//求集合的并集
// void add（sl，s2，s3）：s3=slUs2；
// 求集合的差集
// void sub（s1，s2，s3）：s3=sl-s2；
//求集合的交集
// void intersection（s1，s2，s3）：s3=slls2；
// }
#include <stdio.h>
#define MaxSize 10

// Set集合的存储结构
typedef struct Set
{
    int data[MaxSize];//Set集合中的数据
    int length = 0;//Set集合的实际长度
}Set,* pSet;

/*
    s 为 Set集合的指针变量，a 为 需要存入的数组，n为数组的长度
*/
void createSet(Set * s,int a[],int n){
    if(a != NULL){
        for(int i = 0; i < n; i++){
            s->data[i] = a[i];
        }
        s->length = n;
    }
}

/*
    输出 Set集合
*/
void dispSet(Set s){
    for(int i = 0; i < s.length; i++){
        printf("%d\t",s.data[i]);
    }
    printf("集合长度为：%d\t",s.length);
}

/*
    判断 Set集合中是否存在e 这个元素，如果存在就 返回true
*/
bool inSet(Set s,int e){
    for(int i = 0; i < s.length; i++){
        if(s.data[i] == e){
            return true;
        }
    }
    return false;
}

/*
    求两个集合的并集。返回 两个集合向并的新集合
*/

Set add(Set s1,Set s2,Set s3){
    // 1.遍历集合s1，s2，将其所有元素追加到s3集合中
    s3.length = 0;
    for (int i = 0; i < s1.length; i++)
    {
        /* code */
        s3.data[i] = s1.data[i];
        s3.length++;
    }
    for(int j = 0; j < s2.length; j++){
        s3.data[s3.length] = s2.data[j];
        s3.length++;
    }

    return s3;
}

/*
    求两个集合的差， s3，返回两个集合的差.s3
    s1,不包含 s2中的元素，即为差 
*/
Set sub(Set s1,Set s2,Set s3){
    // 1.遍历s1  集合
      s3.length = 0;
    for(int i = 0; i < s1.length; i++){
        // 2.排除 s1中与s2 相同的元素,调用inSet函数，判断是否存在
        if(!inSet(s2,s1.data[i])){
            // 在s2中不存在
            s3.data[s3.length] = s1.data[i];
            s3.length++;
        }
    }

    return s3;
}

/*
    求两集合的 交集，s3返回两集合共有的属性
*/
Set intersection(Set s1,Set s2,Set s3){
    s3.length = 0;
    // 1.遍历 s1
    for(int i = 0; i < s1.length; i++){
        // 2.判断 s1中的元素是否在s2中存在
        if(inSet(s2,s1.data[i])){
            s3.data[s3.length] = s1.data[i];
            s3.length++;
        }
    }

    return s3;
}






int main(void){
    int a[] = {1,2,3};
    int b[] = {3,4,5};
    Set set1,set2,set3;
    createSet(&set1,a,3);
    createSet(&set2,b,3);
    // set3 = add(set1,set2,set3);
    // set3 = sub(set1,set2,set3);
    set3 = intersection(set1,set2,set3);
    dispSet(set3);
    // bool flag = inSet(set1,2);
    // printf("%d",flag);

    getchar();
    return 0;
}

