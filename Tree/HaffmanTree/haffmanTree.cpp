/*
    构造哈夫曼树
    时间：2020年6月14日15:21:15
    作者：泽兑ing
*/

#include <stdio.h>
#include <malloc.h>

typedef struct
{
    char data;     //结点值
    double weight; //权重
    int parent;    //双亲结点
    int lchild;    //左孩子
    int rchild;    //右孩子

} HTNode;

typedef struct{
    char cd[10];//存放当前结点的哈夫曼树编码
    int start;//cd[start] ~ cd[n]存放哈夫曼编码
}HCode;
/*
    构建一棵哈夫曼树，n个叶子结点，存在 2n-1个结点
        将哈夫曼树存于 ht[]中，前n个结点为 叶子节点，且带权重。

    思路： 
        1.将所有2n-1个结点的parent，lchild，rchild为-1
        2.处理每个非叶子结点ht[i](存放在ht[n] ~ ht[2n-2])
            ·从ht[0] ~ ht[i-1],找到权值最小的两个结点ht[lnode],ht[rnode]
            ·将它们作为ht[i]的左右子树，且它们各自的域中的值相应赋值
        3.如此操作，直到n-1个非叶子结点处理完毕
*/
void CreateHT(HTNode ht[], int n)
{
    int i, j, k, lnode, rnode;
    double min1, min2;
    for (i = 0; i < 2 * n - 1; i++)
    {
        ht[i].parent = ht[i].lchild = ht[i].rchild = -1; //所有结点的相关域为-1
    }
    for (i = n; i < 2 * n - 1; i++) //构造哈夫曼树
    {
        min1 = min2 = 32767; //lnode，rnode为权重最小的两个结点位置
        lnode = rnode = -1;
        for (k = 0; k < i - 1; k++) //在ht[]找权值最小的两个结点
        {
            if (ht[k].parent == -1)//只在尚未构造二叉树的结点中查找
            {
                if (ht[k].weight < min1)//找比min1权值小的结点位置
                {
                    min2 = min1;//min1即将被覆盖，用min2，rnode保存  之前min1，lnode 权值最小的结点位置，留下一次比较
                    rnode = lnode;
                    min1 = ht[k].weight;
                    lnode = k;
                }
                else if (ht[k].weight < min2)//找比min2权值小的结点位置
                {
                    min2 = ht[k].weight;
                    rnode = k;
                }
            }
            ht[i].weight = ht[lnode].weight + ht[rnode].weight;//由最小权值的左右孩子构建的双亲结点
            ht[i].lchild = lnode;
            ht[i].rchild = rnode;
            //两个结点已经完成构造二叉树，parent指向其双亲，下次不参与比较
            ht[lnode].parent = i;
            ht[rnode].parent = i;
        }
    }
}

/**/
void CreateHCode(HTNode ht[],HCode hcd[],int n){
    int i,f,c;
    HCode hc;
    for ( i = 0; i < n; i++)//根据哈夫曼树求哈夫曼编码
    {
        hc.start = n;
        c = i;
        f = ht[i].parent;
        while (f != -1)//循环直到无双亲结点及到达树根结点为止
        {
            if(ht[f].lchild == c){//当前结点是其双亲结点的左孩子结点
                hc.cd[hc.start--] = '0';
            }
            else//当前结点是其双亲结点的右孩子结点
            {
                hc.cd[hc.start--] = '1';
            }
            c = f;
            f = ht[f].parent;//再对其双亲结点进行同样的操作
            
        }
        hc.start++;//start指向哈夫曼编码的开始字符
        hcd[i] = hc;        
    }
    
}

int main(void)
{

    getchar();
    getchar();
    return 0;
}