/*
    ��������
    ʱ�䣺2020��9��2��10:23:51
    ���ߣ����ing
*/

#include <stdio.h>
#include <malloc.h>
#define MAXV 10       //��󶥵���
typedef int EdgeType; //����Ȩֵ����

typedef int VertexType; //��������

//�߱�����
typedef struct EdgeNode
{
    int adjvex;            //���ڽӵ��򣬴洢�ö�����±�
    EdgeType weight;       //�ô洢���㵽�ö�����ϵ�Ȩֵ������ͼ����Ҫ
    struct EdgeNode *next; //����ָ����һ��������ڽӵ�
} EdgeNode;

//���������
typedef struct VertexNode
{
    VertexType data;    //�����򣬶�����Ϣ
    int inCount;//��������
    EdgeNode *firstedg; //����ָ��߱��ͷ
} VertexNode, AdjList[MAXV];

//�ڽӱ�����
typedef struct ALGragh
{
    AdjList adjList;//�߱�����
    int vertex,edges;//������������
}ALGragh;


void topSort(ALGragh * G){
    //1.ջSt��ָ��Ϊtop
    int i,j;
    int St[MAXV],top = -1;
    EdgeNode * p;
    //2.�����Ϊ0
    for ( i = 0; i < G->vertex; i++)
    {
        G->adjList[i].inCount = 0;
    }
    // 3.�����ж�������
    for ( i = 0; i < G->vertex; i++)
    {
        p = G->adjList[i].firstedg;
        while(p != NULL){
            G->adjList[p->adjvex].inCount++;//p->adjvexΪ i�����
            p = p->next;//pָ����һ���ڽӵ�
        }
    }
    //4.���Ϊ0�Ķ����ջ
    for ( i = 0; i < G->vertex; i++)
    {
        if(G->adjList[i].inCount == 0){
            top++;
            St[top] = i;
        }
    }

    //5.�����������
    while(top > -1){
        i = St[top--];
        printf("%d ",i);
        p = G->adjList[i].firstedg;//�ҵ�����i�ĵ�һ���ڽӵ�
        //��i�����е��ڽӵ����ȼ�һ
        while (p != NULL)
        {
            j = p->adjvex;
            G->adjList[j].inCount--;
            //�����һ�����Ϊ0������ջ
            if (G->adjList[j].inCount == 0)
            {
                St[++top] = j;
            }
            p = p->next;
        }
        
    }
}

void CreateALGraph1(ALGragh *G)
{
    int i, j, k; //iΪ��㣬jΪ�յ�
    EdgeNode *e; //��ʱ�������ڽӵ�
    printf("����������ͼ�Ķ��������������");
    scanf("%d %d", &G->vertex, &G->edges);
    //��ʼ�������
    for (i = 0; i < G->vertex; i++)
    {

        printf("�����%d��������:", i + 1);
        scanf("%d", &G->adjList[i].data);
        G->adjList[i].firstedg = NULL; //�߱���Ϊ��
    }
    //�����ߣ������߱�
    for (k = 0; k < G->edges; k++)
    {
        printf("�����루vi��vj���϶������ţ�");
        scanf("%d %d", &i, &j);

        //ͷ�巨
        //�����µ��ڽӵ㣬iΪ���㣬jΪ�ڽӵ�
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = j; //�ڽ����Ϊj
        e->next = G->adjList[i].firstedg;
        G->adjList[i].firstedg = e;
    }
}


int *etv,*ltv;//�¼����緢��ʱ�����ٷ���ʱ������
int *stack2;//���ڴ洢���������ջ
int top2;//����stack2��ջ��ָ��
/*
    �����������ڹؼ�·������
*/
bool TopologicalSort(ALGragh * G){
    EdgeNode * e;
    int i,k,gettop;
    int count;//�����ѽ����������򶥵�ĸ���

    int top = 0;int count = 0;int * stack;//top����ջ��
    stack = (int *)malloc(G->vertex * sizeof(int));
    //���������Ϊ0�Ķ�����ջ
    for ( i = 0; i < G->vertex; i++)
    {
        if(0 == G->adjList[i].inCount)
            stack[++top] = i;
    }
    top2 = 0;//��ʼ��Ϊ0
    etv = (int *)malloc(G->vertex * sizeof(int));
    //��ʼ���¼����緢��ʱ��
    for ( i = 0; i < G->vertex; i++)
    {
        etv[i] = 0;
    }
    stack2 = (int *)malloc(G->vertex * sizeof(int));
    
    //������������ջ���������Ӧ�������¼�����ʱ��
    while (top != 0)
    {
        gettop = stack[top--];
        count++;
        stack2[++top2] = gettop;//�������Ķ�������ѹ���������е�ջ

        for ( e = G->adjList[gettop].firstedg; e; e = e->next)
        {
            k = e->adjvex;
            //e������ڽӵ���ȶ���һ�����������Ϊ0��Ԫ����ջ
            if (0 == (--G->adjList[k].inCount))
                stack[++top] = k;
            //������ж������緢��ʱ�䣬��������·��������Ҫǰ���ջ���αȽϳ����ֵ�����и�ֵ
            if (etv[gettop]+e->weight > etv[k])
                etv[k] = etv[gettop]+e->weight;
        }
    }

    //���������ж������������ԭ������������ڻ�·
    if(count < G->vertex)
        return false;
    else
        return true;
}

/*
    ��ؼ�·����GΪ�����������G�ĸ���ؼ��
*/
void CriticalPath(ALGragh *G){
    EdgeNode * e;
    int i,gettop,k,j;
    int ete,lte;//��������緢������ٷ���ʱ�����
    TopologicalSort(G);//����������У���������etv��stack2��ֵ
    ltv = (int *)malloc(G->vertex * sizeof(int));//�¼�������ʱ��
    for ( i = 0; i < G->vertex; i++)
    {
        ltv[i] = etv[G->vertex-1];//��ʼ��ltv
    }
    while (top2 != 0)//����ltv
    {
        gettop = stack2[top2--];//���������г�ջ������ȳ�
        for ( e = G->adjList[gettop].firstedg; e; e = e->next)
        {
            //��������¼���ٷ���ʱ��ltv
            k = e->adjvex;
            if (ltv[k]-e->weight < ltv[gettop])
            {
                ltv[gettop] = ltv[k]-e->weight;
            }
        }
        
        //��etv��lte�͹ؼ��
        for ( i = 0; i < G->vertex; i++)
        {
            for (e = G->adjList[j].firstedg; e; e = e->next)
            {
                k = e->adjvex;
                ete = etv[j];//����緢��ʱ��
                lte = ltv[k] - e->weight;//�������ʱ��
                if (ete == lte)
                {
                    printf("<v%d,v%d> length: %d,",G->adjList[j].data,G->adjList[k].data,e->weight);
                }
            }
            
        }
        

    }

}

int main(void){
    ALGragh G;
    CreateALGraph1(&G);
    topSort(&G);

    getchar();
    getchar();
    return 0;
}