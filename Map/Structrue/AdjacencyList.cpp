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

void CreateALGraph1(GraphAdjList *G)
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
    }
}

bool visited[MAXV]; //��ʶ�˶����Ƿ񱻷���
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
void DFS(GraphAdjList G, int v)
{
    EdgeNode *p;                       //�����߱�
    visited[v] = 1;                    //��Ϊ�ѷ���
    printf("%d\t", G.adjList[v].data); //�����ǰ����
    p = G.adjList[v].firstedg;         //pָ�� v����ĵ�һ���ڽӵ�
    while (p)
    {
        if (!visited[p->adjvex]) //�жϸ��ڽӵ��Ƿ񱻷���
            DFS(G, p->adjvex);   //�Դ��ڽӵ� ����DFS
        p = p->next;             //pָ�� ����v����һ���ڽӵ�
    }
}

/*
    �ڽӱ�Ĺ�����ȱ���
    ˼·��
        1.����ѭ������
        2.��visited������г�ʼ��
        3.���ʳ�ʼ���㣬����ӣ�����Ϊ�ѷ���
        4.ջ����ѭ��
            �����ӣ����㸳ֵ��w
            ��pָ��w����ĵ�һ���ڽӵ���
            ��ѭ����p��
                ���ж� p��ÿһ���ڽӵ��Ƿ񱻷��ʣ�   ע����ѭ����p���Ͷ�p�Ƿ���ڽ����жϣ��������ж�
                    ��true������ڽӵ㣬��ӣ���Ϊ�ѷ���
                ��p����
*/
void BFS(GraphAdjList G, int v)
{
    //1
    EdgeNode *p;
    int queue[MAXV], rear = 0, front = 0;
    int w, i;
    //2
    for (i = 0; i < G.numVertex; i++)
    {
        visited[i] = 0;
    }
    //3
    printf("%2d", G.adjList[v].data);
    visited[v] = 1;
    rear = (rear + 1) % MAXV;
    queue[rear] = v;
    //4
    while (rear != front)
    {
        //����
        front = (front + 1) % MAXV;
        w = queue[front];
        //pָ��ջ��������w�ĵ�һ���ڽӵ�
        p = G.adjList[w].firstedg;
        while (p)
        {
            if (!visited[p->adjvex]) //�ö����Ƿ��ѷ���
            {
                //�������ӣ���Ϊ�ѷ���
                printf("%2d", p->adjvex);
                visited[p->adjvex] = 1;
                rear = (rear + 1) % MAXV;
                queue[rear] = p->adjvex;
            }
            p = p->next; //pָ��ջ�����������һ���ڽӵ�
        }
    }
}

//Ӧ��
/*
    �ж�ͼG�Ƿ�Ϊ��ͨͼ
    ˼·��
        0.��ʼ��visited
        1.�Ը�ͼ����һ����ȱ���
        2.�ٶԸ�ͼ�����ж����жϣ�visited�Ƿ�Ϊ1
            ��1����ͨ
            ��0������ͨ
*/
bool connect(GraphAdjList G)
{
    bool flag;
    //1
    for (int i = 0; i < G.numVertex; i++)
    {
        visited[i] = 0;
    }

    //2
    DFS(G, 0);
    for (int i = 0; i < G.numVertex; i++)
    {
        //�Ƿ��ѷ���
        if (visited[i] != 1)
        {
            flag = false;
            break;
        }
    }
    return flag;
}
/*
    �ڽӱ��ж� ����u ������ v�Ƿ���ڼ�·��
    ˼·��
        1.����ȱ����Ļ����ϼ��� u����v��������
        2.�ж�u == v ������ has ��Ϊ�Ƿ���ڼ�·����ʶ
*/
void ExistPath(GraphAdjList G, int u, int v, bool *has)
{
    // int w;  //��ʱ��Ŷ���
    EdgeNode *p; //�����ڽӵ�
    //���ɶ�visited�����ʼ��,����visited��Ϊ0
    visited[u] = 1; //��Ϊ�ѷ���
    if (u == v)     //˵���ӿ�ʼu���㣬һֱ����·�����ʵ�v��������һ��·��
    {
        *has = true;
        return;
    }

    p = G.adjList[u].firstedg; //pָ�򶥵�u�ĵ�һ���ڽӵ�

    while (p) //����p��ÿһ���ڽӵ�
    {
        if (!visited[p->adjvex])
        {
            ExistPath(G, p->adjvex, v, has);
        }
        p = p->next;
    }
}

