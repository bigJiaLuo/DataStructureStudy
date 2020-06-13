#include <stdio.h>
#include <malloc.h>
#define MaxSize 10

typedef char ElemType;
typedef ElemType SqBTree[MaxSize]; //顺序存储结构

typedef struct BTNode
{                          //结点链式存储结构
    ElemType data;         //数据域
    struct BTNode *lchild; //左孩子
    struct BTNode *rchild; //右孩子
} BTNode, *PBTNode;

/*
    创建一棵二叉树，使用括号表示法进行输入，括号表示法 有四种状态
        1.（  表示之前创建的结点存在孩子结点，需要将其入栈，其后的字符不是 （，表示可以开始处理孩子结点，k = 1，表示此结点为栈顶结点的左孩子
        2. ） 表示以栈顶结点为根节点的子树创建完毕，将栈顶退栈
        3. ， 表示开始处理栈顶指针的右孩子
        4. 其他情况  表示该字符只能是元素结点，需要创建新的结点，根据k 的值，将其连接到栈顶 结点的 对应孩子位置
    如此循环 str处理完毕，栈St保存双亲结点，top为栈顶指针，k为孩子状态
*/
void CreateBTNode(PBTNode *b, char *str)
{
    BTNode *St[MaxSize], *p; //p用来临时存储新节点
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
            p = (PBTNode)malloc(sizeof(BTNode));
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
    查找结点
    递归模型：
        f(b,x) = NULL  若 b == NULL
        f(b,x) = b       若b->data == x
        f(b,x) = p        若在左子树找到了，即p = f(b->lchild,x).且 p !=NULL
        f(b,x) = f(b->rchild,x)     其他情况
*/
PBTNode FindNode(PBTNode b, ElemType x)
{
    PBTNode p = NULL; //保存查找之后的结点
    if (b == NULL)
        return NULL;
    else if (b->data == x)
        return b;
    else
    {
        p = FindNode(b->lchild, x);
        if (p != NULL)
            return p;
        else
        {
            return FindNode(b->rchild, x);
        }
    }
}

/*
    找左孩子
*/
PBTNode FindLChild(BTNode b)
{
    return b.lchild;
}

/*
    找右孩子
*/
PBTNode FindRChild(BTNode b)
{
    return b.rchild;
}

/*
    求树的高度
    递归模型：
        f(b) = 0            若b = NULL
        f(b) = MAX{f(b->lchild),f(b->rchild)} +1
*/
int BTNodeHeight(BTNode *b)
{

    int lchild, rchild; //存放左子树高度，右
    if (b == NULL)
        return 0;
    else
    {
        lchild = BTNodeHeight(b->lchild);
        rchild = BTNodeHeight(b->rchild);
        return (lchild > rchild) ? (lchild + 1) : (rchild + 1);
    }
}

/*
    输出二叉树
    递归思路：
        1.对于非空二叉树，先输出b所指结点的值。
        2.当b 结点存在左孩子结点或右孩子是，输出一个 （ ，然后递归处理左子树
        3.当存在右孩子时，输出一个  符号，递归处理右子树
        4.最后输出一个  ）  
*/
void DisPBTNode(PBTNode b)
{
    if (b != NULL)
    {
        printf("%c", b->data);
        if (b->lchild != NULL || b->rchild != NULL)
        {
            //存在孩子结点
            printf("(");
            DisPBTNode(b->lchild); //递归处理左孩子
            if (b->rchild != NULL)
                printf(",");       //存在右孩子，输出，
            DisPBTNode(b->rchild); //递归处理右孩子
            printf(")");           //处理完以某个根节点的子树
        }
    }
}

/*
    先序遍历
*/
void PreOrder(PBTNode b)
{
    if (b != NULL)
    {
        printf("%c\t", b->data);
        PreOrder(b->lchild);
        PreOrder(b->rchild);
    }
}

/*
    中序遍历
*/
void InOrder(PBTNode b)
{
    if (b != NULL)
    {
        InOrder(b->lchild);
        printf("%c", b->data);
        InOrder(b->rchild);
    }
}

/*
    后序遍历
*/
void PostOrder(PBTNode b)
{
    if (b != NULL)
    {
        PostOrder(b->lchild);
        PostOrder(b->rchild);
        printf("%c", b->data);
    }
}

//非递归遍历
/*
    先序遍历
    思路：
        1、先根，再左，再右
        2.先将根结点入栈，再出栈打印
            ·在判断是否存在右孩子，有入栈
            ·在判断有无左孩子，有入栈
        3.一直循环到栈空
*/
void PreOrder1(PBTNode b)
{
    PBTNode p;           //临时存放栈顶元素
    PBTNode St[MaxSize]; //存放先序结点的顺序
    int top = -1;        //栈顶指针
    if (b != NULL)
    {
        top++;
        St[top] = b;
        while (top > -1)
        {                  //栈不空
            p = St[top--]; //取出栈顶，top--
            printf("%c\t", p->data);
            if (p->rchild != NULL)
                St[++top] = p->rchild; //右孩子入栈
            if (p->lchild != NULL)
                St[++top] = p->lchild;
        }
        printf("\n");
    }
}
/*
    中序遍历
    思路：
        1.先找到根节点的最底层的左子树，沿途依次将左子树入栈，直到左子树为空
        2.在访问当前根节点
        3.将访问根节点的右子树
        4.重复以上步骤
*/
void InOrder1(PBTNode b)
{
    PBTNode St[MaxSize], p;
    int top = -1; //栈顶指针
    if (b != NULL)
    {
        p = b;
        while (top > -1 || p != NULL) //栈不空，存在结点
        {
            while (p != NULL) //将左子树依次进栈
            {
                St[++top] = p;
                p = p->lchild;
            }
            if (top > -1)
            {
                p = St[top--];
                printf("%c\t", p->data); //输出根节点
                p = p->rchild;           //处理p的右孩子结点
            }
        }
    }
}

/*
    后序遍历
    思路：
        1.采用一个栈保存需要返回的结点指针，先扫描根节点的所有左孩子并一一进栈
        2.出栈一个结点 *b 当做当前结点
            ·然后扫描该节点的右子树
        3.当一个结点的左右子树均访问，再访问该节点。重复操作
        难点：
            如何判断一个结点 *b的右子树已经访问过
            1.用p指针来保存刚刚访问的结点（初值为NULL），若b->rchild == p ，说明*b的左右子树已经访问过

*/
void PostOrder1(PBTNode b)
{
    PBTNode St[MaxSize];
    PBTNode p;
    int flag, top = -1; //flag 表示是否*b的左子树是否访问过，或空
    if (b != NULL)
    {
        do
        {
            while (b != NULL) //将*b的所有左子树入栈
            {
                St[++top] = b;
                b = b->lchild;
            }
            //执行到此处时，栈顶元素没有左孩子或左孩子已访问
            p = NULL;
            flag = 1; //表示左子树已访问
            while (top > -1 && flag)
            {
                b = St[top]; //先取出栈顶，不退栈
                /*
                    若p == NULL，说明b的右孩子不存在，左子树访问完毕。p ！= NULL，说明，*b的右子树访问完毕，p指向b的右孩子，因可以访问b结点
                */
                if (b->rchild == p)
                {
                    printf("%c\t", b->data);
                    top--;
                    p = b; //指向访问过的结点
                }
                else
                {
                    b = b->rchild; //说明*b的左右子树都访问完毕，接下来访问*b，b->rchile == NULL
                    flag = 0;
                }
            }

        } while (top > -1);
    }
    printf("\n");
}

/*
    层次遍历
    需要一层一层的遍历二叉树，可采用循环队列来存储结点。将每一层的结点一次存入队列
    front 指向队头的前一下标，rear 指向队尾
    思路：
        1.创建一个队列，来保存所有入队结点，先将 根节点入队
        2.出队，访问该结点
        3.入队操作
            ·判断当前结点是否有左孩子，有则入队，判断一次
            ·同理，有右孩子，入队，一次
        4.重复操作，直到队列为空
*/
void LevelOrder(PBTNode b){
    PBTNode p,qu[MaxSize];
    int front = -1,rear = -1;//队列为空
    if (b != NULL)
        rear++;
    qu[rear] = b;//根节点入队
    while (front != rear)//队不空
    {
        front = (front + 1) % MaxSize;//队头出队
        p = qu[front];
        printf("%c\t",p->data);
        if(p->lchild != NULL){
            rear = (rear + 1) % MaxSize;
            qu[rear] = p->lchild;//左孩子入队
        }
        if (p->rchild != NULL)
        {
            rear = (rear + 1) % MaxSize;
            qu[rear] = p->rchild;//右孩子入队
        }
        
    }
    
    
}

//应用
/*
    给定一棵二叉树，输出其所有的叶子结点
    递归模型：
        1.f(b)  无操作      b == NULL
        2.f(b) = 输出 *b 结点的data     *b 为叶子结点
        3.f(b) = f(b->lchild);f(b->rchild);     其他情况
*/
void DisLeaf(PBTNode b)
{
    if (b != NULL)
    {
        if (b->lchild == NULL && b->rchild == NULL)
            printf("%c", b->data);
        DisLeaf(b->lchild);
        DisLeaf(b->rchild);
    }
}
/*
    逆序输出 叶子结点
    只需将递归循序更换
*/
void DisLeaf1(PBTNode b)
{
    if (b != NULL)
    {
        if (b->lchild == NULL && b->rchild == NULL)
            printf("%c", b->data);
        DisLeaf(b->rchild);
        DisLeaf(b->lchild);
    }
}

/*
    求二叉树中结点值 为 x的 所在的层数，假设二叉树中的值 不相同,h初值为1
    递归思路：
        1.b 为空树，返回 0
        2.当前结点的结点值为x ，返回h
            ·否则，从左子树查找
            ·右子树查找
        每次进入相应子树，h同步自增，对应所在结点的层数
*/
int Level(PBTNode b, ElemType x, int h)
{
    int l = 0;
    if (b == NULL)
        return 0;
    else if (b->data == x)
        return h;
    else
    {
        l = Level(b->lchild, x, h + 1); //从左子树查找,进入下一层
        if (l != 0)
            return l;
        else
        {
            return Level(b->rchild, x, h + 1); //左子树未找到，进入右子树
        }
    }
}

/*
    判断两棵二叉树是否相似
    递归模型：
        1.f(t1,t2) = true       t1，t2都为空
        2.f(t1,t2) = flase      t1,t2其中有一为NULL，另一不为NULL
        3.f(t1,t2) = f(t1->lchild,t2->lchild) && f(t1->rchild,t2->rchild)
*/
bool Like(PBTNode b1, PBTNode b2)
{
    bool like1, like2;            //左子树，右子树，标识
    if (b1 == NULL && b2 == NULL) //判断是否都为NULL
        return true;
    else if (b1 == NULL || b2 == NULL) //判断是否有一为NULL
    {
        return false;
    }
    else
    {
        like1 = Like(b1->lchild, b2->lchild);
        like2 = Like(b1->rchild, b2->rchild);
        return like1 && like2; //左右子树都相似
    }
}

/*
    输出  值为x 的所有祖先
    思路: 祖先  a 为 b 或b的子树的 孩子，即 b为a 的祖先
        1.设f(b,x)表示b结点是否值为x的结点祖先结点
            ·若是，f(b,x) = true
            ·否则，f(b,x) = false.
        2，当f(b,x) 为true时，输出 b结点的值
        3. 递归模型：
            ·f(b,x) = false         若 b == NULL
            ·f(b,x) = true          若b 结点的左或右孩子data域为x
            ·f(b,x) = true          若f(b->lchild,x) == true 或  f(b->rchild,x) == true
            ·f(b,x) = false         其他情况
*/

bool ancestor(PBTNode b, ElemType x)
{
    if (b == NULL)
        return false; //递归出口
    else if (b->lchild != NULL && b->lchild->data == x || b->rchild != NULL && b->rchild->data == x)
    {
        printf("%c\t", b->data);
        return true; //递归出口
    }
    else if (ancestor(b->lchild, x) || ancestor(b->rchild, x)) //递归体
    {
        printf("%c\t", b->data);
        return true;
    }
    else
        return false;
}

/*
    二叉树为二叉链结构
    输出从根节点到每个叶子结点的路径的 元素逆序
    后序非递归中的栈中保存该节点的所有祖先结点，且次序是逆序的
    思路：
        1.采用后续非递归的思路，将输出结点的操作，该为判断是否是叶子结点
*/
void AllPath1(PBTNode b)
{
    PBTNode St[MaxSize], p;
    int top = -1, flag;

    if (b != NULL)
    {
        do
        {
            while (b != NULL)
            {
                St[++top] = b;
                b = b->lchild;
            }
            p = NULL;
            flag = 1;
            while (top != -1 && flag)
            {
                b = St[top];
                if (b->rchild == p)
                {
                    if (b->lchild == NULL && b->rchild == NULL)
                    { //输出栈中所有元素
                        for (int i = top; i > 0; i--)
                            printf("%c ->", St[i]->data);
                        printf("%c\n", St[0]->data);
                    }
                    top--;
                    p = b;
                }
                else
                {
                    b = b->rchild;
                    flag = 0;
                }
            }

        } while (top != -1);
    }
    printf("\n");
}

/*
    输出二叉树 根节点到叶子结点 路径的  逆序
    也可以采用非环形队列的实现
    思路：
        1.声明一个存有 二叉链结构的结点类型，且具有该结点在队列中的双亲结点的下标
        2.将根节点入队，parent 为 -1
        3.当队列不空时，循环操作
            ·判断当前结点是否为叶子结点，是，则根据parent结点 从叶子结点持续遍历到根节点
        4.判断 是否有左右孩子，有则分别入队一次
        5.重复执行以上操作，直到队列为空
*/
void AllPath2(PBTNode b){
    struct snode{
        BTNode * node;//存放当前指针结点
        int parent;//存放双亲结点在队列额的位置
    }qu[MaxSize];
    int front = -1,rear = -1,p;//p临时保存双亲结点位置
    PBTNode q;//临时保存队首结点
    if(b != NULL){
        rear++;
        qu[rear].node = b;
        qu[rear].parent = -1;//根节点入队
    }
    while (front != rear)
    {
        front++;//当前队首在队列中的下标
        q = qu[front].node;//队首出队
        if(q->lchild == NULL && q->rchild == NULL){
            p = front;
            while (qu[p].parent != -1)//当前结点不是根节点
            {
                printf("%c ->",qu[p].node->data);
                p = qu[p].parent;//p指向下一个双亲位置
            }
            printf("%c\n",qu[p].node->data);//输出根节点
        }
        if (q->lchild != NULL)
        {
            rear++;
            qu[rear].node = q->lchild;
            qu[rear].parent = front;//指向其双亲
        }
        if(q->rchild != NULL){
            qu[++rear].node = q->rchild;
            qu[rear].parent = front;
        }
    }
    
}


int main(void)
{
    char *str1 = "a(b(d(,g)),c(e,f))";
    char *str2 = "a(b(d(,g)),c(e))";
    BTNode T, *PT1, *PT2;
    CreateBTNode(&PT1, str1);
    CreateBTNode(&PT2, str2);
    PBTNode s = FindNode(PT1, 'g');
    // printf("%c",s->data);
    int height = BTNodeHeight(PT1);
    // DisPBTNode(PT1);
    // PreOrder(PT1);
    // PreOrder1(PT1);
    // InOrder(PT1);
    // PostOrder(PT1);
    // PostOrder1(PT1);
    // AllPath1(PT1);
    AllPath2(PT1);
    // LevelOrder(PT1);
    // height = Level(PT1,'c',1);
    // DisLeaf(PT1);
    // bool flag = Like(PT1,PT2);
    // ancestor(PT1,'f');
    getchar();
    getchar();
    return 0;
}