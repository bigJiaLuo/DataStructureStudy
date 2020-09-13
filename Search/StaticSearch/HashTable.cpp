/*
    哈希表，采用求余数法获得散列地址，采用线性探测法解决地址冲突
    时间：2020年9月9日10:52:49
*/

#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
#define NULLKEY -1//定义空关键字
#define DELKEY -2 //表示已删除结点
typedef int KeyType;//关键类型
typedef char * InfoType;//其他数据类型

typedef struct HashTable
{
    KeyType key;//关键字域
    InfoType data;//其他数据域
    int count;//探查次数
}HashTable[MaxSize];

/* 
    查找与建表类似
    ha哈希表，p为被除数，key为关键字
 */
int SearchHT(HashTable ha,int p,KeyType key){
    
    int adr = 0;
    adr = key % p;//拿余数
    
    //1.在哈希表中搜索关键字，不为空，且不相等
    while (ha[adr].key != NULLKEY && ha[adr].key != key)
    {
        adr = (adr+1) % p;//采用线性探测法
    }

    if (ha[adr].key == key)//查找成功
    {
        return adr;
    }else
    {
        return -1;
    }
}

/* 
    删除哈希表中的关键字key
    ha哈希表，p为被除数，key为关键字,n为元素个数
 */
int DeleteHT(HashTable ha,int p,int key,int &n){
    int adr = 0;
    adr = SearchHT(ha,p,key);//查找key在哈希表中角标
    if (adr != NULLKEY)
    {
        //在该地址上的key置为已删除
        ha[adr].key = DELKEY;
        n--;
        return 1;
    }else
    {//adr为空，未找到
        return 0;
    }
}

/* 
    插入操作
    ha哈希表，p为被除数，key为关键字,n为元素个数
 */
void InsertHT(HashTable ha,int &n,KeyType k,int p){
    int adr;
    adr = k % p;
    //在adr位置上的结点为空，或一置为已删除，可以进行插入
    if (ha[adr].key == NULLKEY || ha[adr].key == DELKEY)
    {
        ha[adr].key = k;
        ha[adr].count = 1;
    }else
    {
        //发生冲突
        int i = 1;
        do
        {
            //对哈希表进行探测
            adr = (adr+1) % p;
            i++;
        } while (ha[adr].key != NULLKEY && ha[adr].key != DELKEY);
        //找到合适位置，插入
        ha[adr].key = k;
        ha[adr].count = i;
    }
    n++; //元素个数加一
}

/* 
    创建表
    ha哈希表，p为被除数，key为关键字,n为元素个数
 */
void CreateHT(HashTable ha,KeyType x[],int n,int m,int p){
    int i,n1 = 0;//n1为当前元素个数
    //初始化所有哈希表中的元素为空
    for ( i = 0; i < n; i++)
    {
        ha[i].key = NULLKEY;
        ha[i].count = 0;
    }

    //将x数组中的元素依次插入到哈希表
    for ( i = 0; i < n; i++)
    {
        InsertHT(ha,n1,x[i],p);
    } 
}

int main(void){
    return 0;
}