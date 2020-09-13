#include <stdio.h>
#include <malloc.h>

#define LH 1;//左高
#define EH 0;//等高
#define RH -1;//右高
typedef struct BITree
{
    int data;//结点数据
    int bf;//平衡因子
    struct BITree *lchild,*rchild;//左右孩子指针  
}BITreeNode,*BITree;


/* 
    对以p为根的二叉排序树作右旋处理；
    处理之后p指向新的树根结点，即旋转处理之前的左子树根节点
 */
void R_Rotate(BITree &p){
    BITree L;
    L = p->lchild;//L指向p的左子树根节点
    p->lchild = L->rchild;//L的右子树挂在p的左子树上
    L->rchild = p;
    p = L;//p指向新的根节点
}

/* 
    对以p为根的二叉排序树作左旋处理；
    处理之后p指向新的树根结点，即旋转处理之前的右子树根节点
 */
void L_Rotate(BITree &p){
    BITree R;
    R = p->rchild;
    p->rchild  = R->lchild;//R的左子树挂接在p的右子树
    R->lchild = p;
    p = R;//p指向新的根节点
}


/* 
    对以指针T所指的结点为根的二叉树作左平衡旋转处理
    T指向新的根节点
 */
void LeftBalance(BITree &T){
    BITree L,Lr;
    L = T->lchild;
    switch (L->bf)
    {
        case 1:
            T->bf = L->bf = EH;
            R_Rotate(T);
            break;
        case -1:
            Lr = L->rchild;//Lr指向T的左孩子的右子树根
            switch (Lr->bf)
            {
                case 1:
                    T->bf = RH;
                    L->bf = EH;
                    break;
                case 0:
                    T->bf = L->bf = EH;
                    break;
                case -1:
                    T->bf = EH;
                    L->bf = LH;
                    break;
            }
            Lr->bf = EH;
            L_Rotate(T->lchild);//对T的左子树左旋平衡处理
            R_Rotate(T);//对T作右旋处理
    }
}

int InsertAVL(BITree &T,int e,int *taller){
    
}

int main(void){

    return 0;
}