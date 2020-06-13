#include <stdio.h>
#include <malloc.h>

#define MaxSize 10//最大结点数
typedef int ElemType;
/*
    双亲表示法
*/
typedef struct node
{
    ElemType data;//数据域
    int parent;//该结点双亲的位置
}PTree[MaxSize];

/*
    孩子链表示法
*/
typedef struct node{
    ElemType data;//数据域
    struct node * sons[MaxSize];//存储所有孩子结点的指针数组
    //MaxSize 根据树的度，取值
}TSonNode;

/*
    孩子兄弟表示法
*/
typedef struct node{
    ElemType data;//数据域
    struct node * fb;//指向下一个兄弟
    struct node * fc;//指向第一个孩子
}TSBNode;


/*
    求 孩子兄弟结构树  的高度
    使用递归
    设f（t）为树t的高度递归模型:
        f(t) = 0  若t == NULL
        f(t) = 1   若t 没有孩子结点
        f(t) = MAX(f(p)+1)  其他情况
        p为t的孩子
*/
int TreeHeight(TSBNode * t){
    TSBNode * p;
    int m,max = 0;
    if(t == NULL)
        return 0;//空树返回0
    if(t->fc == NULL)
        return 1;//树没有孩子结点
    else{
        p = t->fc;//指向第一个孩子结点
        while(p != NULL){//从所有孩子结点中找到一个高度最大的孩子
            m = TreeHeight(p);
            if(max < m)
                max = m;
            p = p->fb;//继续求其他兄弟的高度
        }
        return max+1;//返回当前树的高度
    }
}


int main(void){
    
    
    getchar();
    getchar();
    return 0;
}