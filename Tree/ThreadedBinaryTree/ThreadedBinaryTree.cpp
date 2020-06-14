/*
    线索二叉树
    时间：2020年6月14日10:04:08
    作者：洛
*/
#include <stdio.h>
#include <malloc.h>
#define MaxSize 10
typedef int ElemType;
typedef struct node{
    ElemType data;//数据域
    int ltag,rtag;//线索标记
    struct node * lchild;
    struct node * rchild;
}TBTNode,* PTBTNode;
PTBTNode pre;//全局变量，保存p的前驱结点

/*
    对以p为根节点的二叉树进行线索化
    思路：  类似中序遍历递归算法
        1.在p不为NULL时，先对 p结点的左子树线索化，若p结点没有左孩子，则将其lchild指针线索化指向其前驱结点pre，将其ltag为1
        2.若pre的rchild为null，将其rchild指针线索化为指向其后继结点 p，将其rtag为1
        3.最后对p结点的右子树进行线索化
*/
void Thread(PTBTNode &p){//对二叉树p进行中序线索化
    if(p != NULL){
        Thread(p->lchild);//左子树线索化

        //此时p结点左子树不存在，或已经线索化
        if(p->lchild == NULL){
            p->lchild = pre;//左子树不存在，进行前驱结点线索化
            p->ltag = 1;//建立当前结点的前驱线索
        }else
        {
            p->ltag = 0;//左子树存在，ltag为左孩子
        }
        
        if(pre->rchild == NULL){//对pre的后继结点线索化
            pre->rchild = p;
            pre->rtag = 1;
        }else
        {
            pre->rtag = 0;
        }

        pre = p;
        Thread(p->rchild);
        
    }
}
/*
    创建一棵线索二叉树
    思路：
        1.先建立头结点 root，其lchild为链指针，rchild为线索
        2.将lchild指针指向 b，如果二叉树b为空，则将lchild指向自身，否则将root 的lchild指向b，p指向b，pre指向root
        3.在调用Thread（b），将整个二叉树线索化
        4.最后加入头结点的线索，将头结点的rchild指针域线索化为指向最后一个结点（由于线索化直到p等于NULL为止，所以最后一个访问的为pre）
*/
TBTNode * CreaThread(PTBTNode b){//中序
    TBTNode * root;
    root = (PTBTNode)malloc(sizeof(TBTNode));//创建头结点
    root->ltag = 0;
    root->rtag = 1;
    root->rchild = b;
    if(b == NULL){//空二叉树
        root->lchild = root;
    }
    else
    {
        root->lchild = b;
        pre = root;
        Thread(b);
        pre->rchild = root;
        pre->rtag = 1;
        root->rchild = pre;//头结点右线索化
    }
    return root;
    
}
void CreateTBTNode(PTBTNode *b, char *str)
{
    TBTNode *St[MaxSize], *p; //p用来临时存储新节点
    int top = -1, k, j = 0;  //j 为str下标
    char ch = str[j];        //ch 保存 str每次遍历的单个字符
    *b = NULL;               //将根节点置空
    while (ch != '\0')
    { //str 不空
        switch (ch)
        {
        case '(':
            //开始处理孩子结点，将之前创建的结点入栈
            top++;
            St[top] = p;
            k = 1; //标记下一个元素结点为 左孩子
            break;
        case ')':
            //表示以栈顶为根节点的子树创建完毕
            top--;
            break;
        case ',':
            //  表示下一结点为右孩子
            k = 2;
            break;
        default:
            //表示当前字符，为元素结点
            p = (PTBTNode)malloc(sizeof(TBTNode));
            p->data = ch;
            p->lchild = p->rchild = NULL;
            if (*b == NULL)
            {
                //还没创建二叉树的根节点
                *b = p;
            }
            else
            {
                switch (k)
                {
                case 1:
                    //左孩子
                    St[top]->lchild = p;
                    break;
                case 2:
                    //右孩子
                    St[top]->rchild = p;
                    //其他情况不处理
                }
            }
            break;
        }
        j++;
        ch = str[j]; //迭代语句
    }
}

/*
    先序遍历
*/
void PreOrder(PTBTNode b)
{
    if (b != NULL)
    {
        printf("%c\t", b->data);
        PreOrder(b->lchild);
        PreOrder(b->rchild);
    }
}



int main(void){
    char * str1 = "a(b(d(,g)),c(e,f))";
    TBTNode * T1,T2;
    CreateTBTNode(&T1,str1);
    CreaThread(T1);
    PreOrder(T1);
    getchar();
    getchar();
    return 0;
}