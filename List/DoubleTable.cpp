//  2020��5��25��09:34:53
//˫������
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
    struct Node * prior;//��һ��� ��ַ
    struct Node * next; //��һ��� ��ַ
} doubleList, *pdoubleList;

Status getElem(doubleList L, int i, ElemType *e);
Status listInsert(pdoubleList pL, int i, ElemType e);
Status isEmpty(int i, int j, pdoubleList *p);
void initList(pdoubleList *pL);
void createListF(pdoubleList pL, ElemType a[], int n);

/*
    �ж� ��i-j������Ƿ� ���ڣ����� �����i���ĵ�ַ��*p
    ���� TRUE�������i��Ԫ��Ϊ��,FALSE ��Ϊ��
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
    ��ȡ�����е�i������
    ˼·�� 
        1.����һ�����pָ������ͷ��㣬��ʼ��j ��1��ʼ
        2.�� j < iʱ���ͱ���������p��ָ������ƶ�������ָ����һ��㣬j�ۼ�
        3.������ĩβpΪ�գ���˵����i��Ԫ�ز�����
        4.������ҳɹ������ؽ��p��������
    ʱ�临�Ӷ� Ϊ O(n)
*/
Status getElem(doubleList L, int i, ElemType *e)
{
    int j = 1;             //��ʼ ��ʼλ��
    pdoubleList p = L.next;  //pָ��ͷ���
    if (isEmpty(i, j, &p)) // p ѭ�� i-1�� p = p->next,����ָ�� ��i��Ԫ�ص�ǰһ��
        return ERROR;      //û���ҵ���i��Ԫ��
    *e = p->data;
    return OK;
}

/*
    ������ĵ�i�����ݲ�����
    pLΪ �������ͷ����ָ�������iΪ����Ԫ��λ�ã�eΪ�����������
    ˼·��
        1.�������pָ�������ͷ��㣬��ʼ��j = 1
        2.��j < iʱ���ͱ���������p��ָ�벻�Ϻ��ƣ�j�ۼ�
        3.������ĩβpΪ�գ���˵����i��Ԫ�ز�����
        4.������ҳɹ�����ϵͳ������һ�ζ�̬�洢�ռ� s
        5.������Ԫ��e ��ֵΪ s->data
        6.˫����Ĳ����׼���
            s->next = p->next;//�½ڵ������ӵ�i�����
            s->prior = p;//�½ڵ�ǰ������ ��i-1�����
            p->next->prior = s;//��i�����ǰ������ �½ڵ�s
            p->next = s;//��i-1����������� �½ڵ�s
        7.���
*/
Status listInsert(pdoubleList *pL, int i, ElemType e)
{
    int j = 1;
    pdoubleList p = (*pL), s; //pָ�� ͷ���
    //���� ��i��Ԫ���Ƿ����
    if (isEmpty(i, j, &p))
        return ERROR;                        //û���ҵ���i��Ԫ��
    s = (pdoubleList)malloc(sizeof(doubleList)); //�����µĶ�̬���
    s->data = e;
    //�����½ڵ�
    s->next = p->next;//�½ڵ������ӵ�i�����
    s->prior = p;//�½ڵ�ǰ������ ��i-1�����
    p->next->prior = s;//��i�����ǰ������ �½ڵ�s
    p->next = s;//��i-1����������� �½ڵ�s
    return OK;
}

