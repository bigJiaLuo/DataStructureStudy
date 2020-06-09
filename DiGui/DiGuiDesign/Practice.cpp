#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef struct release
{
    ElemType data;
    struct release * next;
}linkList,* pLinkList;


/*
    初始化一个头指针
*/
void initList(pLinkList *pL)
{
    *pL = (pLinkList)malloc(sizeof(linkList));
    (*pL)->next = NULL;
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
void createListF(pLinkList *pL, ElemType a[], int n)
{
    initList(&(*pL));
    pLinkList p;
    for (int i = 0; i < n; i++)
    {
        //生成新的结点
        p = (pLinkList)malloc(sizeof(linkList));
        //赋值
        p->data = a[i];
        //插入到上一插入结点之后,包含了NULL，第一个插入的结点，即为尾结点
        p->next = (*pL)->next;
        //插入头结点之后
        (*pL)->next = p;
    }
}
/*
    使用递归计算出 数组a，其中n元素的平均值
    思路：
        1.f（a,n)计算n个元素之和，f(a,n-1)计算n-1个元素之和
                 f(a,n) = a[n-1] + f(a,n-1);
        2.avg = f(a,n) / n
*/
double Avg(ElemType a[],int n){
    if(n == 1)
        return a[0];//递归出口
    else{
        double sum = Avg(a,n-1) + a[n-1];//递归体
        return sum;
    }

}
double Avg1(ElemType a[],int n){
    if(n == 0){
        return a[0];
    }else
    {
        return (a[n]+Avg1(a,n-1)*n) / (n+1);
    }
}

/*
    求以h为头指针的单链表的结点个数
    p:为头指针，指向第一个数据结点
    f(p) 求 n个元素个数，f(p->next) 求n-1个
*/
int length(pLinkList h){
    if(h != NULL){

        return length(h->next)+1;
    }else
    {
        return 0;//递归出口
    }
    
}

/*
    正向显示以h为头指针的单链表的所有结点值
    f(h) 打印 第1元素， f（h->next）打印第2个元素。。
*/
void DueDisp(pLinkList h){
    if(h == NULL)
        return;//递归出口
    else//递归体
    {
        printf("%d\t",h->data);
        DueDisp(h->next);
    }
    
}

/*
    逆向打显示以 h为头指针的单链表的所有结点值
        f(h) 打印第一个元素，f(h->next)第二
*/
void AgainstDisp(pLinkList h){
    if(h == NULL)//递归出口
        return;
    else//递归体
    {
        AgainstDisp(h->next);//直到最后一个元素
        printf("%d\t",h->data);
    }
    
    
}

/*
    删除以h为头结点的单链表 值为 x的 第一个结点
    此版本为带头结点的
    f(h,x) 删除
*/
void deleteElem(pLinkList h,ElemType x){
    pLinkList p;
    //h为待删除的前一个结点
    if(h->next->data == x){//递归出口
        p = h->next;
        h->next = p->next;
        free(p);
        //找到后阻止递归
        return;
    }else if(h == NULL){//递归出口
        return;
    }
    deleteElem(h->next,x);//找值为x的元素
    
}
/*
    删除以h为头指针的单链表中值为x的所有元素
    答案有问题

*/
void DelElemAll(pLinkList * h,ElemType x){
    if(*h == NULL)
        return;
    if((*h)->data == x){
        pLinkList p;
        p = *h;
        *h = (*h)->next;
        free(p);
    }
    DelElemAll(&(*h)->next,x);
    
}

/*
    输出一h为头指针的单链表中最大结点值
    思路：
        1.f(p) 与 f(p->next) 比较大小，得出最大值
        2.f(p->next) 采用相同方法，与 f(p->next->next) 比大小
        3.p->next 为 NULL，返回 p->data，与上一元素比较大小，递归出口
*/
int Max(pLinkList p){
    if(p->next == NULL)
        return p->data;//递归出口
    
    //递归体
    int max = Max(p->next);
    if(max > p->data) return max;
    else return p->data;
}

/*
    输出一个h为头指针单链表中的最小值
    思路：
        1.f(h) 与 f(h->next) 比较大小，得到最小值
        2.相同的，f(h->next) 与 f(h->next->next) 比较得出最小值
        3.p->next 为NULL，返回 p->data,开始与上一元素比较大小，返回最小值
*/
int Min(pLinkList h){
    if(h->next == NULL)
        return h->data;
    
    int min = Min(h->next);//得到最后一个元素的值
    if(min > h->data)//min 与它前面的元素比较
    {
        return h->data;
    }else
    {
        return min;
    }
    
}

/*
    求一个算法求正整数n的位数
    递归模型：
        f(n) = 1   当n < 10时
        f(n) = f(n/10) + 1   其他情况
*/
int count(int n){
    if(n < 10)
        return 1;
    else
        return count(n/10)+1;
}
int main(void){

    ElemType a[] = {1,2,2,4};
    double avg = Avg1(a,3);
    printf("%lf",avg);
    pLinkList p;
    createListF(&p,a,4);

    // int len = length(p->next);//传入头指针
    // printf("%d\n",len);

    // DueDisp(p->next);
    AgainstDisp(p->next);
    // DelElemAll(&(p),2);
    // AgainstDisp(p->next);
    // int max = Max(p->next);
    // printf("%d",max);
    // int min = Min(p->next);
    // printf("%d",min);
    getchar();
    getchar();
    return 0;
}