/*
    并查集，如亲戚关系
    时间：2020年7月4日11:58:17
    作者：泽兑ing
*/

#include <stdio.h>
#define N 10
typedef struct node
{
    int data;//结点对应人的编号
    int rank;//子树高度的正整数，也是该结点高度的上限
    int parent;//结点对应的父节点
}UFSTree;//并查集树的结点类型

/*
     并查集树的初始化
     建立一个存放并查集树的数组t，对于亲戚关系 ，每个结点的data值设置为其所对应的人的编号，rank值为0，parent值设为自己
*/
void MAKE_SET(UFSTree t[]){
    int i;
    for ( i = 0; i <= N; i++)
    {
        t[i].data = i;
        t[i].rank = 0;
        t[i].parent = i;
    }
    
}

/*
    查找一个元素所属的集合
    在分离集合森林中，每一课分离集合树对应一个集合。要查找 某个元素所属的集合，就是要找这个元素的结点所在的分离树
*/
int FIND_SET(UFSTree t[],int x){
    if (x != t[x].parent)//当前结点不为双亲
    {
        return FIND_SET(t,t[x].parent);//递归双亲中找到x
    }else{

        return x; //双亲为自己，返回分离树的根节点
    }
    
}

/*
    两个元素各自所属的集合的合并
    思路：
        1.比较两个结点的秩，让较小的秩的根指向较大的秩的根
        2.如果两根相等，则让其中一个根指向另一个根，同时秩加一
*/
void UNION(UFSTree t[],int x,int y){//将x和y所在的子树合并
    x = FIND_SET(t,x);//查找 x，y对应分离树中的根节点
    y = FIND_SET(t,y);
    if (t[x].rank > t[y].rank)  //y的秩域小于x，则让y称为 x的孩子结点
    {
        t[y].parent = x;
    }else{//y的秩域大于等于x
        t[x].parent = y;
        if (t[x].rank == t[y].rank)//x 与 y 的秩域是否相等
        {
            t[y].rank++;
        }
    }
    
}



int main(void){
    return 0;
}