/*
    ������ɾ����i��Ԫ��
    pLΪ ͷ��㣬iΪ �ڼ���Ԫ�أ�e����ɾ��������
    ˼·��
        1.����һ���ָ�� ��һ����㣬��ʼ�� j = 1
        2.���� ��i-1��Ԫ���Ƿ���ڣ����� ��p �����i-1��Ԫ�صĵ�ַ
        3.���е�����ɾ���������ɾ���Ľ�� q = p->next; p = q->next;
        4.�ͷ� q��� �ڴ�ռ�
        5.���
*/
Status listDelete(pdoubleList *pL, int i, ElemType *e)
{
    int j = 1;
    pdoubleList p = (*pL), q; // ��һ�����
    if (isEmpty(i, j, &p))
        return ERROR; //ɾ��Ԫ�� ������
    //ɾ�� ��i�����
    q = p->next;//���� ɾ�����
    p->next = q->next;//��i-1������ ���� ��i+1���
    q->next->prior = p;//��i+1���ǰ������ ��i-1���
    free(q);
    q = NULL;
    return OK;
}

/*
    ��ʼ��һ��ͷ���
*/
void initList(pdoubleList *pL)
{
    *pL = (pdoubleList)malloc(sizeof(doubleList));
    (*pL)->prior = *pL;//��һ���ָ������
    (*pL)->next = *pL;//��һ�����ָ��������
}
/*
    �������飬���� ������ͷ�巨��
    pLͷ��㣬a Ϊ�����׵�ַ��nΪ ���鳤��
    ˼·��
        1.����һ��ͷ��� �� pL����i =1��
        2.ѭ�� ���� i<n
        3.ѭ��
            ������һ���½�� p
            ��������ѭ���� �����е�ֵ�� p->data[i]
            ���� p���뵽ͷ��� ����һ�½ڵ�֮��
*/
void createListF(pdoubleList *pL, ElemType a[], int n)
{
    initList(&(*pL));
    pdoubleList p;
    for (int i = 0; i < n; i++)
    {
        //�����µĽ��p
        p = (pdoubleList)malloc(sizeof(doubleList));
        //��ֵ

        p->data = a[i];

        p->prior = (*pL);//p��ǰ��ָ��ͷ���
        p->next = (*pL)->next;//p�ĺ��ָ���һ�����
        (*pL)->next->prior = p;//���׽ڵ���ǰ��ָ�� p
        (*pL)->next = p;  //  p��Ϊ�µ��׽ڵ�
    }
}

/*
    �������Ա���β�巨��

    ע���βʱ����ͷ���� prior ����Ϊ ���һ�����

*/
// void createListR(pdoubleList &pL, ElemType a[], int n)
// {
//     pL = (pdoubleList)malloc(sizeof(doubleList));
//     pL->next = pL;
//     pL->prior = pL;
//     pdoubleList p, r = pL,L = pL; //p�����½ڵ㣬rָ�������,preָ���һ���
//     for (int i = 0; i < n; i++)
//     {
//         //�����µĽ��
//         p = (pdoubleList)malloc(sizeof(doubleList));
//         p->data = a[i];
//         // p->next = NULL;
//         // p->prior = NULL;
//         //�½ڵ���뵽���һλ��r����ָ�����һλ
//         r->next = p;
//         p->prior = r;
//         r = p;//����ָ�����һλ���
//     }
//     //βָ��nextΪͷ���
//     r->next = pL;
//     pL->prior = r;
// }
void createListR(pdoubleList *pL, ElemType a[], int n)
{
    initList(&(*pL));
    pdoubleList p, r = *pL,L = *pL; //p�����½ڵ㣬rָ�������,preָ���һ���
    for (int i = 0; i < n; i++)
    {
        //�����µĽ��
        p = (pdoubleList)malloc(sizeof(doubleList));
        p->data = a[i];
        // p->next = NULL;
        // p->prior = NULL;
        //�½ڵ���뵽���һλ��r����ָ�����һλ
        r->next = p;
        p->prior = r;
        r = p;//����ָ�����һλ��㣬����һ��ѭ����p-next��ֵ
    }
    //βָ��nextΪͷ��㣬ͷ����ǰ��Ϊ β���
    r->next = *pL;
    (*pL)->prior = r;
}

