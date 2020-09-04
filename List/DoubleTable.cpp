//  2020年5月25日09:34:53
//双向链表
#include <stdio.h>
#include <malloc.h>
#define ERROR 0;
#define OK 1;
#define TRUE 1;
#define FALSE 0;

typedef int ElemType;
typedef int Status;

typedef struct Node
{
    ElemType data;
    struct Node * prior;//上一结点 地址
    struct Node * next; //下一结点 地址
} doubleList, *pdoubleList;

Status getElem(doubleList L, int i, ElemType *e);
Status listInsert(pdoubleList pL, int i, ElemType e);
Status isEmpty(int i, int j, pdoubleList *p);
void initList(pdoubleList *pL);
void createListF(pdoubleList pL, ElemType a[], int n);

/*
    判断 第i-j个结点是否 存在，并且 保存第i结点的地址，*p
    返回 TRUE，代表第i个元素为空,FALSE 不为空
*/
Status isEmpty(int i, int j, pdoubleList *p)
{
    while (j < i && *p)
    {
        j++;
        *p = (*p)->next;
    }
    if (j > i || !*p)
        return TRUE;
    return FALSE;
}
/*
    获取链表中第i个数据
    思路： 
        1.声明一个结点p指向链表头结点，初始化j 从1开始
        2.当 j < i时，就遍历链表，让p的指针向后移动，不断指向下一结点，j累加
        3.若链表末尾p为空，则说明第i个元素不存在
        4.否则查找成功，返回结点p的数据域
    时间复杂度 为 O(n)
*/
Status getElem(doubleList L, int i, ElemType *e)
{
    int j = 1;             //初始 开始位置
    pdoubleList p = L.next;  //p指向头结点
    if (isEmpty(i, j, &p)) // p 循环 i-1次 p = p->next,最后会指向 第i个元素的前一个
        return ERROR;      //没有找到第i个元素
    *e = p->data;
    return OK;
}

/*
    单链表的第i个数据插入结点
    pL为 单链表的头结点的指针变量，i为插入元素位置，e为待插入的数据
    思路：
        1.声明结点p指向链表的头结点，初始化j = 1
        2.当j < i时，就遍历链表，让p的指针不断后移，j累加
        3.若链表末尾p为空，则说明第i个元素不存在
        4.否则查找成功，在系统中生成一段动态存储空间 s
        5.将数据元素e 赋值为 s->data
        6.双链表的插入标准语句
            s->next = p->next;//新节点后继连接第i个结点
            s->prior = p;//新节点前驱连接 第i-1个结点
            p->next->prior = s;//第i个结点前驱链接 新节点s
            p->next = s;//第i-1个结点后继连接 新节点s
        7.完毕
*/
Status listInsert(pdoubleList *pL, int i, ElemType e)
{
    int j = 1;
    pdoubleList p = (*pL), s; //p指向 头结点
    //查找 第i个元素是否存在
    if (isEmpty(i, j, &p))
        return ERROR;                        //没有找到第i个元素
    s = (pdoubleList)malloc(sizeof(doubleList)); //创建新的动态结点
    s->data = e;
    //插入新节点
    s->next = p->next;//新节点后继连接第i个结点
    s->prior = p;//新节点前驱连接 第i-1个结点
    p->next->prior = s;//第i个结点前驱链接 新节点s
    p->next = s;//第i-1个结点后继连接 新节点s
    return OK;
}

/*
    单链表删除第i个元素
    pL为 头结点，i为 第几个元素，e返回删除的数据
    思路：
        1.声明一结点指向 第一个结点，初始化 j = 1
        2.查找 第i-1个元素是否存在，并且 用p 保存第i-1个元素的地址
        3.进行单链表删除。保存待删除的结点 q = p->next; p = q->next;
        4.释放 q结点 内存空间
        5.完毕
*/
Status listDelete(pdoubleList *pL, int i, ElemType *e)
{
    int j = 1;
    pdoubleList p = (*pL), q; // 第一个结点
    if (isEmpty(i, j, &p))
        return ERROR; //删除元素 不存在
    //删除 第i个结点
    q = p->next;//保存 删除结点
    p->next = q->next;//第i-1结点后驱 连接 第i+1结点
    q->next->prior = p;//第i+1结点前驱连接 第i-1结点
    free(q);
    q = NULL;
    return OK;
}

/*
    初始化一个头结点
*/
void initList(pdoubleList *pL)
{
    *pL = (pdoubleList)malloc(sizeof(doubleList));
    (*pL)->prior = *pL;//上一结点指向自身
    (*pL)->next = *pL;//下一个结点指向其自身
}
/*
    根据数组，建立 单链表（头插法）
    pL头结点，a 为数组首地址，n为 数组长度
    思路：
        1.创建一个头结点 给 pL，和i =1，
        2.循环 遍历 i<n
        3.循环
            ·生成一个新结点 p
            ·将本次循环的 数组中的值给 p->data[i]
            ·将 p插入到头结点 与上一新节点之间
*/
void createListF(pdoubleList *pL, ElemType a[], int n)
{
    initList(&(*pL));
    pdoubleList p;
    for (int i = 0; i < n; i++)
    {
        //生成新的结点p
        p = (pdoubleList)malloc(sizeof(doubleList));
        //赋值

        p->data = a[i];

        p->prior = (*pL);//p的前驱指向头结点
        p->next = (*pL)->next;//p的后继指向第一个结点
        (*pL)->next->prior = p;//旧首节点结点前驱指向 p
        (*pL)->next = p;  //  p称为新的首节点
    }
}

