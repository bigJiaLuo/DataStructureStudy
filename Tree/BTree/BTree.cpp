#include <stdio.h>
#include <malloc.h>
#define MaxSize 10

typedef char ElemType;
typedef ElemType SqBTree[MaxSize]; //˳��洢�ṹ

typedef struct BTNode
{                          //�����ʽ�洢�ṹ
    ElemType data;         //������
    struct BTNode *lchild; //����
    struct BTNode *rchild; //�Һ���
} BTNode, *PBTNode;

/*
    ����һ�ö�������ʹ�����ű�ʾ���������룬���ű�ʾ�� ������״̬
        1.��  ��ʾ֮ǰ�����Ľ����ں��ӽ�㣬��Ҫ������ջ�������ַ����� ������ʾ���Կ�ʼ�����ӽ�㣬k = 1����ʾ�˽��Ϊջ����������
        2. �� ��ʾ��ջ�����Ϊ���ڵ������������ϣ���ջ����ջ
        3. �� ��ʾ��ʼ����ջ��ָ����Һ���
        4. �������  ��ʾ���ַ�ֻ����Ԫ�ؽ�㣬��Ҫ�����µĽ�㣬����k ��ֵ���������ӵ�ջ�� ���� ��Ӧ����λ��
    ���ѭ�� str������ϣ�ջSt����˫�׽�㣬topΪջ��ָ�룬kΪ����״̬
*/
void CreateBTNode(PBTNode *b, char *str)
{
    BTNode *St[MaxSize], *p; //p������ʱ�洢�½ڵ�
    int top = -1, k, j = 0;  //j Ϊstr�±�
    char ch = str[j];        //ch ���� strÿ�α����ĵ����ַ�
    *b = NULL;               //�����ڵ��ÿ�
    while (ch != '\0')
    { //str ����
        switch (ch)
        {
        case '(':
            //��ʼ�����ӽ�㣬��֮ǰ�����Ľ����ջ
            top++;
            St[top] = p;
            k = 1; //�����һ��Ԫ�ؽ��Ϊ ����
            break;
        case ')':
            //��ʾ��ջ��Ϊ���ڵ�������������
            top--;
            break;
        case ',':
            //  ��ʾ��һ���Ϊ�Һ���
            k = 2;
            break;
        default:
            //��ʾ��ǰ�ַ���ΪԪ�ؽ��
            p = (PBTNode)malloc(sizeof(BTNode));
            p->data = ch;
            p->lchild = p->rchild = NULL;
            if (*b == NULL)
            {
                //��û�����������ĸ��ڵ�
                *b = p;
            }
            else
            {
                switch (k)
                {
                case 1:
                    //����
                    St[top]->lchild = p;
                    break;
                case 2:
                    //�Һ���
                    St[top]->rchild = p;
                    //�������������
                }
            }
            break;
        }
        j++;
        ch = str[j]; //�������
    }
}

