#include <stdio.h>
#include <malloc.h>
#define MaxSize 20 //存储空间初始分配量
// 定义 状态代码
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int Status;   // 函数的类型，值为 函数结果状态代码，如：OK
typedef int ElemType; // 默认的元素类型 int ，别名ElemType

typedef struct List
{
    /* data */
    ElemType * data; //包含 默认大小的 ElemType类型数组
    int length;     // 线性表长度
} SqList;

/*
    初始化线性表
    思路：
        重新分配一段空间，并设长度为0
*/
Status initList(SqList *pL)
{
    pL->data = (ElemType *)malloc(MaxSize * sizeof(ElemType));
    if (!pL->data)
        return ERROR;
    (pL)->length = 0;
    return OK;
}

/*
    创建顺序线性表
    思路：
        1.遍历数组a
        2.逐一进行赋值
    pL线性表的指针，a为 创建线性表提供的数组，n为 数组长度
*/
Status createList(SqList *pL, ElemType a[], int n)
{
    if (!pL || !a)
    {
        return ERROR;
    }
    initList(pL);
    for (int i = 0; i < n; i++)
    {
        pL->data[i] = a[i];
        pL->length++;
    }
    return OK;
}

/*
    销毁线性表
    结果：释放线性表pL所占用的内存空间
*/
Status destroyList(void **pL)
{
    if (*pL != NULL)
    {
        free(*pL);
        *pL = NULL;
    }

    return OK;
}

/*
    判断是否是空表
    思路：
        判断线性表的长度是否为0
    true 为空表，false 不是空表
*/
Status ListEmpty(SqList l)
{
    if (l.length <= 0)
        return true;
    return false;
}

/*
    求 线性表的长度
*/
int listLength(SqList l)
{

    return l.length;
}

/*
    输出线性表
    思路： 以线性表的长度为 判断条件，逐个输出
*/
Status displayList(SqList l)
{
    if (l.length <= 0)
        return ERROR;
    for (int i = 0; i < l.length; i++)
    {
        // 每输出10个数 ，换行
        if (i % 9 == 0 && i != 0)
            printf("\n");
        printf("%d\t", l.data[i]);
    }
    printf("\n");
    return true;
}

/*
    获取线性表中的 第 i个元素，使用 e 来返回 其值，Status 返回函数结果状态
    第i个元素 在数组中 的下标为 i-1
*/
Status getElem(SqList sqlist, int i, ElemType *e)
{
    // 判断i值是否合法
    if (sqlist.length == 0 || i < 1 || i > sqlist.length)
    {
        return FALSE;
    }
    *e = sqlist.data[i - 1];
    return TRUE;
}
/*
    按元素数值查找线性表，返回该值的逻辑序号
    思路：
        1.首先遍历这个线性表
        2.判断表中第一个与 该数值匹配的元素，并记录其逻辑序号返回
    结果：存在返回逻辑序号，不存在返回 0；
*/
int locateElem(SqList l, ElemType e)
{
    for (int i = 0; i < l.length; i++)
    {
        if (l.data[i] == e)
        {
            return i + 1;
        }
    }
    return 0;
}

/*
    插入算法的思路：
        1.如果插入的位置不合理，抛出异常
        2.如果线性表长度大于等于数组长度，则抛出异常或动态增加容量；
        3.从最后一个元素开始向前遍历到第i个位置，分别将它们都向后移动一个位置
        4.将要插入元素填入 位置i处
        5.表长加1
        pl线性表，i 插入位置，e插入元素
*/
Status listInsert(SqList *pL, int i, ElemType e)
{
    if (i < 1 || i > pL->length + 1) //当i不在线性表范围
        return ERROR;
    if (pL->length >= MaxSize) //顺序线性表长度已经满了
        return ERROR;
    if (i <= pL->length) //判断 插入位置是否在表尾
    {
        // 否
        for (int k = pL->length - 1; k >= i - 1; k--) //将i位置以及之后的元素都向后移一位
        {
            pL->data[k + 1] = pL->data[k];
        }
    }
    // 最后将 元素插入到 对应i 位置,表长加1
    pL->data[i - 1] = e;
    pL->length++;
    return OK;
}

/*
    删除算法思路：
        1.如果删除的位置不合理，抛出异常
        2.存储待删除的元素
        3.将删除位置i之后的元素都向前移一位
        4.表长减一
    pl线性表，i 删除位置，e 返回删除元素
*/
Status listDelete(SqList *pL, int i, ElemType *e)
{
    if (i < 1 || i > pL->length) //删除位置不合法
        return ERROR;
    if (pL->length == 0) //线性表为空
        return ERROR;
    *e = pL->data[i - 1];
    if (i < pL->length) //是否删除的是末尾元素
    {
        // 否
        for (int k = i; k < pL->length; k++)
        {
            pL->data[k - 1] = pL->data[k];
        }
    }
    pL->length--;
    return OK;
}