/*
    ��ӡ���Ա�
    LΪͷָ��
*/
void displayList(pdoubleList L)
{
    pdoubleList p = L->next;
    printf("˳�������\n");
    while (p != L)
    {
        printf("%d\t", p->data);
        p = p->next;
    }
    printf("\n");
}
void displayList1(pdoubleList L)
{
    printf("���������\n");
    pdoubleList p = L->prior;
    while (p != L)
    {
        printf("%d\t", p->data);
        p = p->prior;
    }
    printf("\n");
}

/*
    �ͷ�pL��ָ��ĵ�����
    ˼·��
        1.����p��q��p��Ŵ��ͷŽ�㣬q�����һ���
        2.����һ����p
        3.ѭ����
            ������һ�ڵ㸳��q
            ���ͷ�p
            ����q ����p
*/
Status clearList(pdoubleList *pL)
{
    pdoubleList p, q; //p��Ŵ��ͷŵĽ�㣬q�����һ���
    p = (*pL)->next;
    //��pΪ��ʱֹͣ
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



// ˫����Ӧ��ʾ��
/*
    1.��һ��ͷ���ĵ�����L = {a1,b1,a2,b2...an,bn},���һ���㷨����
    ���Ϊ������ͷ���ĵ�����L1��L2��L1={a1,a2,an},L2={b1,b2,..bn}.
    Ҫ��L1����L��ͷ���
    ˼·��
        1.L1�� Ԫ��Ϊ˳����룬����β�巨��L2��������룬����ͷ�巨
    
*/
void split(pdoubleList * L,pdoubleList * L1,pdoubleList * L2){
    pdoubleList p = (*L)->next,r1,q;//p ����ѭ��L��ָ���һ����㣬r1����ʼ��ָ��L1��β��㣬q�������� ͷ�巨�޸�p->next
    *L1 = *L;//L1����L��ͷ���
    r1 = *L1;//ʼ��ָ��L1β���
    *L2 = (pdoubleList)malloc(sizeof(doubleList));//L2����ͷ���
    (*L2)->next = NULL; 
    while(p != *L){
        //��Ҫд��*L1�� ����β�巨 �Ļ�����ʹ���һֱ���ڵ�һԪ�أ� ���Ҳֻ��һ�����
        r1->next = p;//β�巨 ����Ԫ��p   ai
        r1 = p;//ָ�� L1β���
        
        p = p->next;//�ƶ�pָ�룬 dataֵΪ bi
        q = p->next;// ������ͷ�巨 ʧȥ��p->next,  dataΪ ai

        p->next = (*L2)->next;//ͷ�巨����p�����һλ���
        (*L2)->next = p;//L2ͷ��㣬ʼ��ָ���²�����
        p = q;//p����ָ�� ai + 1�Ľ��
    }

    r1->next = NULL;//ѭ��������Ϊβ���next��NULL
}

/*
    ɾ��һ��˫����������Ԫ��
    ˼·��
        1.ɾ��һ��Ԫ�أ���Ҫ��ȡ��ǰһλ��Ԫ��
        2.����һ��㸳��max��p�� maxpre ����maxǰһ��㣬pre ���� pǰһ���
        3.ѭ��
            �����α���������max���ÿһ���p���бȽϣ���Ľ�����max��
            ���ж��Ƿ���Ҫ��max��ֵ��Ҫ-��maxpre = pre;
            ��pre = p,p = p->next
*/
void listDeleteMax(pdoubleList * pL){
    pdoubleList maxpre = *pL,max = (*pL)->next,p = (*pL)->next,pre = *pL;
    while(p != *pL){
        //�Ƚϴ�С
        if(max->data < p->data){
            max = p;
            maxpre = pre;
        }
        //�� pָ����ƣ�����pre
        pre = p;
        p = p->next;
    }
    maxpre->next=maxpre->next->next;
    free(max);
    max = NULL;
}

/*
    ˫�����ɵ�������
    ˼·��
        1.����˫����L����һ�����ϵ����ݽ�㣬�ȹ���ֻ��һ�����ݽ��������
        2.ɨ��˫����L���µĽ�� p( ֱ��p = NULL)
            preʼ��ָ�� �ź����������ͷ��㣬��ԭ�������е� pָ��Ľ��Ƚ�
            �������С�� p��� �� �����ƶ�ָ�뵽��һ����ֱ������p��㣬�� pre->next == *pL
        3.���������ͨ���Ƚ��Ҳ��� p����ǰ����� pre
        4.��pre���֮����� p��㣬ֱ�Ӳ�������

        2020��5��24��16:32:58�� ��Ҫ�ص㸴ϰ���������
        ͷ�巨��pre�൱���ƶ���ͷ��㣬p��������֮��

*/
void sort(pdoubleList * pL){

    pdoubleList p,pre,q,L = *pL;
    p = L->next->next;//pָ�� L�ĵڶ������ݽ��
    L->next->next = *pL;//����ֻ�� һ�����ݽ��������
    while(p != *pL){
        q = p->next;// q���� p����̽���ָ��
        pre = L;// �������ͷ���бȽϣ�preָ����� p��ǰ�����
        while(pre->next != *pL && pre->next->data < p->data)//ѭ������ ��˵�� �Ѿ��ҵ���p��Ľ�㣬pre������ǰ����㣬���� pre��ָ������С��p��ָ���
            pre = pre->next;//����preָ��

        //���붯����p������ pre->next��p�����뵽 pre->next λ���ϣ� pre->next ����һλ��ͷ�巨��pre�൱���ƶ���ͷ��㣬p��������֮��
        //pre->next �ش��� p->next,������뵽 p���next���У�pre��Ϊǰ��������� p
        p->next = pre->next;//��p���뵽 pre֮��
        p->prior = pre;//����Ԫ��ָ�� ����λ��Ԫ�ص�ǰ��
        pre->next->prior = p;//���ƽ��ǰ��ָ�� p
        pre->next = p;
        p = q;//ɨ��ԭ˫�������µĽ��
        // printf("��ַ��%p",p);
    }
}


//˫�����Ӧ��ʾ��

/*
    1.��һ˫����L�� ���һ�㷨����L������Ԫ�ص�˳������
    ˼·��  
        1.�ȹ���һ��ֻ����ͷ����˫��������L��ͷ��㣩L
            1.1  ����p ָ��L�Ŀ�ʼ���
        2.ͨ������ԭ����ʹ��ͷ�巨���²���
*/
void reverse(pdoubleList * L){
    pdoubleList p = (*L)->next,q;//pָ�� L�Ŀ�ʼ��㣬q����ͷ�巨��ʧ����һ���
    (*L)->next = *L;//����һ���ս��
    while(p != *L){//ɨ��L
        q = p->next;//������һ���
        //ͷ�巨
        p->next = (*L)->next;//��p���뵽L�Ŀ�ʼ��㴦
        if((*L)->next != *L){
        }
        (*L)->next->prior = p;//�� ԭ�ȿ�ʼ���ǰ��ָ�� �¿�ʼ���
        p->prior = *L;//�¿�ʼ�ڵ�ǰ��ָ�� ͷ���
        (*L)->next = p;//ͷ����� ָ���¿�ʼ���
        p = q;//ָ����һ���
    }

}

/*
    2.��һ˫����L, ɾ�� ��һ��ֵΪ x�� ���
    ˼·��
        1.Ѱ�� ɾ������ǰ�����
        2.ɾ��
*/
Status delElem1(pdoubleList * L,ElemType x){
    pdoubleList p = *L,q;
    while (p->next != (*L) && p->next->data != x)
    {
        /* code */
        p = p->next;//Ѱ�� ��һ��Ԫ��Ϊx��ǰ�����
    }
    if(p->next != (*L)){
        q = p->next;//���� ɾ�����
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
        p = p->next;//Ѱ�� ��һ��Ԫ��Ϊx�Ľ��
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