/*
    �ڽӱ�
    ʱ�䣺2020��6��15��20:35:21
    ��ϰ��2020��8��27��14:35:12
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
 q
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
    �ڽӱ�Ĺ�����ȱ������������Ĳ�α�������Ҫ����һ������
    ˼·��
        1.����ѭ������
        2.��visited������г�ʼ��
        3.���ʳ�ʼ���㣬����ӣ�����Ϊ�ѷ���
        4.���в���ѭ��
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
        //pָ�򶥵�w�ĵ�һ���ڽӵ�
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
            p = p->next; //pָ�򶥵����һ���ڽӵ�
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
    bool flag = true;
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
    EdgeNode *p; //�����ڽӵ�
    //���ɶ�visited�����ʼ��,����visited��Ϊ0����Ϊ�ǵݹ鷽��
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
        p = p->next;//ָ����һ���ڽӵ�
    }
}

/*
    �ڽӱ�,���ͼG�� ���дӶ���u������v��һ����·��
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
    visited[u] = 1;//��Ϊ�ѷ���u
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
        p = p->next;//��һ�ڽӵ�
    }
    visited[u] = 0; //�ָ�������˵������u�����Ҳ���·������u���»ָ�δ����״̬��ʹ���������ʹ��
}

/*
    ���ͼG�дӶ���u��v�ĳ���Ϊ1�����м�·��   ÿһ��ݹ��е�path�д�ŵ�·��Ԫ�ض���ͬ
    ˼·��  ��������м�·�����ƣ������·��������Ϊd == 1 && u == v����
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

        if (w == v && d > 0) //�ҵ�һ����·�����ٰ�����������
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



//������ȱ�����Ӧ��
typedef struct
{
    int data;   //������Ϣ
    int parent; //����ǰ���ڶ����е��±�
} QUEUE;

/* 
    �ڽӱ��󲻴�Ȩ������ͨͼG�дӶ���u������v��һ�����·��
    ˼·��
        1.���ù�����ȱ���,һ��һ�㣬����ɢ��Χ���ԣ����״�u == vʱ�������е�Ԫ�ؼ�Ϊ���·��
        2.���÷ǻ��ζ��У�����ʱҲ�ɱ���֮ǰ����Ԫ�أ����ȡ������ÿ�������ǰ��
*/
void ShortPath(GraphAdjList G, int u, int v)
{
    EdgeNode *p;
    int w, i;
    QUEUE qu[MAXV];
    int front = -1, rear = -1; //��ʼ���ǻ��ζ���
    int visited[MAXV];         //��ʶ����
    for (i = 0; i < G.numVertex; i++)
    {
        visited[i] = 0;
    }
    //��ӣ�parent��ָ����ǰ��
    rear++;
    qu[rear].data = u;
    qu[rear].parent = -1;
    //���в���
    while (rear != front)
    {
        //���׶������
        w = qu[++front].data;

        if (w == v) //�� ����w �� v�״���ȣ������·��
        {
            i = front;//iָ�����·�������һ������
            while (qu[i].parent != -1) //ֻҪparent��Ϊ����u
            {
                printf("%2d", qu[i].data);
                i = qu[i].parent;
            }
            printf("%2d\n", qu[i].data); //�������u
            break;//�˳�����ѭ��
        }

        //pָ�� w�� �׸��ڽӵ�
        p = G.adjList[w].firstedg;
        //������w���ڽӵ�ȫ�����
        while (p)
        {
            if (visited[p->adjvex] == 0)
            {   //��ӣ�parent��ָ��p�����ǰ��
                qu[++rear].data = p->adjvex;
                qu[rear].parent = front; //front Ϊ����w�ڶ����е��±�
            }
            p = p->next;//pָ�� ����w����һ���ڽӵ�
        }
    }
}

/*
    �ڽӱ��󲻴�Ȩ����ͼ�о��붥��v����Զ��һ������
        ��ʵ�����󣬾ඥ��v�ı������Ķ���
        ������ȱ����������е����һ�����㼴Ϊ��Զ
        Ӧ�������·�����ɲ���ѭ������
    ˼·��
        1.������ȱ�����һ��һ���˼�룬ÿһ�㶼����һ���ߣ������һ������һ������Ϊ��Զ����
*/
int Maxdist(GraphAdjList G,int v){
    EdgeNode * p;
    int Qu[MAXV],rear = 0,front = 0;//��ʼ������
    int j,k;//j��ʱ���׶��㣬kΪ ��Զ����
    for (int i = 0; i < G.numVertex; i++)
    {
        visited[i] = 0;//��ʼ�� ��ʶ����
    }
    //��ʶ�����
    visited[v] = 1;
    rear = (rear+1) % MAXV;
    Qu[rear] = v;

    //���в���
    while (rear != front)
    {
        front = (front + 1) % MAXV;
        k = Qu[front];//�����׸���k��ֱ�������һ�����׸���k

        p = G.adjList[k].firstedg;//pָ�� k����ĵ�һ���ڽӵ�
        //����p,��k�������ڽӵ����
        while (p && visited[p->adjvex] == 0 )
        {
            //��ӣ���ʶ
            rear = (rear+1) % MAXV;
            Qu[rear] = p->adjvex;
            visited[p->adjvex] = 1;
            p = p->next;
        }
    }
    return k;
    
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
    // int max = Maxdist(G,0);
    getchar();
    getchar();
    return 0;
}