/*
    顺序表的应用
    1.解法一：删除顺序表中所有等于x 的元素，时间复杂度为 O（n）
    思路：
        1.删除所有等于x元素后的顺序表为L1，L1为L的子集
        2.判定那些元素不为x，将其逐一加入L1表
        3.L1重用L的空间
*/
void deleteNode1(SqList *pL, ElemType x)
{
    int k = 0; //记录包含新表元素的个数
    for (int i = 0; i < pL->length; i++)
    {
        if (pL->data[i] != x)
        {
            pL->data[k] = pL->data[i];
            k++;
        }
    }
    pL->length = k; //新表长度
    return;
}

/*
    1.解法二：
        思路：
            1.使用k来统计 元素为x的个数
            2.遍历L表一边统计k值
            3.将不为k值的元素向前移 k位
*/
void deleteNode2(SqList *pL, ElemType x)
{
    int k = 0;
    for (int i = 0; i < pL->length; i++)
    {
        if (pL->data[i] == x)
        {
            k++; //计数
        }
        else
        {
            //前移k个位置
            pL->data[i - k] = pL->data[i];
        }
    }
    pL->length -= k; //新表长度

    return;
}

/*
    交换a和b的值
*/
void swap(ElemType *a, ElemType *b)
{
    ElemType temp;
    temp = *a;
    *a = *b;
    *b = temp;
    return;
}
/*
    2.有一顺序表，以第一元素为分界线，将所有 小于等于 它的元素移到它前面，将 所有大于 它的元素移到它后面
        注意:
    解法一：
        思路： 
            1.用pivot存放基准，p->data[0]，用户i，j分别指向L的第一个元素和最后一个元素
            2.当i<j时循环
                从右向左循环，找到一个关键字小于等于pivot的data[j]，再
                从左向右循环，找到关键字大于pivot的记录data[i]
                将两者互换
            3.循环结束后，将data[0]基准和data[j] 互换
*/
void move1(SqList *pL)
{
    int i = 0, j = pL->length - 1; //最大最小下标
    ElemType pivot = pL->data[0];  //基准
    while (i < j)
    {
        while (i < j && pL->data[j] > pivot)
        {
            j--; //j指向  小于等于pivot的 pL->data[j]，保存比基准小的 元素下标
        }
        while (i < j && pL->data[i] <= pivot)
        {
            i++;//保存比基准 大 的 元素下标
        }
        if (i < j)
        {
            swap(&pL->data[i], &pL->data[j]); //交换i，j所指向的元素的值
        }
    }
    // 交换 data[0] 和 data[j]，基准与比基准小的元素互换
    swap(&pL->data[0], &pL->data[j]);
    printf("i = %d\n", i);
    return;
}

/*
    2. 解法二：
        思路：
            1.将基准 pL->data[0] 存入 pivot
            2.i，j分别记录 最小，最大下标
            3.循环条件， i < j, 
                从右向左循环，找到比 pivot 大的元素 pL->data[j], 将 该值覆盖 pL->data[i].
                    之后 j 不变，i自增1
                从左向右循环，找到比pivot 小等于的元素 pL->data[i],将 该值 覆盖 pL->data[j]
                    之后 i 值不变，j自增1
            j 下标之后的元素都大于 pivot，最后一次覆盖后，j本身代表的位置就是 中间值，基准的位置
            4.最后 将 pivot 覆盖 pL->data[j], 基准位于中间值
*/
void move2(SqList *pL)
{
    ElemType pivot = pL->data[0];  //基准
    int i = 0, j = pL->length - 1; // 最小，最大下标
    while (i  < j)//最后i，j
    {
        //从右向左 循环
        while (i < j && pL->data[j] > pivot)
        {
            j--;
        }
        pL->data[i] = pL->data[j];
        i++;
        //从左向右 循环
        while (i < j && pL->data[i] <= pivot)
        {
            i++;
        }
        pL->data[j] = pL->data[i];
        j--;
    }
    //最后指向原先 j所指的 下标位置，这个位置之后的元素都大于基准，且已经赋值给其他下标，将基准赋给该位置 
     pL->data[j] = pivot;
    printf("i = %d,j = %d\n", i, j);
    return;
}

int main(void)
{
    SqList L1, *pL1;
    pL1 = &L1;
    // int a[] = {4, 2, 3, 4, 6};
    int a[] = {3,8,2,7,1,5,3,4,6,0};
    // 3,8,2,7,1,5,3,4,6,0
    createList(&L1, a, 10);
    displayList(L1);
    move2(&L1);
    // deleteNode2(&L1, 2);
    displayList(L1);

    destroyList((void **)&L1.data);
    getchar();
    return 0;
}