/*
    创建线性表。（尾插法）

    注意结尾时，将头结点的 prior 更换为 最后一个结点

*/
// void createListR(pdoubleList &pL, ElemType a[], int n)
// {
//     pL = (pdoubleList)malloc(sizeof(doubleList));
//     pL->next = pL;
//     pL->prior = pL;
//     pdoubleList p, r = pL,L = pL; //p保存新节点，r指向最后结点,pre指向第一结点
//     for (int i = 0; i < n; i++)
//     {
//         //生成新的结点
//         p = (pdoubleList)malloc(sizeof(doubleList));
//         p->data = a[i];
//         // p->next = NULL;
//         // p->prior = NULL;
//         //新节点插入到最后一位，r重新指向最后一位
//         r->next = p;
//         p->prior = r;
//         r = p;//重新指向最后一位结点
//     }
//     //尾指针next为头结点
//     r->next = pL;
//     pL->prior = r;
// }
void createListR(pdoubleList *pL, ElemType a[], int n)
{
    initList(&(*pL));
    pdoubleList p, r = *pL,L = *pL; //p保存新节点，r指向最后结点,pre指向第一结点
    for (int i = 0; i < n; i++)
    {
        //生成新的结点
        p = (pdoubleList)malloc(sizeof(doubleList));
        p->data = a[i];
        // p->next = NULL;
        // p->prior = NULL;
        //新节点插入到最后一位，r重新指向最后一位
        r->next = p;
        p->prior = r;
        r = p;//重新指向最后一位结点，且下一次循环将p-next域赋值
    }
    //尾指针next为头结点，头结点的前驱为 尾结点
    r->next = *pL;
    (*pL)->prior = r;
}

/*
    打印线性表
    L为头指针
*/
void displayList(pdoubleList L)
{
    pdoubleList p = L->next;
    printf("顺序遍历！\n");
    while (p != L)
    {
        printf("%d\t", p->data);
        p = p->next;
    }
    printf("\n");
}
void displayList1(pdoubleList L)
{
    printf("逆序遍历！\n");
    pdoubleList p = L->prior;
    while (p != L)
    {
        printf("%d\t", p->data);
        p = p->prior;
    }
    printf("\n");
}

/*
    释放pL所指向的单链表
    思路：
        1.声明p，q。p存放待释放结点，q存放下一结点
        2.将第一结点给p
        3.循环：
            ·将下一节点赋给q
            ·释放p
            ·将q 赋给p
*/
Status clearList(pdoubleList *pL)
{
    pdoubleList p, q; //p存放待释放的结点，q存放下一结点
    p = (*pL)->next;
    //当p为空时停止
    while (p)
    {
        /* code */
        q = p->next;
        free(p);
        p = q;
    }
    (*pL)->next = *pL;
    return OK;
}



// 双链表应用示例
/*
    1.有一带头结点的单链表L = {a1,b1,a2,b2...an,bn},设计一个算法将其
    拆分为两个带头结点的单链表L1和L2，L1={a1,a2,an},L2={b1,b2,..bn}.
    要求L1沿用L的头结点
    思路：
        1.L1表 元素为顺序插入，采用尾插法，L2表逆序插入，采用头插法
    
*/
void split(pdoubleList * L,pdoubleList * L1,pdoubleList * L2){
    pdoubleList p = (*L)->next,r1,q;//p 用于循环L表，指向第一个结点，r1用于始终指向L1的尾结点，q用来保存 头插法修改p->next
    *L1 = *L;//L1沿用L的头结点
    r1 = *L1;//始终指向L1尾结点
    *L2 = (pdoubleList)malloc(sizeof(doubleList));//L2建立头结点
    (*L2)->next = NULL; 
    while(p != *L){
        //不要写成*L1， 这样尾插法 的话，会使结点一直插在第一元素， 最后也只有一个结点
        r1->next = p;//尾插法 插入元素p   ai
        r1 = p;//指向 L1尾结点
        
        p = p->next;//移动p指针， data值为 bi
        q = p->next;// 保存因头插法 失去的p->next,  data为 ai

        p->next = (*L2)->next;//头插法，将p插入第一位结点
        (*L2)->next = p;//L2头结点，始终指向新插入结点
        p = q;//p重新指向 ai + 1的结点
    }

    r1->next = NULL;//循环结束后，为尾结点next域赋NULL
}

