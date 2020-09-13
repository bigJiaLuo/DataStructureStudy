/*
    时间：2020年9月4日17:35:31
    二叉搜索树（排序）
*/
#include <stdio.h>
#include <malloc.h>
typedef int KeyType;
typedef int InfoType;
typedef struct BSTSearch
{
    KeyType key;//元素类型
    InfoType data;//其他数据类型
    struct BSTSearch * lchild,*rchild;//左右孩子
}BSTNode;

/*
    插入一个元素到二叉排序树中，保证不破坏二叉排序树的性质
*/
int InsertBST(BSTNode * &p,KeyType k){
    //原树为空时，新插入的结点为根节点
    if (p == NULL)
    {
        p = (BSTNode *)malloc(sizeof(BSTNode));
        p->key = k;
        p->lchild = p->rchild = NULL;
        return 1;
    }
    else if(k == p->key)
        return 0;//结点已经存在相同关键字k
    else if(k < p->key)
        return InsertBST(p->lchild,k);//将关键字k往根节点的左边插
    else
        return InsertBST(p->rchild,k);    //将关键字k往根节点的右边插
    
}


/*
    构建一棵二叉排序树
    A为顺序表，n为表中元素
*/
BSTNode * CreateBST(KeyType A[],int n){
    BSTNode * bt = NULL;
    int i = 0;
    //遍历表中所有元素，并执行插入操作
    while (i < n)
    {
        InsertBST(bt,A[i]);
        i++;
    }
    return bt;
}

BSTNode * SearchBST(BSTNode * B,KeyType key){
    if (B == NULL || B->key == key)
    {
        return B;   //没找到对应结点，或者找到对应结点都 返回B
    }
    else if (B->key < key)
    {
        return SearchBST(B->rchild,key);
    }else
    {
        return SearchBST(B->lchild,key);
    }
}

/*
    1.删除结点存在左右两个孩子，按照二叉树排序树的性质，按中序遍历得到一个有序的序列。
    2.找其删除结点的 左子树的最右结点（该节点再无右孩子），即为 删除结点在有序序列中的直接前驱，将其替换 删除结点位置
    3.然后用该节点的左孩子顶替 其父节点的位置（最右结点）
*/
void Delete1(BSTNode * p,BSTNode * &r){
    BSTNode * q;
    if (r->rchild != NULL)
    {
        Delete1(p,r->rchild);//找到最右结点
    }else//找到最右结点，即是p的直接前驱结点,r此时没有右孩子
    { 
        p->key = r->key;//最右结点替换p的关键字，即删除 p
        q = r;//保存最右结点

        r = r->lchild;//直接将其左子树的根 替换 最右结点的位置，因右孩子为空

        free(q);//删除之前的那个最右结点
    }

    
}

/*
    非递归，删除存在左右孩子的结点
*/
void Delete2(BSTNode * &p){
    BSTNode * q,*r;//保存其双亲结点
    //p结点右子树为空，直接用其左子树替换其位置
    if (p->rchild == NULL)
    {
        q = p;
        p = p->lchild;
        free(q);
    }
    else if(p->lchild == NULL){
        q = p;
        p = p->rchild;
        free(q);
    }else//左右孩子都存在
    {
        q = p;

        //找到其删除结点p的左子树中的最右结点
        r = p->lchild;
        while (r->rchild)
        {
            q = r;//保存r的双亲结点
            r = r->rchild;
        }
        p->key = r->key;//最右结点覆盖 删除结点
        if (q != p)
        {//说明最右结点r在右边，将其 左孩子顶替其 最右孩子的位置
            q->rchild = r->lchild;
        }else
        {
            //说明最右结点r在左边
            q->lchild = r->lchild;
        }
        free(r);
    }
    

}
void Delete(BSTNode * &p){
    BSTNode * q;//保存其双亲结点
    //p结点右子树为空，直接用其左子树替换其位置
    if (p->rchild == NULL)
    {
        q = p;
        p = p->lchild;
        free(q);
    }
    else if(p->lchild == NULL){
        q = p;
        p = p->rchild;
        free(q);
    }else//左右孩子都存在
    {
        //将其删除结点，和其左孩子传入
        Delete1(p,p->lchild);
    }

}

/*
    在二叉排序树中删除，关键字为k的结点
*/
int DeleteBST(BSTNode * &b,KeyType k){
    if (b == NULL)
    {
        return 0;//空树删除失败
    }else
    {
        if (k < b->key)//递归在左子树删除 关键字为k的结点
        {
            DeleteBST(b->lchild,k);
        }
        else if (k > b->key)//递归在右子树删除 关键字为k的结点
        {
            DeleteBST(b->rchild,k);
        }else
        {
            // Delete(b);
            Delete2(b);
            return 1;
        }
        
    }  
}
int main(void){

    int a[] = {1,2,3,4,5,6};
    BSTNode * B,*p;
    B = CreateBST(a,6);
    DeleteBST(B,3);
    p = SearchBST(B,3);
    if (p)
    {
        printf("%d",p->key);
    }else
    {
        printf("not found");
    }
    
    
    getchar();
    getchar();
    return 0;
}