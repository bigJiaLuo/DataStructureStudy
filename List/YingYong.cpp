/*
    计算任意两个表的简单自然连接。
    连接条件，只要 i = j，即 
    表1             表2
    123             35
    233             16
    111             34

结果：
    12335
    12334
    23335
    11116
*/

#include <stdio.h>
#include <malloc.h>
#define MaxCol 10//最大行数
typedef int ElemType;
//数据结点类型
typedef struct Node1{
    ElemType data[MaxCol];//存放一行的数据
    struct Node1 * next;//存放后继数据结点
}DList,* PDList;//行类型

//头结点类型
typedef struct Node2{
    int Row,Col; //行列
    DList * next;//指向第一个数据结点

}HList,* PHList;

/*
    创建数据结点

        // 由于 内部通过h来创建动态空间，并没有直接对H进行操作，最后进行对H赋值
*/
void createTable(PHList * H){
    int i,j;
    PHList h;
    PDList s,r;
    h = (PHList)malloc(sizeof(HList));//创建头结点
    h->next = NULL;
    printf("表的行数，列数：");
    scanf("%d%d",&h->Row,&h->Col);//输入行列
    for(i = 0; i < h->Row; i++){//输入所有数据
        printf("第%d行：",i+1);
        s = (PDList)malloc(sizeof(DList));
        for(j =  0; j < h->Col; j++){//输入一行的数据
            scanf("%d",&s->data[j]);
        }
        if(h->next == NULL)//插入第一个数据结点
            h->next = s;
        else
            r->next = s;//将 *s结点插入到 *r之后
        r = s;
    }
    r->next = NULL;
    // 由于 内部通过h来创建动态空间，并没有直接对H进行操作，最后进行对H赋值
    *H = h;
}
/*
    释放单链表
*/
void destroryTable(PHList * h){
    PDList pre = (*h)->next,p = pre->next;
    while(p != NULL){
        free(pre);
        pre = p;
        p = p->next;
    }
    free(pre);
    free(*h);
}


/*
    输出单链表
*/
void dispTable(PHList h){
    int j;
    DList * p = h->next;//指向开始结点
    while(p!=NULL){
        for(j = 0; j < h->Col; j++){
            printf("%d\t",p->data[j]);
        }
        printf("\n");
        p = p->next;// 指向下一行结点
    }
}


/*
    表连接
    思路：
        1.先输入两个表连接的列序号i和j
        2.扫描单链表h1.
            2.1对h1每个结点， 从头到尾扫描单链表h2,
            2.2若连接条件成立， data[i-1] = data[j-1]
            2.3则在新建单链表h中添加一个新结点。
        新建单链表也采用尾插法建立
*/
void LinkTable(PHList * h1,PHList * h2,PHList * h){
    int i,j,k;
    DList * p = (*h1)->next,*q,*s,*r;//p指向h1开始结点
    printf("连接字段是：第1个表序号，第二个表序号：");
    scanf("%d %d",&i,&j);
    (*h) = (PHList)malloc(sizeof(HList));//建立头结点
    (*h)->Row = 0;//
    (*h)->Col = (*h1)->Col+(*h2)->Col;
    (*h)->next = NULL;

    while(p){//扫描 h1
        q = (*h2)->next;//每次都指向 h2开始结点
        while(q){
            if(p->data[i-1] == q->data[j-1]){//自然连接 条件成立,增加一行数据
                s = (PDList)malloc(sizeof(DList));
                for(k = 0; k < (*h1)->Col; k++){
                    s->data[k] = p->data[k];//赋值
                }
                for(k = 0; k < (*h2)->Col; k++){
                    s->data[(*h1)->Col+k] = q->data[k];//h1表的列 加上k就是连接表h2的s的下标
                }
                //尾插法
                if((*h)->next == NULL)
                    (*h)->next = s;//头结点 后驱指向开始结点后，交由r来完成后面指向
                else
                    r->next = s;
                r = s;//始终指向最终结点
                (*h)->Row++;
            }
            q = q->next;
        }
        p = p->next;
    }
    r->next = NULL;

}

int main(void){
    PHList h,h1,h2;
    createTable(&h1);
    createTable(&h2);
    dispTable(h1);
    dispTable(h2);
    LinkTable(&h1,&h2,&h);
    dispTable(h);
    // destroryTable(&h);

    // dispTable(h);
    getchar();
    getchar();
    return 0;
}