/*
    删除一个双链表中最大的元素
    思路：
        1.删除一个元素，需要获取其前一位的元素
        2.将第一结点赋给max，p； maxpre 保存max前一结点，pre 保存 p前一结点
        3.循环
            ·依次遍历链表，将max与后每一结点p进行比较，大的结点存入max中
            ·判断是否需要对max赋值，要-》maxpre = pre;
            ·pre = p,p = p->next
*/
void listDeleteMax(pdoubleList * pL){
    pdoubleList maxpre = *pL,max = (*pL)->next,p = (*pL)->next,pre = *pL;
    while(p != *pL){
        //比较大小
        if(max->data < p->data){
            max = p;
            maxpre = pre;
        }
        //将 p指针后移，重置pre
        pre = p;
        p = p->next;
    }
    maxpre->next=maxpre->next->next;
    free(max);
    max = NULL;
}

/*
    双链表由递增排序
    思路：
        1.由于双链表L中有一个以上的数据结点，先构造只含一个数据结点的有序表。
        2.扫描双链表L余下的结点 p( 直到p = NULL)
            pre始终指向 排好序的有序表的头结点，与原单链表中的 p指向的结点比较
            有序表中小于 p结点 则 继续移动指针到下一个，直到大于p结点，或 pre->next == *pL
        3.在有序表中通过比较找插入 p结点的前驱结点 pre
        4.在pre结点之后插入 p结点，直接插入排序法

        2020年5月24日16:32:58， 需要重点复习，初步理解
        头插法，pre相当于移动的头结点，p结点插在其之后

*/
void sort(pdoubleList * pL){

    pdoubleList p,pre,q,L = *pL;
    p = L->next->next;//p指向 L的第二个数据结点
    L->next->next = *pL;//构造只含 一个数据结点的有序表
    while(p != *pL){
        q = p->next;// q保存 p结点后继结点的指针
        pre = L;// 从有序表开头进行比较，pre指向插入 p的前驱结点
        while(pre->next != *pL && pre->next->data < p->data)//循环结束 ，说明 已经找到比p大的结点，pre保存其前驱结点，或者 pre所指有序表均小于p所指结点
            pre = pre->next;//后移pre指针

        //插入动作，p结点大于 pre->next，p结点插入到 pre->next 位置上， pre->next 后移一位，头插法，pre相当于移动的头结点，p结点插在其之后
        //pre->next 必大于 p->next,将其插入到 p结点next域中，pre作为前驱结点链接 p
        p->next = pre->next;//将p插入到 pre之后
        p->prior = pre;//插入元素指向 插入位置元素的前驱
        pre->next->prior = p;//后移结点前驱指向 p
        pre->next = p;
        p = q;//扫描原双链表余下的结点
        // printf("地址：%p",p);
    }
}


//双链表的应用示例

/*
    1.有一双链表L， 设计一算法，将L中所有元素的顺序逆序
    思路：  
        1.先构造一个只包含头结点的双链表（沿用L的头结点）L
            1.1  变量p 指向L的开始结点
        2.通过遍历原链表，使用头插法重新插入
*/
void reverse(pdoubleList * L){
    pdoubleList p = (*L)->next,q;//p指向 L的开始结点，q保存头插法丢失的下一结点
    (*L)->next = *L;//构造一个空结点
    while(p != *L){//扫描L
        q = p->next;//保存下一结点
        //头插法
        p->next = (*L)->next;//将p插入到L的开始结点处
        if((*L)->next != *L){
        }
        (*L)->next->prior = p;//将 原先开始结点前驱指向 新开始结点
        p->prior = *L;//新开始节点前驱指向 头结点
        (*L)->next = p;//头结点后继 指向新开始结点
        p = q;//指向下一结点
    }

}

/*
    2.有一双链表L, 删除 第一个值为 x的 结点
    思路：
        1.寻找 删除结点的前驱结点
        2.删除
*/
Status delElem1(pdoubleList * L,ElemType x){
    pdoubleList p = *L,q;
    while (p->next != (*L) && p->next->data != x)
    {
        /* code */
        p = p->next;//寻找 第一个元素为x的前驱结点
    }
    if(p->next != (*L)){
        q = p->next;//保留 删除结点
        p->next->next->prior = p;
        p->next = q->next;
        free(q);
        q = NULL;
        return OK;
    }
    
    return ERROR;
}
Status delElem2(pdoubleList * L,ElemType x){
    pdoubleList p = (*L)->next;
    while (p != (*L) && p->data != x)
    {
        /* code */
        p = p->next;//寻找 第一个元素为x的结点
    }
    if (p != *L)
    {
        /* code */
        p->next->prior = p->prior;
        p->prior->next = p->next;
        free(p);
        p = NULL;
        return OK;
    }
    

    return ERROR;
}
int main(void)
{
    pdoubleList L,L1,L2;
    pdoubleList& L3 = L;
    ElemType a[] = {11, 20, 33, 4, 5,6,7,8,9,10};
    createListR(&L, a, 10);
    // initList(&L1);
    // initList(&L2);
    // split(&L,&L1,&L2);
    displayList(L);
    reverse(&L);
    // sort(&L);
    // delElem2(&L,10);
    // listDeleteMax(&L);
    // int e;
    // listDelete(&L,10,&e);
    // listInsert(&L, 1, 100);
    displayList(L);
    // displayList(L2);

    getchar();
    return 0;
}