/*
    ���ҽ��
    �ݹ�ģ�ͣ�
        f(b,x) = NULL  �� b == NULL
        f(b,x) = b       ��b->data == x
        f(b,x) = p        �����������ҵ��ˣ���p = f(b->lchild,x).�� p !=NULL
        f(b,x) = f(b->rchild,x)     �������
*/
PBTNode FindNode(PBTNode b, ElemType x)
{
    PBTNode p = NULL; //�������֮��Ľ��
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
    ������
*/
PBTNode FindLChild(BTNode b)
{
    return b.lchild;
}

/*
    ���Һ���
*/
PBTNode FindRChild(BTNode b)
{
    return b.rchild;
}

/*
    �����ĸ߶�
    �ݹ�ģ�ͣ�
        f(b) = 0            ��b = NULL
        f(b) = MAX{f(b->lchild),f(b->rchild)} +1
*/
int BTNodeHeight(BTNode *b)
{

    int lchild, rchild; //����������߶ȣ���
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
    ���������
    �ݹ�˼·��
        1.���ڷǿն������������b��ָ����ֵ��
        2.��b ���������ӽ����Һ����ǣ����һ�� �� ,Ȼ��ݹ鴦��������
        3.�������Һ���ʱ�����һ��  ���ţ��ݹ鴦��������
        4.������һ��  ��  
*/
void DisPBTNode(PBTNode b)
{
    if (b != NULL)
    {
        printf("%c", b->data);
        if (b->lchild != NULL || b->rchild != NULL)
        {
            //���ں��ӽ��
            printf("(");
            DisPBTNode(b->lchild); //�ݹ鴦������
            if (b->rchild != NULL)
                printf(",");       //�����Һ��ӣ������
            DisPBTNode(b->rchild); //�ݹ鴦���Һ���
            printf(")");           //��������ĳ�����ڵ������
        }
    }
}

/*
    �������
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
    �������
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
    �������
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

//�ǵݹ����
/*
    �������
    ˼·��
        1���ȸ�����������
        2.�Ƚ��������ջ���ٳ�ջ��ӡ
            �����ж��Ƿ�����Һ��ӣ�����ջ
            �����ж��������ӣ�����ջ
        3.һֱѭ����ջ��
*/
void PreOrder1(PBTNode b)
{
    PBTNode p;           //��ʱ���ջ��Ԫ��
    PBTNode St[MaxSize]; //����������˳��
    int top = -1;        //ջ��ָ��
    if (b != NULL)
    {
        top++;
        St[top] = b;
        while (top > -1)
        {                  //ջ����
            p = St[top--]; //ȡ��ջ����top--
            printf("%c\t", p->data);
            if (p->rchild != NULL)
                St[++top] = p->rchild; //�Һ�����ջ
            if (p->lchild != NULL)
                St[++top] = p->lchild;
        }
        printf("\n");
    }
}
/*
    �������
    ˼·��
        1.���ҵ����ڵ����ײ������������;���ν���������ջ��ֱ��������Ϊ��
        2.�ڷ��ʵ�ǰ���ڵ�
        3.�����ʸ��ڵ��������
        4.�ظ����ϲ���
*/
void InOrder1(PBTNode b)
{
    PBTNode St[MaxSize], p;
    int top = -1; //ջ��ָ��
    if (b != NULL)
    {
        p = b;
        while (top > -1 || p != NULL) //ջ���գ����ڽ��
        {
            while (p != NULL) //�����������ν�ջ
            {
                St[++top] = p;
                p = p->lchild;
            }
            if (top > -1)
            {
                p = St[top--];
                printf("%c\t", p->data); //������ڵ�
                p = p->rchild;           //����p���Һ��ӽ��
            }
        }
    }
}

/*
    �������
    ˼·��
        1.����һ��ջ������Ҫ���صĽ��ָ�룬��ɨ����ڵ���������Ӳ�һһ��ջ
        2.��ջһ����� *b ������ǰ���
            ��Ȼ��ɨ��ýڵ��������
        3.��һ�������������������ʣ��ٷ��ʸýڵ㡣�ظ�����
        �ѵ㣺
            ����ж�һ����� *b���������Ѿ����ʹ�
            1.��pָ��������ոշ��ʵĽ�㣨��ֵΪNULL������b->rchild == p ��˵��*b�����������Ѿ����ʹ�

*/
void PostOrder1(PBTNode b)
{
    PBTNode St[MaxSize];
    PBTNode p;
    int flag, top = -1; //flag ��ʾ�Ƿ�*b���������Ƿ���ʹ������
    if (b != NULL)
    {
        do
        {
            while (b != NULL) //��*b��������������ջ
            {
                St[++top] = b;
                b = b->lchild;
            }
            //ִ�е��˴�ʱ��ջ��Ԫ��û�����ӻ������ѷ���
            p = NULL;
            flag = 1; //��ʾ�������ѷ���
            while (top > -1 && flag)
            {
                b = St[top]; //��ȡ��ջ��������ջ
                /*
                    ��b->rchild == p == NULL��˵��b���Һ��Ӳ����ڣ�������������ϡ�p ��= NULL��˵����*b��������������ϣ�pָ��b���Һ��ӣ�˵��b���Һ��ӷ�����,����Է���b���
                */
                if (b->rchild == p) //p����ΪNULL,Ҳ��Ϊb�ڵ���Һ���
                {                   //b�����������������Լ���ջ,���Է���b�ڵ�,Ȼ��b�ڵ���ջ
                    printf("%c\t", b->data);
                    for (int i = top; i >= 0; i--)
                    {
                        printf("%c ", St[i]->data);
                    }
                    printf("\n");

                    top--;
                    p = b; //pָ����ʹ��Ľ��
                }
                else
                {
                    b = b->rchild; //˵��b����������������������b����������b->rchild != NULL
                    flag = 0;
                }
            }

        } while (top > -1);
    }
    printf("\n");
}

/*
    ��α���
    ��Ҫһ��һ��ı������������ɲ���ѭ���������洢��㡣��ÿһ��Ľ��һ�δ������
    front ָ���ͷ��ǰһ�±꣬rear ָ���β
    ˼·��
        1.����һ�����У�������������ӽ�㣬�Ƚ� ���ڵ����
        2.���ӣ����ʸý��
        3.��Ӳ���
            ���жϵ�ǰ����Ƿ������ӣ�������ӣ��ж�һ��
            ��ͬ�����Һ��ӣ���ӣ�һ��
        4.�ظ�������ֱ������Ϊ��
*/
void LevelOrder(PBTNode b)
{
    PBTNode p, qu[MaxSize];
    int front = -1, rear = -1; //����Ϊ��
    if (b != NULL)
        rear = (rear + 1) % MaxSize;
    qu[rear] = b; //���ڵ����

    while (front != rear) //�Ӳ���
    {
        //��ͷ����,�����ǰ�ڵ�
        front = (front + 1) % MaxSize;
        p = qu[front];
        printf("%c\t", p->data);

        //����ǰ�ڵ�����������
        if (p->lchild != NULL)
        {
            rear = (rear + 1) % MaxSize;
            qu[rear] = p->lchild; //�������
        }
        //����ǰ�ڵ�����������
        if (p->rchild != NULL)
        {
            rear = (rear + 1) % MaxSize;
            qu[rear] = p->rchild; //�Һ������
        }
    }
}
/*
    ��֪������������� ������һ�ö�����
    pre �������У�in ����������У�nΪ���������ĸ��������ع���ö������ĸ�
    ��û��⣬2020��6��13��19:48:23
*/
PBTNode CreateBT1(char *pre, char *in, int n)
{
    PBTNode b; //���ָ��
    char *p;
    int k;
    if (n <= 0)
        return NULL;
    b = (BTNode *)malloc(sizeof(BTNode));
    b->data = *pre;
    for (p = in; p < in + n; p++)
    {                   //�������������ҵ���*pre�Ľ���λ��k
        if (*p == *pre) //preָ����ڵ�
            break;      //��in���ҵ����˳�ѭ��
    }
    k = p - in;                                           //ȷ�����ڵ���in�е�λ��
    b->lchild = CreateBT1(pre + 1, in, k);                //�ݹ鹹��������
    b->rchild = CreateBT1(pre + k + 1, p + 1, n - k - 1); //�ݹ鹹��������
    return b;
}

/*
    ��֪����ͺ��� ���У�����һ�ö�����
    post ��ź������У�inΪ�������У�nΪ������������
*/
PBTNode CreateBT2(char *post, char *in, int n)
{
    PBTNode b;  //��ʱ��Ž��
    char r, *p; //r��Ÿ��ڵ�ֵ��pָ����ڵ�
    int k;
    if (n <= 0)
        return NULL;
    r = *(post + n - 1); //���ڵ�ֵ
    b = (PBTNode)malloc(sizeof(BTNode));
    b->data = r;
    for (p = in; p < in + n; p++)
    { //��in�в��Ҹ��ڵ�
        if (*p == r)
            break;
    }
    k = p - in; //���ڵ�  in�е��±�
    b->lchild = CreateBT2(post, in, k);
    b->rchild = CreateBT2(post + k, p + 1, n - k - 1);
}

/*
    ��˳��洢��������ת��Ϊ��ʽ�洢������
    �ݹ�ģ��:
        f(a,i) = NULL       ��i����MaxSize
        f(a,i) = NULL       ��i��Ӧ�Ľ��Ϊ��
        f(a,i) = b(���������b����dataֵΪa[i]);    �������
                b->lchild = f(a,2*i);
                b->rchild = f(a,2*i +1);
*/
PBTNode trans(SqBTree a, int i)
{
    PBTNode b; //���ڵ�
    if (i > MaxSize)
        return NULL;
    if (a[i] == '#')
        return NULL; //��㲻����
    b = (PBTNode)malloc(sizeof(BTNode));
    b->data = a[i];
    b->lchild = trans(a, 2 * i);
    b->rchild = trans(a, 2 * i + 1);
    return b;
}

//Ӧ��
/*
    ����һ�ö���������������е�Ҷ�ӽ��
    �ݹ�ģ�ͣ�
        1.f(b)  �޲���      b == NULL
        2.f(b) = ��� *b ����data     *b ΪҶ�ӽ��
        3.f(b) = f(b->lchild);f(b->rchild);     �������
*/
void DisLeaf(PBTNode b)
{
    if (b != NULL)
    {
        //�Ƿ�ΪҶ�ӽ��
        if (b->lchild == NULL && b->rchild == NULL)
            printf("%c", b->data);
        //����b������
        DisLeaf(b->lchild);
        //����b���Һ���
        DisLeaf(b->rchild);
    }
}
/*
    ������� Ҷ�ӽ��
    ֻ�轫�ݹ�ѭ�����
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
    ��������н��ֵ Ϊ x�� ���ڵĲ���������������е�ֵ ����ͬ,h��ֵΪ1
    �ݹ�˼·��
        1.b Ϊ���������� 0
        2.��ǰ���Ľ��ֵΪx ������h
            �����򣬴�����������
            ��������������
        ÿ�ν�����Ӧ������hͬ����������Ӧ���ڽ��Ĳ���
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
        l = Level(b->lchild, x, h + 1); //������������,������һ��
        if (l != 0)//l������0˵�����������ҵ���x�Ĳ���������
            return l;
        else
        {
            //������δ�ҵ�������������
            return Level(b->rchild, x, h + 1); 
        }
    }
}

/*
    �ж����ö������Ƿ�����
    �ݹ�ģ�ͣ�
        1.f(t1,t2) = true       t1��t2��Ϊ��
        2.f(t1,t2) = flase      t1,t2������һΪNULL����һ��ΪNULL
        3.f(t1,t2) = f(t1->lchild,t2->lchild) && f(t1->rchild,t2->rchild)
*/
bool Like(PBTNode b1, PBTNode b2)
{
    bool like1, like2;            //������������������ʶ
    if (b1 == NULL && b2 == NULL) //�ж��Ƿ�ΪNULL
        return true;
    else if (b1 == NULL || b2 == NULL) //�ж��Ƿ���һΪNULL
    {
        return false;
    }
    else
    {
        like1 = Like(b1->lchild, b2->lchild);
        like2 = Like(b1->rchild, b2->rchild);

        return like1 && like2; //��������������
    }
}

/*
    ���  ֵΪx ����������
    ˼·: ������˼�ǣ�  a Ϊ b ����b�������� ���ӣ��� bΪa ������
        1.��f(b,x)��ʾb����Ƿ���ֵΪx�Ľ�����Ƚ��
            �����ǣ�f(b,x) = true
            ������f(b,x) = false.
        2����f(b,x) Ϊtrueʱ����� b����ֵ
        3. �ݹ�ģ�ͣ�
            ��f(b,x) = false         �� b == NULL
            ��f(b,x) = true          ��b ��������Һ���data��Ϊx
            ��f(b,x) = true          ��f(b->lchild,x) == true ��  f(b->rchild,x) == true
            ��f(b,x) = false         �������
*/

bool ancestor(PBTNode b, ElemType x)
{
    if (b == NULL)
        return false; //�ݹ����
    else if (b->lchild != NULL && b->lchild->data == x || b->rchild != NULL && b->rchild->data == x)
    {
        printf("%c\t", b->data);
        return true; //�ݹ����
    }
    else if (ancestor(b->lchild, x) || ancestor(b->rchild, x)) //�ݹ���
    {
        printf("%c\t", b->data);
        return true;
    }
    else
        return false;
}

/*
    ������Ϊ�������ṹ
    ����Ӹ��ڵ㵽ÿ��Ҷ�ӽ���·���� Ԫ������
    ����ǵݹ��е�ջ�б���ýڵ���������Ƚ�㣬�Ҵ����������
    ˼·��
        1.���ú���ǵݹ��˼·����������Ĳ�������Ϊ�ж��Ƿ���Ҷ�ӽ��
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
            p = NULL;//�����ж�b���Һ����Ƿ���ʹ�
            flag = 1;
            while (top != -1 && flag)
            {
                b = St[top];
                if (b->rchild == p)
                {
                    if (b->lchild == NULL && b->rchild == NULL)
                    { //���ջ������Ԫ��
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
    ��������� ���ڵ㵽Ҷ�ӽ�� ·����  ����
    Ҳ���Բ��÷ǻ��ζ��е�ʵ��
    ˼·��
        1.����һ������ �������ṹ�Ľ�����ͣ��Ҿ��иý���ڶ����е�˫�׽����±�
        2.�����ڵ���ӣ�parent Ϊ -1
        3.�����в���ʱ��ѭ������
            ���жϵ�ǰ����Ƿ�ΪҶ�ӽ�㣬�ǣ������parent��� ��Ҷ�ӽ��������������ڵ�
        4.�ж� �Ƿ������Һ��ӣ�����ֱ����һ��
        5.�ظ�ִ�����ϲ�����ֱ������Ϊ��
*/
void AllPath2(PBTNode b)
{
    struct snode
    {
        BTNode *node; //��ŵ�ǰָ����
        int parent;   //���˫�׽���ڶ��е�λ��
    } qu[MaxSize];
    int front = -1, rear = -1, p; //p��ʱ����˫�׽��λ��
    PBTNode q;                    //��ʱ������׽��
    if (b != NULL)
    {
        rear++;
        qu[rear].node = b;
        qu[rear].parent = -1; //���ڵ����
    }
    while (front != rear)
    {
        front++;            //��ǰ�����ڶ����е��±�
        q = qu[front].node; //���׳���

        //�жϵ�ǰq����Ƿ�ΪҶ�ӽ��
        if (q->lchild == NULL && q->rchild == NULL)
        {
            p = front;
            while (qu[p].parent != -1) //��ǰ��㲻�Ǹ��ڵ�
            {
                printf("%c ->", qu[p].node->data);
                p = qu[p].parent; //pָ����һ��˫��λ��
            }
            printf("%c\n", qu[p].node->data); //������ڵ�
        }
        
        //q����������
        if (q->lchild != NULL)
        {
            rear++;
            qu[rear].node = q->lchild;
            qu[rear].parent = front; //ָ����˫��
        }
        if (q->rchild != NULL)
        {
            qu[++rear].node = q->rchild;
            qu[rear].parent = front;
        }
    }
}

int main(void)
{
    char *str1 = "a(b(d(,g)),c(e,f))";
    char *str2 = "a(b(d(,g)),c(e))";
    BTNode *T, *PT1, *PT2;
    CreateBTNode(&PT1, str1);
    CreateBTNode(&PT2, str2);
    // PBTNode s = FindNode(PT1, 'g');
    // printf("%c",s->data);
    // int height = BTNodeHeight(PT1);
    // DisPBTNode(PT1);
    PreOrder(PT1);
    printf("\n");
    // PreOrder1(PT1);
    // InOrder(PT1);
    // PostOrder(PT1);
    // PostOrder1(PT1);
    // AllPath1(PT1);
    // AllPath2(PT1);
    // LevelOrder(PT1);
    // height = Level(PT1,'c',1);
    // DisLeaf(PT1);
    // bool flag = Like(PT1,PT2);
    ancestor(PT1,'f');
    char *pre = "ABDGCEF";
    char *in = "DGBAECF";
    char *post = "GDBEFCA";
    // T = CreateBT1(pre,in,7);
    // T = CreateBT2(post,in,7);
    // PreOrder(T);
    // CreaThread(PT1);
    getchar();
    getchar();
    return 0;
}