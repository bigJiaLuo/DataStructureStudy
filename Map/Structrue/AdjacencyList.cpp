/*
    �ڽӱ�
    ʱ�䣺2020��6��15��20:35:21
    ���ߣ���
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
    EdgeNode *firstedg; //����ָ��߱��ͷ
} VertexNode, AdjList[MAXV];

//ͼ���ڽӱ�
typedef struct
{
    AdjList adjList;         //�ڽӱ�
    int numVertex, numEdges; //ͼ�ж�����������
} GraphAdjList;

/*
    ʹ���ڽӱ� ����һ������ͼ������Ȩ
*/
void CreateALGraph(GraphAdjList *G)
{
    int i, j, k; //iΪ��㣬jΪ�յ�
    EdgeNode *e; //��ʱ�������ڽӵ�
    printf("����������ͼ�Ķ��������������");
    scanf("%d %d", &G->numVertex, &G->numEdges);
    //��ʼ�������
    for (i = 0; i < G->numVertex; i++)
    {

        printf("�����%d��������:", i + 1);
        scanf("%d", &G->adjList[i].data);
        G->adjList[i].firstedg = NULL; //�߱���Ϊ��
    }
    //�����ߣ������߱�
    for (k = 0; k < G->numEdges; k++)
    {
        printf("�����루vi��vj���϶������ţ�");
        scanf("%d %d", &i, &j);

        //ͷ�巨
        //�����µ��ڽӵ㣬iΪ���㣬jΪ�ڽӵ�
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = j; //�ڽ����Ϊj
        e->next = G->adjList[i].firstedg;
        G->adjList[i].firstedg = e;

        //�����µ��ڽӵ㣬jΪ���㣬iΪ�ڽӵ�
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = i;
        e->next = G->adjList[j].firstedg;
        G->adjList[j].firstedg = e;
    }
}

bool visited[MAXV];//��ʶ�˶����Ƿ񱻷���
/*
    �ڽӱ��������ȱ���
    ˼·��
        1.������v���������visited[v]��Ϊ�ѷ���
        2.���� ͼ�ж�����б߱�ĵ�һ���ڽӵ�
        3.�жϸ��ڽӵ��Ƿ��ѷ���
        4.�Ը��ڽӵ�ʹ��DFS���γɵݹ�
        5.����ݹ��Լ����ж� ����v�Ƿ���δ���ʵ��ڽӵ㣬��������ݹ�
      ʱ�临�Ӷȣ�O(n+e) ���㣬����
*/
void DFS(GraphAdjList G,int v){
    EdgeNode * p;//�����߱�
    visited[v] = 1;//��Ϊ�ѷ���
    printf("%d\t",G.adjList[v].data);//�����ǰ����
    p = G.adjList[v].firstedg;//pָ�� v����ĵ�һ���ڽӵ�
    while (p)
    {
        if(!visited[p->adjvex])//�жϸ��ڽӵ��Ƿ񱻷���
            DFS(G,p->adjvex);//�Դ��ڽӵ� ����DFS
        p = p->next;//pָ�� ����v����һ���ڽӵ�
    }
    
}

/*
    �ڽӱ�Ĺ�����ȱ���
    ˼·��
        1.����ѭ������
        2.��������г�ʼ��
        3.���ʳ�ʼ���㣬����ӣ�����Ϊ�ѷ���
        4.ջ����
            �����ӣ����㸳ֵΪ=��w
            ��pָ��w����ĵ�һ���ڽӵ���
            ��ѭ����p��
                ���ж� p�ڽӵ��Ƿ񱻷��ʣ���ѭ����p���Ͷ�p�Ƿ���ڽ����жϣ��������ж�
                    ��true������ڽӵ㣬��ӣ���Ϊ�ѷ���
                ��p����
*/
void BFS(GraphAdjList G,int v){
    //1
    EdgeNode * p;
    int queue[MAXV],rear = 0,front = 0;
    int w,i;
    //2
    for ( i = 0; i < G.numVertex; i++)
    {
        visited[i] = 0;
    }
    //3
    printf("%2d",G.adjList[v].data);
    visited[v] = 1;
    rear = (rear+1) % MAXV;
    queue[rear] = v;
    //4
    while (rear != front)
    {
        //����
        front = (front+1) % MAXV;
        w = queue[front];
        //ָ��ջ��������ĵ�һ���ڽӵ�
        p = G.adjList[w].firstedg;
        while (p)
        {
            if (!visited[p->adjvex])//�ö����Ƿ��ѷ���
            {
                //�������ӣ���Ϊ�ѷ���
                printf("%2d",p->adjvex);
                visited[p->adjvex] = 1;
                rear = (rear+1) % MAXV;
                queue[rear] = p->adjvex;
            }
            p = p->next;//pָ��ջ�����������һ���ڽӵ�
        }
        
    }
    
    

}

int main(void)
{

    GraphAdjList G;
    CreateALGraph(&G);
    // DFS(G,0);
    BFS(G,0);
    getchar();
    getchar();
    return 0;
}