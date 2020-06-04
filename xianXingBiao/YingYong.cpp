/*
    ��������������ļ���Ȼ���ӡ�
    ����������ֻҪ i = j���� 
    ��1             ��2
    123             35
    233             16
    111             34

�����
    12335
    12334
    23335
    11116
*/

#include <stdio.h>
#include <malloc.h>
#define MaxCol 10//�������
typedef int ElemType;
//���ݽ������
typedef struct Node1{
    ElemType data[MaxCol];//���һ�е�����
    struct Node1 * next;//��ź�����ݽ��
}DList,* PDList;//������

//ͷ�������
typedef struct Node2{
    int Row,Col; //����
    DList * next;//ָ���һ�����ݽ��

}HList,* PHList;

/*
    �������ݽ��

        // ���� �ڲ�ͨ��h��������̬�ռ䣬��û��ֱ�Ӷ�H���в����������ж�H��ֵ
*/
void createTable(PHList * H){
    int i,j;
    PHList h;
    PDList s,r;
    h = (PHList)malloc(sizeof(HList));//����ͷ���
    h->next = NULL;
    printf("���������������");
    scanf("%d%d",&h->Row,&h->Col);//��������
    for(i = 0; i < h->Row; i++){//������������
        printf("��%d�У�",i+1);
        s = (PDList)malloc(sizeof(DList));
        for(j =  0; j < h->Col; j++){//����һ�е�����
            scanf("%d",&s->data[j]);
        }
        if(h->next == NULL)//�����һ�����ݽ��
            h->next = s;
        else
            r->next = s;//�� *s�����뵽 *r֮��
        r = s;
    }
    r->next = NULL;
    // ���� �ڲ�ͨ��h��������̬�ռ䣬��û��ֱ�Ӷ�H���в����������ж�H��ֵ
    *H = h;
}
/*
    �ͷŵ�����
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
    ���������
*/
void dispTable(PHList h){
    int j;
    DList * p = h->next;//ָ��ʼ���
    while(p!=NULL){
        for(j = 0; j < h->Col; j++){
            printf("%d\t",p->data[j]);
        }
        printf("\n");
        p = p->next;// ָ����һ�н��
    }
}


/*
    ������
    ˼·��
        1.���������������ӵ������i��j
        2.ɨ�赥����h1.
            2.1��h1ÿ����㣬 ��ͷ��βɨ�赥����h2,
            2.2���������������� data[i-1] = data[j-1]
            2.3�����½�������h�����һ���½�㡣
        �½�������Ҳ����β�巨����
*/
void LinkTable(PHList * h1,PHList * h2,PHList * h){
    int i,j,k;
    DList * p = (*h1)->next,*q,*s,*r;//pָ��h1��ʼ���
    printf("�����ֶ��ǣ���1������ţ��ڶ�������ţ�");
    scanf("%d %d",&i,&j);
    (*h) = (PHList)malloc(sizeof(HList));//����ͷ���
    (*h)->Row = 0;//
    (*h)->Col = (*h1)->Col+(*h2)->Col;
    (*h)->next = NULL;

    while(p){//ɨ�� h1
        q = (*h2)->next;//ÿ�ζ�ָ�� h2��ʼ���
        while(q){
            if(p->data[i-1] == q->data[j-1]){//��Ȼ���� ��������,����һ������
                s = (PDList)malloc(sizeof(DList));
                for(k = 0; k < (*h1)->Col; k++){
                    s->data[k] = p->data[k];//��ֵ
                }
                for(k = 0; k < (*h2)->Col; k++){
                    s->data[(*h1)->Col+k] = q->data[k];//h1����� ����k�������ӱ�h2��s���±�
                }
                //β�巨
                if((*h)->next == NULL)
                    (*h)->next = s;//ͷ��� ����ָ��ʼ���󣬽���r����ɺ���ָ��
                else
                    r->next = s;
                r = s;//ʼ��ָ�����ս��
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