/*
    �ڽӱ�,���ͼG�� �Ӷ���u������v��һ����·��
    ˼·:
        1.����ͼ��������ȱ���,���������β�,v,path,d�� ÿһ��ݹ��е�path�д�ŵ�·��Ԫ�ض���ͬ
            ������v�����յ�v��path ���u��v���������ڽӵ㣬d��ʾpath�Ĵ�С����ֵΪ-1
            �����������У�����ǰ���㣬����path[]
            ������u == v����ֹ������˵����u �� v�ҵ���һ����·�������path
            ���ٴӶ���u��һ��δ���ʵĶ���w��
                �������������Ķ��㣬���w������������
                ����������������w��˵���ö���u�������Ҳ���·����������visited[u] = 0���Ա㶥��u��Ϊ����·���ϵĶ��㣬��Ϊ�ָ�����
        ���visited[]����0����ջ������u������·��
*/
void FindPath(GraphAdjList G, int u, int v, int path[], int d)
{
    int w, i;
    EdgeNode *p;
    visited[u] = 1;
    d++; //·������+1,u����·��
    path[d] = u;
    if (u == v) //�ҵ�һ��·��
    {
        printf("����һ����·����");
        for (int i = 0; i <= d; i++)
        {
            printf("%2d", path[i]);
        }
        printf("\n");
    }

    p = G.adjList[u].firstedg; //pָ��u�ĵ�һ���ڽӵ�
    while (p)
    {
        if (!visited[p->adjvex])
        {
            FindPath(G, p->adjvex, v, path, d);
        }
        p = p->next;
    }
    visited[u] = 0; //�ָ�������˵������u�����Ҳ���·������u���»ָ�δ����״̬��ʹ���������ʹ��
}

/*
    ���ͼG�дӶ���u��v�ĳ���Ϊ1�����м�·��   ÿһ��ݹ��е�path�д�ŵ�·��Ԫ�ض���ͬ
    ˼·��  ��������м�·�����ƣ������·��������Ϊd = 1 && u == v����
        1.
*/
void PathAll(GraphAdjList G, int u, int v, int path[], int d)
{
    //d��ʾpath�е�·�����ȣ���ʼΪ-1
    int w, i;
    EdgeNode *p;
    visited[u] = 1;
    d++;
    path[d] = u; //·��������1������u����·��
    if (u == v && d == 1)
    {
        for (int i = 0; i <= d; i++)
        {
            printf("%2d", path[i]);
        }
        printf("\n");
    }
    p = G.adjList[u].firstedg; //pָ��u�ĵ�һ���ڽӵ�
    while (p)
    {
        w = p->adjvex; //wΪu���ڽӵ�
        if (!visited[w])
        {
            PathAll(G, w, v, path, d);
        }
        p = p->next; //pָ����һ���ڽӵ�
    }
    visited[u] = 0; //�ָ�������ʹu������ٴ�ʹ��
}

/*
    �ڽӱ���ͼ�� ͨ��ĳ����k�����м򵥻�·�������ڣ����򵥻�·��ָ·���ϵĶ��㲻�ظ�������һ�������һ����ͬ��·��
    ����v�����յ�v��path ���u��v���������ڽӵ㣬d��ʾpath�Ĵ�С����ֵΪ-1
    ˼·��
        1.���û��ݵ�������ȱ���
        2.�Ӷ���u��ʼ������֮���ڵ�w����w���ڶ���v���ֵΪ��u����·�����ȴ���0����ʾ�ҵ�һ����·�����path����
        3.������������uδ���ʵ����ڵ����������·
*/
void DFSPath(GraphAdjList G, int u, int v, int path[], int d)
{
    int w, i;
    EdgeNode *p;
    d++;
    visited[u] = 1;
    path[d] = u;               //��u���ʣ��Ҽ���·��
    p = G.adjList[u].firstedg; //pָ�򶥵�u�ĵ�һ�����ڵ�

    while (p)
    {
        w = p->adjvex; //wΪu �����ڵ�

        if (w == v && d > 0) //�ҵ�һ����·
        {
            for (int i = 0; i <= d; i++)
            {
                printf("%2d", path[i]);
            }
            printf("%d\n",v);
        }
        if (!visited[w])
        {
            DFSPath(G, w, v, path, d);
        }
        p = p->next;
    }
    visited[u] = 0;
}
void FindCyclePath(GraphAdjList G, int k)
{
    int path[MAXV];
    printf("��������%d�����л�·��\n");
    DFSPath(G, k, k, path, -1);
}
int main(void)
{

    GraphAdjList G;
    CreateALGraph1(&G);
    for (int i = 0; i < G.numVertex; i++)
    {
        visited[i] = 0;
    }
    
    // DFS(G,0);
    // BFS(G,0);
    // bool flag = connect(G);
    bool exist = false;
    VertexType path[MAXV];
    int d = -1;
    // ExistPath(G,0,3,&exist);
    // FindPath(G,0,3,path,d);
    // PathAll(G,0,3,path,d);
    FindCyclePath(G, 0);
    getchar();
    getchar();
    return 0;
}